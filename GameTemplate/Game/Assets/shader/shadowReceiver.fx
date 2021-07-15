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

//ライト用の構造体たち
struct DirectionLigData
{
	float3 ligDir;
	float3 ligColor;
};

struct PointLigData
{
	float3 ligPos;
	float3 ligColor;
	float ligRange;
};

struct SpotLigData
{
	float3 ligPos;
	float3 ligColor;
	float ligRange;
	float3 ligDir;
	float ligAngle;
};

cbuffer LightDataCb : register(b1)
{
	//各配列数はCLightManager.hのMaxLightNumと同じにすること
	DirectionLigData directionLigData[5];
	PointLigData pointLigData[20];
	SpotLigData spotLigData[20];
	float3 eyePos;
	int directionLigNum;
	int pointLigNum;
	int spotLigNum;
};

cbuffer LightCameraCb : register(b2)
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
};
//ピクセルシェーダーへの入力。
struct SPSIn {
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float3 normal		: NORMAL;		//法線
	float2 uv 			: TEXCOORD0;	//uv座標。
	float3 worldPos		: TEXCOORD1;
	float3 normalInView : TEXCOORD2;
	float4 posInLVP 	: TEXCOORD3;
};

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
Texture2D<float4> g_shadowMap : register(t10);			//シャドウマップ
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。
sampler g_sampler : register(s0);	//サンプラステート。
TextureCube<float4> g_skyCubeMap : register(t11);
////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////

/// <summary>
/// 頂点シェーダーのコア関数。
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
	
	//シャドウレシーバー用の頂点シェーダーを実装。
	SPSIn psIn;
	//ここは通常の座標変換
	float4 worldPos = mul(mWorld, vsIn.pos);
	psIn.pos = mul(mWorld, vsIn.pos);
	psIn.worldPos = psIn.pos;
	
	psIn.pos = mul(mView, worldPos);
	psIn.pos = mul(mProj, psIn.pos);
	psIn.uv = vsIn.uv;
	psIn.normal = mul(mWorld, vsIn.normal);

	//ここからライトビュースクリーン空間での座標を計算している。
	psIn.posInLVP = mul(mLVP, worldPos);
	
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

//ランバート拡散反射を計算する。
float3 CalcLambertDiffuse(float3 ligDir, float3 ligColor,float3 normal )
{
	float t = dot(normal, -ligDir);
	
	if (t < 0)
	{
		t = 0;
	}

	return ligColor * t;
}

//フォン鏡面反射を計算する。
float3 CalcPhongSpecular(float3 ligDir, float3 ligColor, float3 worldPos, float3 normal)
{
	float3 toEye = eyePos - worldPos;
	toEye = normalize(toEye);

	float3 refVec = reflect(ligDir, normal);

	float t = dot(toEye, refVec);
	
	if (t < 0)
	{
		t = 0;
	}

	t = pow(t, 2.0f);

	return ligColor * t;
}

float3 CalcLimLight(float3 ligDir, float3 ligColor, float3 normalInView,float3 normal)
{
	float power1 = 1.0f - max(0.0f, dot(ligDir, normal));

	float power2 = 1.0f - max(0.0f, normalInView.z * -1.0f);

	float limPower = power1 * power2;

	limPower = pow(limPower, 5.0f);

	return ligColor * limPower;
}

/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{
	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);

	float4 finalColor = 0.0f;
	finalColor.a = 1.0f;


	//ディレクションライト
	for (int i = 0;i < directionLigNum;i++)
	{
		//ランバート拡散反射
		float3 diffuseLig = CalcLambertDiffuse(directionLigData[i].ligDir, directionLigData[i].ligColor,psIn.normal);

		//フォン鏡面反射
		float3 specularLig = CalcPhongSpecular(directionLigData[i].ligDir, directionLigData[i].ligColor, psIn.worldPos, psIn.normal);

		//リムライト
		//float3 limLig = CalcLimLight(directionLigData[i].ligDir, directionLigData[i].ligColor, psIn.normalInView, psIn.normal);

		float3 finalLig = diffuseLig + specularLig;

		finalColor.xyz +=  finalLig;
	}

	//ポイントライト
	for (int i = 0; i < pointLigNum; i++)
	{
		float3 pointLigDir = psIn.worldPos - pointLigData[i].ligPos;
		pointLigDir = normalize(pointLigDir);

		//ランバート拡散反射
		float3 diffuseLig = CalcLambertDiffuse(pointLigDir, pointLigData[i].ligColor, psIn.normal);

		//フォン鏡面反射
		float3 specularLig = CalcPhongSpecular(pointLigDir,pointLigData[i].ligColor,psIn.worldPos,psIn.normal);

		//リムライト
		//float3 limLig = CalcLimLight(pointLigDir, pointLigData[i].ligColor, psIn.normalInView, psIn.normal);

		float3 finalLig = diffuseLig +specularLig;

		//距離による減衰

		float3 distance = length(psIn.worldPos - pointLigData[i].ligPos);

		float affect = 1.0f - 1.0f / pointLigData[i].ligRange * distance;

		if (affect < 0)
			affect = 0;

		affect = pow(affect, 3.0f);

		finalLig *= affect;

		finalColor.xyz += finalLig;
	}

	//スポットライト
	for (int i = 0; i < spotLigNum; i++)
	{
		float3 spotLigDir = psIn.worldPos - spotLigData[i].ligPos;
		spotLigDir = normalize(spotLigDir);

		//ランバート拡散反射
		float3 diffuseLig = CalcLambertDiffuse(spotLigDir, spotLigData[i].ligColor, psIn.normal);

		//フォン鏡面反射
		float3 specularLig = CalcPhongSpecular(spotLigDir, spotLigData[i].ligColor, psIn.worldPos, psIn.normal);

		//リムライト
		//float3 limLig = CalcLimLight(spotLigDir, spotLigData[i].ligColor, psIn.normalInView, psIn.normal);

		float3 finalLig = diffuseLig + specularLig;

		//距離による減衰

		float3 distance = length(psIn.worldPos - spotLigData[i].ligPos);

		float affect = 1.0f - 1.0f / spotLigData[i].ligRange * distance;

		if (affect < 0)
			affect = 0;

		affect = pow(affect, 3.0f);

		finalLig *= affect;

		//角度による減衰
		float3 toGround = psIn.worldPos - spotLigData[i].ligPos;
		toGround = normalize(toGround);

		float angle = dot(toGround, spotLigData[i].ligDir);
		
		//floatの誤差かacos(1)が0に、acos(-1)がπになるはずなのにNanになっていたので臨時変更(錦織)
		if (-1 < angle && angle < 1)
		{
			angle = acos(angle);
		}
		else if(angle > 0.9 )
		{
			angle = 0;
		}
		else
		{
			angle = acos(-1.0f);
		}

		affect = 1.0f - 1.0f / spotLigData[i].ligAngle * angle;
		if (affect <= 0.0f)
		{
			affect = 0.0f;
		}
		else
		{
			//0より大きい時だけ乗算
			affect = pow(affect, 0.5f);
		}

		finalLig *= affect;

		finalColor.xyz += finalLig;
	}

	//環境光
	float3 ambientLig = 0.3f;
	finalColor.xyz += ambientLig;

	finalColor *= albedoColor;

	//影

	float2 shadowMapUV = psIn.posInLVP.xy / psIn.posInLVP.w;
	shadowMapUV *= float2(0.5f, -0.5f);
	shadowMapUV += 0.5f;

	float zInLVP = psIn.posInLVP.z / psIn.posInLVP.w;
	
	if (shadowMapUV.x > 0.0f && shadowMapUV.x < 1.0f
		&& shadowMapUV.y > 0.0f && shadowMapUV.y < 1.0f)
	{
		// シャドウマップに描き込まれているZ値と比較する
		// 計算したUV座標を使って、シャドウマップから深度値をサンプリング
		float zInShadowMap = g_shadowMap.Sample(g_sampler, shadowMapUV).r;
		if (zInLVP > zInShadowMap)
		{
			// 遮蔽されている
			finalColor.xyz *= 0.5f;			
		}
	}	
	return finalColor;
}

/*!
 *@brief	空用のシェーダー。
 */
float4 PSMain_SkyCube(SPSIn In) : SV_Target0
{

	float4 color = g_skyCubeMap.Sample(g_sampler, In.normal);
	//color.xyz += emissionColor;
	
	return color;
}

