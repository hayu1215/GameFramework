cbuffer global : register(b0)
{
	matrix g_mWVP; //���[���h����ˉe�܂ł̕ϊ��s��
};

struct VS_Output
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};

//
//�o�[�e�b�N�X�V�F�[�_�[
//
VS_Output VS(float4 Pos : POSITION, float4 Color : COLOR)
{
	VS_Output output = (VS_Output)0;
	output.Pos = mul(Pos, g_mWVP);
	output.Color = Color;

	return output;
}

//
//�s�N�Z���V�F�[�_�[
//
float4 PS(VS_Output input) : SV_Target
{
	return input.Color;
}