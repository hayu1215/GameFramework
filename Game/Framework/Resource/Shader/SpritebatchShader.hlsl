Texture2D texDecal: register(t0);//�e�N�X�`���[�� ���W�X�^�[t(n)
SamplerState samLinear : register(s0);//�T���v���[�̓��W�X�^�[s(n)

cbuffer global
{
	matrix wvp;
};

struct VS_Input
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD;
	float4 Color : COLOR;
};

typedef VS_Input VS_Output;
typedef VS_Input PS_Input;

VS_Output VS( VS_Input inout )
{
	VS_Output output = (VS_Output)0;
	output.Pos = mul(input.Pos,wvp);
	output.Tex = input.Tex;
	output.Color = input.Color;
	return output;
}

float4 PS( PS_Input input ) : SV_Target
{
	float4 color = texDecal.Sample(samLinear, input.Tex);
	return input.Color * color;
}