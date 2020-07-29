

//*****************************************************************************
// 定数バッファ
//*****************************************************************************

// マテリアルバッファ
cbuffer MaterialBuffer : register( b1 )
{
	float4		Ambient;
	float4		Diffuse;
	float4		Specular;
	float4		Emission;
	float		Shininess;
	float3		Dummy;//16bit境界用
}
struct SpotlLight
{
    float3 position;
    float cutOff; //

    float3 direction;
    float outerCutOff;


    float3 ambient;
    float constant;

    float3 diffuse;
    float Linear;

    float3 specular;
    float quadratic;

};
cbuffer SpotBuffer : register(b8)
{
    SpotlLight SpotLight;
}





//*****************************************************************************
// グローバル変数
//*****************************************************************************
Texture2D		g_Texture : register( t0 );
SamplerState	g_SamplerState : register( s0 );


//=============================================================================
// ピクセルシェーダ
//=============================================================================
void main( in  float4 inPosition		: POSITION0,
                         in float4 inWorldPos : POSITION1,
						 in  float4 inNormal		: NORMAL0,
						 in  float2 inTexCoord		: TEXCOORD0,
						 in  float4 inDiffuse		: COLOR0,

						 out float4 outDiffuse		: SV_Target )
{

    //outDiffuse = g_Texture.Sample( g_SamplerState, inTexCoord );
    
    float3 viewDir = normalize(SpotLight.position - inPosition.xyz);
    
    float3 lightDir = normalize(SpotLight.position - inPosition.xyz);
     // diffuse shading
    float diff = max(dot(inNormal.xyz, lightDir), 0.0);
    // specular shading
    float3 reflectDir = reflect(-lightDir, inNormal.xyz);
    
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16.0f); //jisuanfashe
    // attenuation
    float distance = length(SpotLight.position - inPosition.xyz);
    float attenuation = 1.0f / (SpotLight.constant + SpotLight.
    Linear * distance
    + SpotLight.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-SpotLight.direction));
    float epsilon = SpotLight.cutOff - SpotLight.outerCutOff;
    float intensity = clamp((theta - SpotLight.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    float3 ambient = SpotLight.ambient * g_Texture.Sample(g_SamplerState, inTexCoord).xyz;
    float3 diffuse = SpotLight.diffuse * diff * g_Texture.Sample(g_SamplerState, inTexCoord).xyz;
    float3 specular = SpotLight.specular * spec * g_Texture.Sample(g_SamplerState, inTexCoord).xyz;
    ambient  *= attenuation * intensity;
    diffuse   *= attenuation * intensity ;
    specular *= attenuation * intensity;
    float3 result = (ambient + diffuse + specular);
    outDiffuse = float4(result, 1.0f);
    
    
    

 	outDiffuse *= inDiffuse;
	//outDiffuse = float4(1.0, 1.0, 1.0, 1.0);
}
