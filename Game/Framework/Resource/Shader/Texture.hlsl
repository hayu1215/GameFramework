//�O���[�o��

Texture2D g_texDecal: register(t0);//�e�N�X�`���[�� ���W�X�^�[t(n)
SamplerState g_samLinear : register(s0);//�T���v���[�̓��W�X�^�[s(n)

cbuffer global
{
	matrix g_mWVP; //���[���h����ˉe�܂ł̕ϊ��s��
	float4 g_vDiffuse;//�f�B�t���[�Y�F
	float g_fAlpha;
	float4 g_vUv;
};

//�\����
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD;
};

//
//�o�[�e�b�N�X�V�F�[�_�[
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
//�s�N�Z���V�F�[�_�[
//
float4 PS( VS_OUTPUT input  ) : SV_Target
{
	float4 color = g_texDecal.Sample(g_samLinear, input.Tex);
	color.a *= g_fAlpha;
	return color;
	//return (g_vDiffuse*g_texDecal.Sample( g_samLinear, input.Tex ))*g_fAlpha;
	//return (g_texDecal.Sample(g_samLinear, input.Tex))*g_fAlpha;
}