#define PLMAX 3
#define SLMAX 1

struct DirectionLightSettings
{
    bool Enable;
    float3 Position;
    float4 Direction;
    float4 Diffuse;
    float4 Ambient;
    matrix ViewMatrix;
    matrix ProjectionMatrix;
    matrix ViewTransMatrix;
    matrix ProjectionTransMatrix;
};

cbuffer DirectionLightBuffer : register(b0)
{
    DirectionLightSettings directionLights;
};

cbuffer ShadowBuffer : register(b3)
{
    float Bias;
    float ShadowColor;
    float2 Empty;
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
    float4 final;

    float2 shadowTexCoord;
    shadowTexCoord.x = (input.inLightViewPosition.x / input.inLightViewPosition.w / 2.0) + 0.5;
    shadowTexCoord.y = (-input.inLightViewPosition.y / input.inLightViewPosition.w / 2.0) + 0.5;
  
    if (saturate(shadowTexCoord.x) == shadowTexCoord.x && saturate(shadowTexCoord.y) == shadowTexCoord.y)
    {
        float closestDepth = g_TextureShadow.Sample(g_ClampSamplerState, shadowTexCoord).r;
        float currentDepth = input.inLightViewPosition.z / input.inLightViewPosition.w;
                
        final = currentDepth - Bias < closestDepth ? 1.0 : ShadowColor;
    }
    else
    {
        final = 1.0;
    }
    
    return final;
}