cbuffer global : register(b0)
{
	matrix g_mVP;
};

struct OffsetParam
{
	float3 pos;
	float3 rotate;
	float3 scale;
	float4 color;
};

struct VsInput
{
	float4 pos : POSITION;
	float4 uv : TEXCOORD;
	float4 normal : NORMAL;
	OffsetParam offset : OFFSET;
};

struct VsOutput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
};

struct PsInput
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
};

VsOutput VS(VsInput input)
{
	VsOutput output;
	output.pos.xyz = input.pos.xyz;
	output.pos.w = 1.0f;

	matrix <float, 4, 4> translation =
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		input.offset.pos.x, input.offset.pos.y, input.offset.pos.z, 1.0f
	};

	matrix <float, 4, 4> rotationZ =
	{
		cos(input.offset.rotate.z), sin(input.offset.rotate.z), 0.0f, 0.0f,
		-sin(input.offset.rotate.z), cos(input.offset.rotate.z), 0.0f,  0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	matrix <float, 4, 4> scale =
	{
		input.offset.scale.x, 0.0f, 0.0f, 0.0f,
		0.0f, input.offset.scale.y, 0.0f, 0.0f,
		0.0f, 0.0f, input.offset.scale.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	output.pos = mul(output.pos, scale);
	output.pos = mul(output.pos, rotationZ);
	output.pos = mul(output.pos, translation);
	output.pos = mul(output.pos, g_mVP);

	output.color = input.offset.color;
	return output;
}

float4 PS(PsInput input) : SV_Target
{
	return input.color;
}