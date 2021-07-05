/*!
 * @brief	シンプルなモデルシェーダー。
 */


 ////////////////////////////////////////////////
 // 定数バッファ。
 ////////////////////////////////////////////////
 //モデル用の定数バッファ
cbuffer ModelCb : register(b0) {
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

//ライトカメラの情報
cbuffer LightCameraCb : register(b1)
{
	float4x4 mLVP;
	float3 lightCameraPos;
	float3 lightCameraDir;
};

////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////
//スキニング用の頂点データをひとまとめ。
struct SSkinVSIn {
	int4  Indices  	: BLENDINDICES0;
	float4 Weights  : BLENDWEIGHT0;
};
//頂点シェーダーへの入力。
struct SVSIn {
	float4 pos 		: POSITION;		//モデルの頂点座標。
	float3 normal	: NORMAL;		//法線
	float2 uv 		: TEXCOORD0;	//UV座標。
	SSkinVSIn skinVert;				//スキン用のデータ。
};
//ピクセルシェーダーへの入力。
struct SPSIn {
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float3 normal		: NORMAL;		//法線
	float2 uv 			: TEXCOORD0;	//uv座標。
	float3 worldPos		: TEXCOORD1;
	float3 normalInView : TEXCOORD2;
};

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。
sampler g_sampler : register(s0);	//サンプラステート。

////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////

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
/// 頂点シェーダーのコア関数。
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
	psIn.normal = normalize(psIn.normal);

	psIn.normalInView = mul(mView, psIn.normal);

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
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{
	//ライトからの距離
	//本来の比較用の距離はこっち
	//float depth = length(psIn.worldPos - lightCameraPos)/1000.0f;//深度値を1000で割って0.0～1.0にする

	//ここから平行光源の深度チェックのテスト用。

	//ライトの向きを取得。
	float3 cameraDir = lightCameraDir;
	//正規化されてるはずだけど、念の為。
	cameraDir = normalize(cameraDir);

	float3 axisX = {1.0f,0.0f,0.0f};

	float3 lightCameraAnotherAxis = cross(axisX,cameraDir);

	//axisX,lightCameraAnotherAxisで構成される平面にpsIn.worldPosから垂線をおろす。

	float3 start = psIn.worldPos;

	//スタート地点からカメラの向きをプラスして仮想の垂線をつくる。
	float3 end = psIn.worldPos + -100 * cameraDir;

	//ポリゴンと線分の交差判定を参考に、
	//仮想の垂線とlightCameraPos,lightCameraPos+axisX,lightCameraPos+lightCameraAnotherAxisの
	//3点でできる平面との交点を求めていく。

	float3 toStart = start - lightCameraPos;

	float3 toEnd = end - lightCameraPos;

	float a = dot(cameraDir,toStart);

	float3 cameraDirRev = -cameraDir;

	float b = dot(cameraDirRev,toEnd);

	//crosspointは交点 = 3点でできる平面と垂線の交点。depthの開始点になる。
	float3 crossPoint = toStart - toEnd;
	crossPoint *= b / (a+b);
	crossPoint += end;

	//crossからの長さで平行光源でもしっかり深度がわかる(はず)
	float depth = length(psIn.worldPos - crossPoint)/2000.0f;

	//ここまで平行光源の深度チェックのテスト用。
	return float4(depth,depth*depth,0.0f,1.0f);
	//return float4(depth,0.0f, 0.0f, 1.0f);

}
