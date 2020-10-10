cbuffer global : register(b0) {
    matrix g_mWVP;
    float4 width;
};

struct VS_Output {
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

struct GS_Output {
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

VS_Output VS(float4 Pos : POSITION, float4 Color : COLOR) {
    VS_Output output = (VS_Output)0;
    output.Pos = Pos;
    output.Color = Color;

    return output;
}

//[maxvertexcount(4)]//maxが4でも6頂点をまとめてrestartstripすれば描画される、重なった頂点を認識してるのか？最大値は256らしい
//void GS(line VS_Output input[4], inout TriangleStream<GS_Output> output)
//{
//	float tmp = width.x / 2.0f;
//	GS_Output element = (GS_Output)0;
//	float4 pos = (float4)0;
//
//	for (int i = 0; i < 2; i++)
//	{
//		float4 dir = normalize(input[i].Pos - input[(i + 1) % 2].Pos);
//		
//		pos = input[i].Pos + float4(dir.y * tmp, -dir.x * tmp, 0, 0);
//		element.Pos = mul(pos, g_mWVP);
//		element.Color = input[i].Color;
//		output.Append(element);
//
//		pos = input[i].Pos + float4(-dir.y * tmp, dir.x * tmp, 0, 0);
//		element.Pos = mul(pos, g_mWVP);
//		element.Color = input[i].Color;
//		output.Append(element);
//
//		pos = input[(i + 1) % 2].Pos + float4(dir.y * tmp, -dir.x * tmp, 0, 0);
//		element.Pos = mul(pos, g_mWVP);
//		element.Color = input[(i + 1) % 2].Color;
//		output.Append(element);
//	}
//
//	output.RestartStrip();
//}

[maxvertexcount(6)]//maxが4でも6頂点をまとめてrestartstripすれば描画される、重なった頂点を認識してるのか？最大値は256らしい
void GS(lineadj VS_Output input[4], inout TriangleStream<GS_Output> output) {
    GS_Output element = (GS_Output)0;
    float4 pos = (float4)0;

    //pos = input[0].Pos;
    //element.Pos = mul(pos, g_mWVP);
    //element.Color = float4(0, 1, 0, 1);
    //output.Append(element);

    //pos = input[1].Pos;
    //element.Pos = mul(pos, g_mWVP);
    //element.Color = float4(1, 0, 0, 1);
    //output.Append(element);

    //output.RestartStrip();

    if (all(input[0].Pos) && all(input[0].Color)) {
        input[0].Pos = input[1].Pos;
        input[0].Color = input[1].Color;
    }

    if (all(input[3].Pos) && all(input[3].Color)) {
        input[3].Pos = input[2].Pos;
        input[3].Color = input[2].Color;
    }

    float tmp = width.x / 2.0f;

    float2 p0 = float2(input[0].Pos.x, input[0].Pos.y);
    float2 p1 = float2(input[1].Pos.x, input[1].Pos.y);
    float2 p2 = float2(input[2].Pos.x, input[2].Pos.y);
    float2 p3 = float2(input[3].Pos.x, input[3].Pos.y);

    float2 line0 = p1 - p0;
    float2 line1 = p2 - p1;
    float2 line2 = p3 - p2;

    float2 n0 = normalize(float2(-line0.y, line0.x));
    float2 n1 = normalize(float2(-line1.y, line1.x));
    float2 n2 = normalize(float2(-line2.y, line2.x));

    float2 t0 = normalize(normalize(line0) + normalize(line1));
    float2 t1 = normalize(normalize(line1) + normalize(line2));

    float2 m0 = float2(-t0.y, t0.x);
    float2 m1 = float2(-t1.y, t1.x);

    float d0 = tmp / dot(m0, n0);
    float d1 = tmp / dot(m1, n1);

    float2 a = p1 + m0 * d0;
    float4 A = float4(a.x, a.y, 0, 1);
    float2 b = p1 - m0 * d0;
    float4 B = float4(b.x, b.y, 0, 1);
    float2 c = p2 - m1 * d1;
    float4 C = float4(c.x, c.y, 0, 1);
    float2 d = p2 + m1 * d1;
    float4 D = float4(d.x, d.y, 0, 1);

    pos = A;
    element.Pos = mul(pos, g_mWVP);
    element.Color = input[1].Color;
    output.Append(element);

    pos = B;
    element.Pos = mul(pos, g_mWVP);
    element.Color = input[1].Color;
    output.Append(element);

    pos = C;
    element.Pos = mul(pos, g_mWVP);
    element.Color = input[2].Color;
    output.Append(element);

    pos = A;
    element.Pos = mul(pos, g_mWVP);
    element.Color = input[1].Color;
    output.Append(element);

    pos = C;
    element.Pos = mul(pos, g_mWVP);
    element.Color = input[2].Color;
    output.Append(element);

    pos = D;
    element.Pos = mul(pos, g_mWVP);
    element.Color = input[2].Color;
    output.Append(element);

    output.RestartStrip();
}

//[maxvertexcount(8)]
//void GS(lineadj VS_Output input[4], inout TriangleStream<GS_Output> output)
//{
//	float tmp = width.x / 2.0f;
//
//	float2 p0 = float2(input[0].Pos.x, input[0].Pos.y);
//	float2 p1 = float2(input[1].Pos.x, input[1].Pos.y);
//	float2 p2 = float2(input[2].Pos.x, input[2].Pos.y);
//	float2 p3 = float2(input[3].Pos.x, input[3].Pos.y);
//
//	float2 line0 = p1 - p0;
//	float2 line1 = p2 - p1;
//	float2 line2 = p3 - p2;
//
//	float2 n0 = normalize(float2(-line0.y, line0.x));
//	float2 n1 = normalize(float2(-line1.y, line1.x));
//	float2 n2 = normalize(float2(-line2.y, line2.x));
//
//	float2 a0 = p0 + tmp * n0;
//	float2 b0 = p0 - tmp * n0;
//	float2 a1 = p1 + tmp * n2;
//	float2 b1 = p1 - tmp * n2;
//
//	float2 t0 = normalize(normalize(line0) + normalize(line1));
//	float2 t1 = normalize(normalize(line1) + normalize(line2));
//
//	float2 m0 = float2(-t0.y, t0.x);
//	float2 m1 = float2(-t1.y, t1.x);
//
//	float d0 = tmp / dot(m0, n0);
//	float d1 = tmp / dot(m1, n1);
//
//	float4 A = float4(a0.x, a0.y, 0, 0);
//	float4 B = float4(b0.x, b0.y, 0, 0);
//	float4 C = float4(p1.x + m0.x * d0, p1.y + m0.y * d0, 0, 0);
//	float4 D = float4(p1.x + (-m0.x) * d0, p1.y + (-m0.y) * d0, 0, 0);
//	float4 E = float4(p2.x + m1.x * d1, p2.y + m1.y * d1, 0, 0);
//	float4 F = float4(p2.x + (-m1.x) * d1, p2.y + (-m1.y) * d1, 0, 0);
//	float4 G = float4(a1.x, a1.y, 0, 0);
//	float4 H = float4(b1.x, b1.y, 0, 0);
//
//	GS_Output element = (GS_Output)0;
//	float4 pos = (float4)0;
//
//	pos = A;
//	element.Pos = mul(pos, g_mWVP);
//	element.Color = input[0].Color;
//	output.Append(element);
//
//	pos = C;
//	element.Pos = mul(pos, g_mWVP);
//	element.Color = input[0].Color;
//	output.Append(element);
//
//	pos = B;
//	element.Pos = mul(pos, g_mWVP);
//	element.Color = input[0].Color;
//	output.Append(element);
//
//	output.RestartStrip();
//
//	pos = D;
//	element.Pos = mul(pos, g_mWVP);
//	element.Color = input[0].Color;
//	output.Append(element);
//
//	pos = B;
//	element.Pos = mul(pos, g_mWVP);
//	element.Color = input[0].Color;
//	output.Append(element);
//
//	pos = C;
//	element.Pos = mul(pos, g_mWVP);
//	element.Color = input[0].Color;
//	output.Append(element);
//
//	output.RestartStrip();
//
//	pos = C;
//	element.Pos = mul(pos, g_mWVP);
//	element.Color = input[0].Color;
//	output.Append(element);
//
//	pos = E;
//	element.Pos = mul(pos, g_mWVP);
//	element.Color = input[0].Color;
//	output.Append(element);
//
//	pos = D;
//	element.Pos = mul(pos, g_mWVP);
//	element.Color = input[0].Color;
//	output.Append(element);
//
//	output.RestartStrip();
//
//	pos = F;
//	element.Pos = mul(pos, g_mWVP);
//	element.Color = input[0].Color;
//	output.Append(element);
//
//	pos = D;
//	element.Pos = mul(pos, g_mWVP);
//	element.Color = input[0].Color;
//	output.Append(element);
//
//	pos = E;
//	element.Pos = mul(pos, g_mWVP);
//	element.Color = input[0].Color;
//	output.Append(element);
//
//	output.RestartStrip();
//
//	pos = E;
//	element.Pos = mul(pos, g_mWVP);
//	element.Color = input[0].Color;
//	output.Append(element);
//
//	pos = G;
//	element.Pos = mul(pos, g_mWVP);
//	element.Color = input[0].Color;
//	output.Append(element);
//
//	pos = F;
//	element.Pos = mul(pos, g_mWVP);
//	element.Color = input[0].Color;
//	output.Append(element);
//
//	output.RestartStrip();
//
//	pos = H;
//	element.Pos = mul(pos, g_mWVP);
//	element.Color = input[0].Color;
//	output.Append(element);
//
//	pos = F;
//	element.Pos = mul(pos, g_mWVP);
//	element.Color = input[0].Color;
//	output.Append(element);
//
//	pos = G;
//	element.Pos = mul(pos, g_mWVP);
//	element.Color = input[0].Color;
//	output.Append(element);
//
//	output.RestartStrip();
//}

float4 PS(VS_Output output) : SV_Target {
    return output.Color;
}

float4 crossPoint(float4 p1, float4 p2, float4 p3, float4 p4) {
    float dev = (p2.y - p1.y) * (p4.x - p3.x) - (p2.x - p1.x) * (p4.y - p3.y);
    float d1 = p3.y * p4.x - p3.x * p4.y;
    float d2 = p1.y * p2.x - p1.x * p2.y;

    float4 ap1 = float4(d1*(p2.x - p1.x) - d2 * (p4.x - p3.x), d1*(p2.y - p1.y) - d2 * (p4.y - p3.y), 0, 0);
    ap1.x /= dev;
    ap1.y /= dev;

    return ap1;
}