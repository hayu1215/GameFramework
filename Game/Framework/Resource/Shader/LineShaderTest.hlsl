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

[maxvertexcount(2)]//maxが4でも6頂点をまとめてrestartstripすれば描画される、重なった頂点を認識してるのか？最大値は256らしい
void GS(lineadj VS_Output input[4], inout LineStream<GS_Output> output) {
    GS_Output element = (GS_Output)0;
    float4 pos = (float4)0;

    pos = input[1].Pos;
    element.Pos = mul(pos, g_mWVP);
    element.Color = float4(0, 0, 1, 1);
    output.Append(element);

    pos = input[2].Pos;
    element.Pos = mul(pos, g_mWVP);
    element.Color = float4(0, 0, 1, 1);
    output.Append(element);

    //if (input[3].Pos.x != 0 && input[3].Pos.y != 0) 
    //{
    //	pos = input[1].Pos;
    //	element.Pos = mul(pos, g_mWVP);
    //	element.Color = float4(0, 0, 1, 1);
    //	output.Append(element);
    //}
    //else 
    //{
    //	pos = input[3].Pos;
    //	element.Pos = mul(pos, g_mWVP);
    //	element.Color = float4(0, 0, 1, 1);
    //	output.Append(element);
    //}

    output.RestartStrip();
}

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