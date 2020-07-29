

//*****************************************************************************
// 定数バッファ
//*****************************************************************************

// マテリアルバッファ
cbuffer MaterialBuffer : register(b1)
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
    float4 Emission;
    float Shininess;
    float3 Dummy; //16bit境界用
}
struct SpotlLight
{
    float3 position;
    float3 direction;
    float cutOff; //
    float outerCutOff;

    float constant;
    float Linear;
    float quadratic;

    float3 ambient;
    float3 diffuse;
    float3 specular;
};
cbuffer SpotBuffer : register(b8)
{
    SpotlLight SpotLight;
}





//*****************************************************************************
// グローバル変数
//*****************************************************************************
Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);


//=============================================================================
// ピクセルシェーダ
//=============================================================================
void main(in float4 inPosition : POSITION0,
                         in float4 inWorldPos : POSITION1,
						 in float4 inNormal : NORMAL0,
						 in float2 inTexCoord : TEXCOORD0,
						 in float4 inDiffuse : COLOR0,

						 out float4 outDiffuse : SV_Target)
{

    outDiffuse = g_Texture.Sample( g_SamplerState, inTexCoord );

    outDiffuse *= inDiffuse;
	//outDiffuse = float4(1.0, 1.0, 1.0, 1.0);
}
