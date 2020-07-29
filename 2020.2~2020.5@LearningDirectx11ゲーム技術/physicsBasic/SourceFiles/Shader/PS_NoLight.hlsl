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
    float4 textureDiffuse = g_TextureDiffuse.Sample(g_WrapSamplerState, input.inTexCoord);
    
    //Lower the intensity
    textureDiffuse = float4(textureDiffuse.x, textureDiffuse.y, textureDiffuse.z, textureDiffuse.w);
    
    return textureDiffuse;
}