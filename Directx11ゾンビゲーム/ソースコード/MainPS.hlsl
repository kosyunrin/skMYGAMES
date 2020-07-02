

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
// ライトバッファ
struct LIGHT
{
    float4 Direction;
    float4 Diffuse;
    float4 Ambient;
    float4 Specular;
    float4x4 View;
    float4x4 Pro;
    float4 CameraPos;
};

cbuffer LightBuffer : register(b4)
{
    LIGHT Light;
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
struct POINTLIGHT
{
    float3 position;
    float constant;
    float3 ambient;
	float Linear;
    float3 diffuse;
    float quadratic;
    float4 specular;
};
cbuffer PointLightBuffer : register(b9)
{
    POINTLIGHT PointLight;
}





//*****************************************************************************
// グローバル変数
//*****************************************************************************
Texture2D g_Texture : register(t0);
Texture2D Shadow : register(t1);
SamplerState g_SamplerState : register(s0);


//=============================================================================
// ピクセルシェーダ
//=============================================================================


struct VertexIn
{
    float4 inPosition : POSITION0;
    float4 inWorldPos : POSITION1;
    float4 inNormal : NORMAL0;
    float2 inTexCoord : TEXCOORD0;
    float4 inDiffuse : COLOR0;
};

float3 CalcDirLight(LIGHT light, float3 normal, float3 viewDir, float2 coord);
float3 CalcPointLight(POINTLIGHT light, float3 normal, float3 fragPos, float3 viewDir, float2 coord);
float3 CalcSpotLight(SpotlLight light, float3 normal, float3 fragPos, float3 viewDir, float2 coord);

float4 PS(VertexIn In) : SV_Target
{
    float3 Normal = normalize(In.inNormal);
    float3 viewDir = normalize(Light.CameraPos - In.inWorldPos);
    
     // phase 1: directional lighting
    float3 result = CalcDirLight(Light, Normal, viewDir,In.inTexCoord);
    // phase 2: point lights
   // result += CalcPointLight(PointLight, Normal, In.inPosition.xyz, viewDir, In.inTexCoord);
    // phase 3: spot light
    result += CalcSpotLight(SpotLight, Normal, In.inWorldPos.xyz, viewDir,In.inTexCoord);
    
    
    //In.inShadowCooord /= In.inShadowCooord.w;
    //In.inShadowCooord.x = In.inShadowCooord.x * 0.5 + 0.5;
    //In.inShadowCooord.y = -In.inShadowCooord.y * 0.5 + 0.5;
    
    //float Depth = Shadow.Sample(g_SamplerState, In.inShadowCooord.xy - 0.1);
    //if (Depth < intWorldPosition.z)
    //    outDiffuse.rgb = 0.0;
    //else
    //    outDiffuse.rgb = 1.0;
    
    return float4(result, 1.0)*In.inDiffuse;
}




float3 CalcDirLight(LIGHT light, float3 normal, float3 viewDir, float2 coord)
{
    float3 lightDir = normalize(-light.Direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    float3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),32);
    // combine results
    float3 ambient = light.Ambient.xyz * g_Texture.Sample(g_SamplerState, coord).xyz;
    float3 diffuse = light.Diffuse.xyz * diff * g_Texture.Sample(g_SamplerState, coord).xyz;
    float3 specular = light.Specular.xyz * spec * g_Texture.Sample(g_SamplerState, coord).xyz;
    return (ambient + diffuse + specular);
}
float3 CalcPointLight(POINTLIGHT light, float3 normal, float3 fragPos, float3 viewDir, float2 coord)
{
    float3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    float3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),32);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.Linear * distance+light.quadratic * (distance * distance));
    // combine results
    float3 ambient = light.ambient * g_Texture.Sample(g_SamplerState, coord).xyz;
    float3 diffuse = light.diffuse * diff * g_Texture.Sample(g_SamplerState, coord).xyz;
    float3 specular = light.specular.xyz * spec * g_Texture.Sample(g_SamplerState, coord).xyz;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
float3 CalcSpotLight(SpotlLight light, float3 normal, float3 fragPos, float3 viewDir, float2 coord)
{
    float3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    float3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.
    Linear * distance
    +light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    float3 ambient = light.ambient * g_Texture.Sample(g_SamplerState, coord).xyz;
    float3 diffuse = light.diffuse * diff * g_Texture.Sample(g_SamplerState, coord).xyz;
    float3 specular = light.specular * spec * g_Texture.Sample(g_SamplerState, coord).xyz;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}
