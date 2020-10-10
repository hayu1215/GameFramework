Texture2D texDecal : register(t0);//テクスチャーは レジスターt(n)
SamplerState samLinear : register(s0);//サンプラーはレジスターs(n)

cbuffer global : register(b0) {
    matrix wvp;
};

struct VS_Input {
    float4 Pos : POSITION;
    float2 Tex : TEXCOORD;
    float4 Color : COLOR;
};

struct VS_Output {
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD;
    float4 Color : COLOR;
};

typedef VS_Input PS_Input;
typedef VS_Output PS_Output;

VS_Output VS(VS_Input input) {
    VS_Output output = (VS_Output)0;
    output.Pos = mul(input.Pos, wvp);
    output.Tex = input.Tex;
    output.Color = input.Color;
    return output;
}

float4 PS(PS_Input input) : SV_Target {
    float4 color = texDecal.Sample(samLinear, input.Tex);
    return input.Color * color;
}