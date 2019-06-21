//グローバル

Texture2D g_texDecal: register(t0);//テクスチャーは レジスターt(n)
SamplerState g_samLinear : register(s0);//サンプラーはレジスターs(n)

cbuffer global
{
	matrix g_mWVP; //ワールドから射影までの変換行列
	float4 g_vDiffuse;//ディフューズ色
	float g_fAlpha;
	float4 g_vUv;
};

//構造体
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD;
};

//
//バーテックスシェーダー
//
VS_OUTPUT VS( float4 Pos : POSITION ,float2 Tex : TEXCOORD )
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    output.Pos = mul(Pos,g_mWVP);
	output.Tex = Tex * float2(g_vUv.z, g_vUv.w) + float2(g_vUv.x, g_vUv.y);
	//output.Tex = Tex;

    return output;
}

//
//ピクセルシェーダー
//
float4 PS( VS_OUTPUT input  ) : SV_Target
{
	float4 color = g_texDecal.Sample(g_samLinear, input.Tex);
	color.a *= g_fAlpha;
	return color;
	//return (g_vDiffuse*g_texDecal.Sample( g_samLinear, input.Tex ))*g_fAlpha;
	//return (g_texDecal.Sample(g_samLinear, input.Tex))*g_fAlpha;
}