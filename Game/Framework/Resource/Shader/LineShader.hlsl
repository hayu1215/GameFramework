cbuffer global : register(b0)
{
	matrix g_mWVP;
	float4 width;
};

struct VS_Output
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};

struct GS_Output
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};

VS_Output VS(float4 Pos : POSITION, float4 Color : COLOR)
{
	VS_Output output = (VS_Output)0;
	output.Pos = Pos;
	output.Color = Color;

	return output;
}

[maxvertexcount(6)]
void GS(line VS_Output input[2], inout TriangleStream<GS_Output> output)
{
	float tmp = width.x / 2.0f;
	GS_Output element = (GS_Output)0;
	float4 pos = (float4)0;

	for (int i = 0; i < 2; i++)
	{
		float4 dir = normalize(input[i].Pos - input[(i + 1) % 2].Pos);
		
		pos = input[i].Pos + float4(dir.y * tmp, -dir.x * tmp, 0, 0);
		element.Pos = mul(pos, g_mWVP);
		element.Color = input[i].Color;
		output.Append(element);

		pos = input[i].Pos + float4(-dir.y * tmp, dir.x * tmp, 0, 0);
		element.Pos = mul(pos, g_mWVP);
		element.Color = input[i].Color;
		output.Append(element);

		pos = input[(i + 1) % 2].Pos + float4(dir.y * tmp, -dir.x * tmp, 0, 0);
		element.Pos = mul(pos, g_mWVP);
		element.Color = input[i].Color;
		output.Append(element);

		output.RestartStrip();
	}
}

float4 PS(VS_Output output) : SV_Target
{
	return output.Color;
}