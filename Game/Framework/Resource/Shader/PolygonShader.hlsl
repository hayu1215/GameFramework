cbuffer global : register(b0)
{
	matrix g_mWVP; //ワールドから射影までの変換行列
};

struct VS_Output
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};

//
//バーテックスシェーダー
//
VS_Output VS(float4 Pos : POSITION, float4 Color : COLOR)
{
	VS_Output output = (VS_Output)0;
	output.Pos = mul(Pos, g_mWVP);
	output.Color = Color;

	return output;
}

//
//ピクセルシェーダー
//
float4 PS(VS_Output input) : SV_Target
{
	return input.Color;
}