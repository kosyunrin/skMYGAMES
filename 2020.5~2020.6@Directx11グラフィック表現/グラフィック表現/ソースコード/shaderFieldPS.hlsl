

#include "shaderNoise.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);


// 定数バッファ
cbuffer ConstatntBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;

    float4 CameraPosition;
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
void main(in float4 inPosition : SV_POSITION,
            in float4 inWorldPosition : POSITION0,
			in float4 inNormal : NORMAL0,
			in float4 inDiffuse : COLOR0,
			in float2 inTexCoord : TEXCOORD0,

			out float4 outDiffuse : SV_Target)
{
    int octave = 10;
    float dx = fbm2(inTexCoord + float2(0.0001, 0.0), octave)
            - fbm2(inTexCoord + float2(-0.0001, 0.0), octave);
    float dz = fbm2(inTexCoord + float2(0.0, 0.0001), octave)
            - fbm2(inTexCoord + float2(0.0, -0.0001), octave);
    
    float3 normal = float3(dx * 3000.0, 1.0, -dz * 3000.0);
    normal = normalize(normal);
    
    float3 lightdir = Light.Direction.xyz;
    lightdir = normalize(lightdir);
    float light = saturate(0.5 - dot(normal, lightdir) * 0.5);
    
    //////////////
  

    /////////////
    outDiffuse = g_Texture.Sample(g_SamplerState, inTexCoord * 10);
    outDiffuse *= light;
    

    float3 diffuse = outDiffuse.rgb;
    //大気距離
    float dist = distance(inWorldPosition, CameraPosition);
    //視線ベクトル
    float3 eye = inWorldPosition - CameraPosition;
    eye = normalize(eye);
    //ミーshan luan
    float m = saturate(-dot(Light.Direction.xyz, eye));
    m = pow(m, 50);

    diffuse += m * dist * 0.003;


    //レイリー散乱
    float3 vy = float3(0.0, 1.0, 0.0);
    float atm = saturate(1.0 - dot(-Light.Direction.xyz, vy));
    float3 rcolor = 1.0 - float3(0.5, 0.8, 1.0) * atm;

    float id = 0.5 - dot(Light.Direction.xyz, eye) * 0.5;

    diffuse += rcolor * dist * id * float3(0.5, 0.8, 1.0) * 0.004;

    outDiffuse.rgb *= diffuse;

    outDiffuse.a = 1.0;
}
