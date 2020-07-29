

#include "shaderNoise.hlsl"

Texture2D		g_Texture : register(t0);
SamplerState	g_SamplerState : register(s0);

// 定数バッファ
cbuffer ConstatntBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;

    float4 CameraPosition;
    float4 Parameter;

}
struct LIGHT
{
    float4 Direction;
    float4 Diffuse;
    float4 Ambient;
};

cbuffer LightBuffer : register(b1)
{
    LIGHT Light;
}



//=============================================================================
// ピクセルシェーダ
//=============================================================================
void main( in  float4 inPosition		: SV_POSITION,
            in float4 inWorldPosition   : POSITION0,
			in  float4 inNormal			: NORMAL0,
			in  float4 inDiffuse		: COLOR0,
			in  float2 inTexCoord		: TEXCOORD0,

			out float4 outDiffuse		: SV_Target )
{
    float offset = -Parameter.x * 0.5;
    int octave = 5;
    float dx = fbm2offet(inTexCoord + float2(0.0001, 0.0), octave, offset)
            - fbm2offet(inTexCoord + float2(-0.0001, 0.0), octave, offset);
    float dz = fbm2offet(inTexCoord + float2(0.0, 0.0001), octave, offset)
            - fbm2offet(inTexCoord + float2(0.0, -0.0001), octave, offset);
    
    float3 normal = float3(dx * 3000.0, 1.0, -dz * 3000.0);
    normal = normalize(normal);
    
  /////
    
    float light = -dot(Light.Direction.xyz, normal);
    
    
    
    ///////

    //water
    float3 eyev = inWorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);
    float fresnel = saturate(1.0 + dot(eyev, normal));
    fresnel =0.01 + (1.0 - 0.05) * pow(fresnel, 5);

    outDiffuse.rgb = float3(0.0, 0.1, 0.1) * (1.0 - fresnel)
    + float3(0.9, 0.95, 1.0) * fresnel ;
    outDiffuse.rgb *= light;
    outDiffuse.a = 0.5;
    
    
    
    
}
