///////////////////////////////////////////
// 構造体
///////////////////////////////////////////
// //スキニング用の頂点データをひとまとめ。
struct SSkinVSIn {
    int4  Indices  	: BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};
// 頂点シェーダーへの入力
struct SVSIn
{
    float4 pos      : POSITION;
    float3 normal   : NORMAL;
    float2 uv       : TEXCOORD0;
    SSkinVSIn skinVert;
};

// ピクセルシェーダーへの入力
struct SPSIn
{
    float4 pos      : SV_POSITION;
    float3 normal   : NORMAL;
    float2 uv       : TEXCOORD0;
    float3 worldPos : TEXCOORD1;
    float3 normalInView:TEXCOORD2;
};

struct DirectionLight
{
    float3 direction; // ライトの方向
    float3 color;     // ライトのカラー
};
struct PointLight
{
    float3 position;
    float3 color;
    float range;
};
struct SpotLight
{
    float3 position;
    float3 color;
    float range;
    float3 direction;
    float angle;
};
///////////////////////////////////////////
// 定数バッファー
///////////////////////////////////////////
// モデル用の定数バッファー
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

// ディレクションライト用のデータを受け取るための定数バッファーを用意する
cbuffer DirectionLightCb : register(b1)
{
    DirectionLight directionLight[5];    
    PointLight pointLight[20];
    SpotLight spotLight[20];
    float3 eyePos; // 視点の位置
    int directionLightNum;
    int pointLightNum;
    int spotLightNum;
};
///////////////////////////////////////////
// 関数宣言
///////////////////////////////////////////
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal);
float3 CalcLigFromPointLight(SPSIn psIn,int num);
float3 CalcLigFromDirectionLight(SPSIn psIn,int num);
float3 CalcLigFromSpotLight(SPSIn psIn,int num);
///////////////////////////////////////////
// シェーダーリソース
///////////////////////////////////////////
// モデルテクスチャ
Texture2D<float4> g_texture : register(t0);

///////////////////////////////////////////
// サンプラーステート
///////////////////////////////////////////
sampler g_sampler : register(s0);

//ボーン行列
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。

/// <summary>
//スキン行列を計算する。
/// </summary>
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
    float4x4 skinning = 0;
    float w = 0.0f;
    [unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }

    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);

    return skinning;
}

/// <summary>
/// モデル用の頂点シェーダーのエントリーポイント
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
    SPSIn psIn;
    float4x4 m;
    if (hasSkin) {
        m = CalcSkinMatrix(vsIn.skinVert);
    }
    else {
        m = mWorld;
    }
    psIn.pos = mul(m, vsIn.pos);

    psIn.worldPos = psIn.pos;

    psIn.pos = mul(mView, psIn.pos);
    psIn.pos = mul(mProj, psIn.pos);
    psIn.normal = mul(m, vsIn.normal);
    // 頂点法線をピクセルシェーダーに渡す
    psIn.normal = mul(mWorld, vsIn.normal); // 法線を回転させる

    psIn.uv = vsIn.uv;

    return psIn;
}
/// <summary>
/// スキンなしメッシュ用の頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, false);
}
/// <summary>
/// スキンありメッシュの頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSSkinMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, true);
}
/// <summary>
/// モデル用のピクセルシェーダーのエントリーポイント
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{
    float3 finalLig = {0,0,0};
    // ディレクションライトによるライティングを計算する
    for (int i=0; i < directionLightNum; i++) {
        float3 directionLig = CalcLigFromDirectionLight(psIn,i);
        finalLig += directionLig;
    }
    // ポイントライトによるライティングを計算する
    for (int i = 0; i < pointLightNum; i++) {
        float3 pointLig = CalcLigFromPointLight(psIn,i);
        finalLig += pointLig;
    }
    //スポットライトによるライティングを計算する
    for (int i = 0; i < spotLightNum; i++) {
        float3 spotLig = CalcLigFromSpotLight(psIn, i);
        finalLig += spotLig;
    }
    // 反射光を最終的な反射光に足し算する
    float3 ambientLight = { 0.5,0.5, 0.5 };//環境光
    finalLig += ambientLight;
    float4 finalColor = g_texture.Sample(g_sampler, psIn.uv);

    // テクスチャカラーに求めた光を乗算して最終出力カラーを求める
    finalColor.xyz *= finalLig;

    return finalColor;
}
/// <summary>
/// Lambert拡散反射光を計算する
/// </summary>
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{
    // ピクセルの法線とライトの方向の内積を計算する
    float t = dot(normal, lightDirection) * -1.0f;

    // 内積の値を0以上の値にする
    t = max(0.0f, t);

    // 拡散反射光を計算する
    return lightColor * t;
}

/// <summary>
/// Phong鏡面反射光を計算する
/// </summary>
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal)
{
    // 反射ベクトルを求める
    float3 refVec = reflect(lightDirection, normal);

    // 光が当たったサーフェイスから視点に伸びるベクトルを求める
    float3 toEye = eyePos - worldPos;
    toEye = normalize(toEye);

    // 鏡面反射の強さを求める
    float t = dot(refVec, toEye);

    // 鏡面反射の強さを0以上の数値にする
    t = max(0.0f, t);

    // 鏡面反射の強さを絞る
    t = pow(t, 1.5f);

    // 鏡面反射光を求める
    return lightColor * t;
}
/// <summary>
/// ポイントライトによる反射光を計算
/// </summary>
/// <param name="psIn">ピクセルシェーダーに渡されている引数</param>
float3 CalcLigFromPointLight(SPSIn psIn,int num)
{
    // このサーフェイスに入射しているポイントライトの光の向きを計算する
    float3 ligDir = psIn.worldPos - pointLight[num].position;

    // 正規化して大きさ1のベクトルにする
    ligDir = normalize(ligDir);

    // 減衰なしのLambert拡散反射光を計算する
    float3 diffPoint = CalcLambertDiffuse(
        ligDir,     // ライトの方向
        pointLight[num].color,    // ライトのカラー
        psIn.normal // サーフェイスの法線
    );

    // 減衰なしのPhong鏡面反射光を計算する
    float3 specPoint = CalcPhongSpecular(
        ligDir,         // ライトの方向
        pointLight[num].color,        // ライトのカラー
        psIn.worldPos,  // サーフェイズのワールド座標
        psIn.normal     // サーフェイズの法線
    );

    // 距離による影響率を計算する
    // ポイントライトとの距離を計算する
    float3 distance = length(psIn.worldPos - pointLight[num].position);

    // 影響率は距離に比例して小さくなっていく
    float affect = 1.0f - 1.0f / pointLight[num].range * distance;

    // 影響力がマイナスにならないように補正をかける
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }

    // 影響の仕方を指数関数的にする。今回のサンプルでは3乗している
    affect = pow(affect, 5.0f);

    // 拡散反射光と鏡面反射光に減衰率を乗算して影響を弱める
    diffPoint *= affect;
    specPoint *= affect;

    return diffPoint + specPoint;
}

/// <summary>
/// ディレクションライトによる反射光を計算
/// </summary
/// <param name="psIn">ピクセルシェーダーからの入力。</param>
float3 CalcLigFromDirectionLight(SPSIn psIn,int num)
{
    // ディレクションライトによるLambert拡散反射光を計算する
    float3 diffDirection = CalcLambertDiffuse(directionLight[num].direction, directionLight[num].color, psIn.normal);

    // ディレクションライトによるPhong鏡面反射光を計算する
    float3 specDirection = CalcPhongSpecular(directionLight[num].direction, directionLight[num].color, psIn.worldPos, psIn.normal);
    return diffDirection + specDirection;
}
//スポットライトに取る反射光を計算
float3 CalcLigFromSpotLight(SPSIn psIn,int num)
{
    //サーフェイスに入射するポイントライトの光の向きを計算する
    float3 ligDir = psIn.worldPos - spotLight[num].position;
    // 正規化して大きさ1のベクトルにする
    ligDir = normalize(ligDir);

    // 減衰なしのLambert拡散反射光を計算する
    float3 diffSpotLight = CalcLambertDiffuse(
        ligDir,     // ライトの方向
        spotLight[num].color,    // ライトのカラー
        psIn.normal // サーフェイスの法線
    );

    // 減衰なしのPhong鏡面反射光を計算する
    float3 specSpotLight = CalcPhongSpecular(
        ligDir,         // ライトの方向
        spotLight[num].color,// ライトのカラー
        psIn.worldPos,  // サーフェイズのワールド座標
        psIn.normal     // サーフェイズの法線
    );

    // 距離による影響率を計算する
    // ポイントライトとの距離を計算する
    float3 distance = length(psIn.worldPos - spotLight[num].position);

    // 影響率は距離に比例して小さくなっていく
    float affect = 1.0f - 1.0f / spotLight[num].range * distance;

    // 影響力がマイナスにならないように補正をかける
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }

    //影響を指数関数的にする。今回のサンプルでは3乗している
    affect = pow(affect, 3.0f);

    // 拡散反射光と鏡面反射光に減衰率を乗算して影響を弱める
    diffSpotLight *= affect;
    specSpotLight *= affect;

    // dot()を利用して内積を求める
    float angle = dot(ligDir, spotLight[num].direction);

    // dot()で求めた値をacos()に渡して角度を求める
    angle = abs(acos(angle));

    // 角度による影響率を求める
    // 角度に比例して小さくなっていく影響率を計算する
    affect = 1.0f - 1.0f / spotLight[num].angle * angle;

    // 影響率がマイナスにならないように補正をかける
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }

    // 影響の仕方を指数関数的にする。今回のサンプルでは0.5乗している
    affect = pow(affect, 0.5f);

    // 角度による影響率を反射光に乗算して、影響を弱める
    diffSpotLight *= affect;
    specSpotLight *= affect;
    
    // ディレクションライト+ポイントライト+環境光を求める
    return diffSpotLight + specSpotLight;
}
