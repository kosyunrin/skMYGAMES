cbuffer BlurBuffer : register(b4)
{
    float Width;
    float Height;
    float Factor;
    float Empty;
}

struct PS_INPUT
{
    float4 inPosition : SV_POSITION;
    float3 inPositionW : POSITIONW;
    float4 inDepthPosition : DEPTHPOSITION;
    float3 inNormal : NORMAL;
    float2 inTexCoord : TEXCOORD;
    float3 inTangent : TANGENT;
    float3 inBitangent : BITANGENT;
    float3 inViewDirection : VIEWDIRECTION;
    float4 inReflectPosition : REFLECTTEXCOORD;
    float4 inLightViewPosition : LIGHTDIRECTION;
    float3 inLightPosition : LIGHTPOSITION;
};

Texture2D g_TextureDiffuse : register(t0);
Texture2D g_TextureNormal : register(t1);
Texture2D g_TextureSpecular : register(t2);
Texture2D g_TextureReflection : register(t3);
Texture2D g_TextureShadow : register(t4);

SamplerState g_WrapSamplerState : register(s0);
SamplerState g_ClampSamplerState : register(s1);
SamplerState g_PointSamplerState : register(s2);

float4 main(PS_INPUT input) : SV_TARGET
{
    //Determine the floating point size of texel for a screen size
    float widthSize = 1.0 / Width;
    float heightSize = 1.0 / Height;

    //Horizontal
    float2 wtexCoord1 = input.inTexCoord + float2(widthSize * -4.0, 0.0);
    float2 wtexCoord2 = input.inTexCoord + float2(widthSize * -3.0, 0.0);
    float2 wtexCoord3 = input.inTexCoord + float2(widthSize * -2.0, 0.0);
    float2 wtexCoord4 = input.inTexCoord + float2(widthSize * -1.0, 0.0);
    float2 wtexCoord5 = input.inTexCoord + float2(widthSize * 0.0, 0.0);
    float2 wtexCoord6 = input.inTexCoord + float2(widthSize * 1.0, 0.0);
    float2 wtexCoord7 = input.inTexCoord + float2(widthSize * 2.0, 0.0);
    float2 wtexCoord8 = input.inTexCoord + float2(widthSize * 3.0, 0.0);
    float2 wtexCoord9 = input.inTexCoord + float2(widthSize * 4.0, 0.0);

    //Vertical
    float2 htexCoord1 = input.inTexCoord + float2(0.0, heightSize * -4.0);
    float2 htexCoord2 = input.inTexCoord + float2(0.0, heightSize * -3.0);
    float2 htexCoord3 = input.inTexCoord + float2(0.0, heightSize * -2.0);
    float2 htexCoord4 = input.inTexCoord + float2(0.0, heightSize * -1.0);
    float2 htexCoord5 = input.inTexCoord + float2(0.0, heightSize * 0.0);
    float2 htexCoord6 = input.inTexCoord + float2(0.0, heightSize * 1.0);
    float2 htexCoord7 = input.inTexCoord + float2(0.0, heightSize * 2.0);
    float2 htexCoord8 = input.inTexCoord + float2(0.0, heightSize * 3.0);
    float2 htexCoord9 = input.inTexCoord + float2(0.0, heightSize * 4.0);

    float weight1 = 1.0;
    float weight2 = 0.9;
    float weight3 = 0.55;
    float weight4 = 0.18;
    float weight5 = 0.1;

    float totalWeight = (weight1 + 2.0 * (weight2 + weight3 + weight4 + weight5));

    weight1 = weight1 / totalWeight;
    weight2 = weight2 / totalWeight;
    weight3 = weight3 / totalWeight;
    weight4 = weight4 / totalWeight;
    weight5 = weight5 / totalWeight;

    float4 horizontal = float4(0.0, 0.0, 0.0, 1.0);

    horizontal += g_TextureDiffuse.Sample(g_WrapSamplerState, wtexCoord1) * weight5;
    horizontal += g_TextureDiffuse.Sample(g_WrapSamplerState, wtexCoord2) * weight4;
    horizontal += g_TextureDiffuse.Sample(g_WrapSamplerState, wtexCoord3) * weight3;
    horizontal += g_TextureDiffuse.Sample(g_WrapSamplerState, wtexCoord4) * weight2;
    horizontal += g_TextureDiffuse.Sample(g_WrapSamplerState, wtexCoord5) * weight1;
    horizontal += g_TextureDiffuse.Sample(g_WrapSamplerState, wtexCoord6) * weight2;
    horizontal += g_TextureDiffuse.Sample(g_WrapSamplerState, wtexCoord7) * weight3;
    horizontal += g_TextureDiffuse.Sample(g_WrapSamplerState, wtexCoord8) * weight4;
    horizontal += g_TextureDiffuse.Sample(g_WrapSamplerState, wtexCoord9) * weight5;

    float4 vertical = float4(0.0, 0.0, 0.0, 1.0);
    vertical += g_TextureDiffuse.Sample(g_WrapSamplerState, htexCoord1) * weight5;
    vertical += g_TextureDiffuse.Sample(g_WrapSamplerState, htexCoord2) * weight4;
    vertical += g_TextureDiffuse.Sample(g_WrapSamplerState, htexCoord3) * weight3;
    vertical += g_TextureDiffuse.Sample(g_WrapSamplerState, htexCoord4) * weight2;
    vertical += horizontal * weight1;
    vertical += g_TextureDiffuse.Sample(g_WrapSamplerState, htexCoord6) * weight2;
    vertical += g_TextureDiffuse.Sample(g_WrapSamplerState, htexCoord7) * weight3;
    vertical += g_TextureDiffuse.Sample(g_WrapSamplerState, htexCoord8) * weight4;
    vertical += g_TextureDiffuse.Sample(g_WrapSamplerState, htexCoord9) * weight5;

    return vertical;
}