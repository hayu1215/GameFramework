cbuffer global : register(b0)
{
	float4 width;
};

struct VS_Input
{
	float4 Pos : POSITION;
	float4 Color : COLOR;
};

struct GS_Output
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};

[maxvertexcount(6)]
void GS(
	line VS_Input input[2],
	inout TriangleStream< GS_Output > output
)
{
	for (int i = 0; i < 2; i++)
	{
		float tmp = width.x / 2.0f;
		{
			GS_Output element;
			element.Pos = input[i].Pos + float4(tmp, 0.0f, 0.0f, 0.0f);
			element.Color = input[i].Color;
			output.Append(element);
		}
		{
			GS_Output element;
			element.Pos = input[i].Pos + float4(-tmp, 0.0f, 0.0f, 0.0f);
			element.Color = input[i].Color;
			output.Append(element);
		}
		{
			GS_Output element;
			element.Pos = input[(i + 1) % 2].Pos + float4(tmp * sign(i - 1), 0.0f, 0.0f, 0.0f);
			element.Color = input[(i + 1) % 2].Color;
			output.Append(element);
		}
		output.RestartStrip();
	}
}