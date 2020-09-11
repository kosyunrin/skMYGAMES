

//*****************************************************************************
// ??????
//*****************************************************************************

// ?????????
cbuffer MaterialBuffer : register(b1)
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
    float4 Emission;
    float Shininess;
    float3 Dummy; //16bit???
}
// ???????
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
// ???????
//*****************************************************************************
Texture2D g_Texture : register(t0);
Texture2D ShadowMap : register(t1);
SamplerState g_SamplerState : register(s0);
SamplerState ClampSampleType : register(s1);


//=============================================================================
// ????????
//=============================================================================


struct VertexIn
{
    float4 inPosition : POSITION0;
    float4 inWorldPos : POSITION1;
    float4 inNormal : NORMAL0;
    float2 inTexCoord : TEXCOORD0;
    float4 inDiffuse : COLOR0;
    float4 LightPos : NORMAL1;
};

float3 CalcDirLight(LIGHT light, float3 normal, float3 viewDir, float2 coord);
float3 CalcPointLight(POINTLIGHT light, float3 normal, float3 fragPos, float3 viewDir, float2 coord);
float3 CalcSpotLight(SpotlLight light, float3 normal, float3 fragPos, float3 viewDir, float2 coord);

//float4 PS(VertexIn In) : SV_Target
//{
//    float4 TexColor; //采集基??理?色
//    float ShadowMapDepth; //a,g,b存?的都是深度
//    float DiffuseFactor;
//    float4 DiffuseLight;
//    float2 ShadowTex; //?影?理坐?
//    float4 color = { 0.0f, 0.0f, 0.0f, 0.0f }; //最??出的?色
//    float Depth;
//    float bias;
 
 
//	//?置偏斜量
//    bias = 0.0001;
 
//	//第一,?取基??理的采??色
//    TexColor = g_Texture.Sample(g_SamplerState, In.inTexCoord);
 
//	//第二，不管有没有遮?，都??具??境光,注意?境光不生成?影,?里??是漫反射光生成?影
//    color = float4(0.5, 0.5, 0.5, 1.0);
 
	
//	//第三,求出相??点坐???在ShdowMap上的深度?
//	//?取投影相机下的投影?理空?的坐??[0.0,1.0]  u=0.5*x+0.5;   v=-0.5*y+0.5;   -1<=x<=1  -1<=y<=1  
//    ShadowTex.x = (In.LightPos.x / In.LightPos.w) * 0.5f + 0.5f;
//    ShadowTex.y = (In.LightPos.y / In.LightPos.w) * (-0.5f) + 0.5f;
	
 
//	//第四,由于3D模型可能超出投影相机下的?截体，其投影?理可能不在[0.0,1.0],所以得?行判定?个3D物体投影的部分是否在?截体内(没SV_POSITION?名 ??不会?行裁剪)
//    if (saturate(ShadowTex.x) == ShadowTex.x && saturate(ShadowTex.y) == ShadowTex.y)
//    {
//		//求出?点?理坐???的深度?
//        ShadowMapDepth = ShadowMap.Sample(ClampSampleType, ShadowTex).rgb;
 
//		//求出?点坐?相?的深度?(点光源到?染点的深度?)
//        Depth = In.LightPos.z / In.LightPos.w;
 
//		//?去?影偏斜量
//        ShadowMapDepth = ShadowMapDepth + bias;
 
//		//如果不被遮?,?物体具?漫反射光
//        if (ShadowMapDepth >= Depth)
//        {
//			//求出漫反射光的的方向
//            float3 DiffuseDir = In.inWorldPos.xyz - Light.CameraPos.xyz;
 
//			//求出点光源到像素的距?
//            float distance = length(DiffuseDir);
 
//			//求出衰?因子
//            float atten1 = 0.5f;
//            float atten2 = 0.1f;
//            float atten3 = 0.0f;
//            float LightIntensity = 1.0f / (atten1 + atten2 * distance + atten3 * distance * distance);
 
//			//求漫反射光的反光向
//            float3 InvseDiffuseDir = -DiffuseDir;
 
//			//求出漫反射因子[0.0,1.0]
//            DiffuseFactor = saturate(dot(InvseDiffuseDir, In.inNormal.xyz));
		
//			//求出漫射光
//            DiffuseLight = DiffuseFactor * float4(0.5, 0.5, 0.5, 1.0) * LightIntensity;
 
//			//?色加上漫反射光
//            color += DiffuseLight;
		
//            color = saturate(color);
 
//        }
//    }
	
//    color = color * TexColor;
//    //color.w = 1.0;
//    return color;
//}

float4 PS(VertexIn In) : SV_Target
{
    float4 TexColor; //采集基??理?色
    float ShadowMapDepth; //a,g,b存?的都是深度
    float DiffuseFactor;
    float4 DiffuseLight;
    float2 ShadowTex; //?影?理坐?
    float4 color = { 0.0f, 0.0f, 0.0f, 0.0f }; //最??出的?色
    float Depth;
    float bias;
 
 
	//?置偏斜量
    bias = 0.0001;
 
	//第一,?取基??理的采??色
    TexColor = g_Texture.Sample(g_SamplerState, In.inTexCoord);
 
	//第二，不管有没有遮?，都??具??境光,注意?境光不生成?影,?里??是漫反射光生成?影
    color = float4(0.5, 0.5, 0.5, 1.0);
 
	
	//第三,求出相??点坐???在ShdowMap上的深度?
	//?取投影相机下的投影?理空?的坐??[0.0,1.0]  u=0.5*x+0.5;   v=-0.5*y+0.5;   -1<=x<=1  -1<=y<=1  
    ShadowTex.x = (In.LightPos.x / In.LightPos.w) * 0.5f + 0.5f;
    ShadowTex.y = (In.LightPos.y / In.LightPos.w) * (-0.5f) + 0.5f;
    float4 discolor = float4(1.0, 1.0, 1.0, 1.0);
 
	//第四,由于3D模型可能超出投影相机下的?截体，其投影?理可能不在[0.0,1.0],所以得?行判定?个3D物体投影的部分是否在?截体内(没SV_POSITION?名 ??不会?行裁剪)
   // if (saturate(ShadowTex.x) == ShadowTex.x && saturate(ShadowTex.y) == ShadowTex.y)
    {
		//求出?点?理坐???的深度?
        ShadowMapDepth = ShadowMap.Sample(ClampSampleType, ShadowTex).rgb;
 
		//求出?点坐?相?的深度?(点光源到?染点的深度?)
        Depth = In.LightPos.z / In.LightPos.w;
 
		//?去?影偏斜量
        ShadowMapDepth = ShadowMapDepth + bias;
 
		//如果不被遮?,?物体具?漫反射光
        if (ShadowMapDepth >= Depth)
        {
			////求出漫反射光的的方向
   //         float3 DiffuseDir = In.inWorldPos.xyz - Light.CameraPos.xyz;
 
			////求出点光源到像素的距?
   //         float distance = length(DiffuseDir);
 
			////求出衰?因子
   //         float atten1 = 0.5f;
   //         float atten2 = 0.1f;
   //         float atten3 = 0.0f;
   //         float LightIntensity = 1.0f / (atten1 + atten2 * distance);
 
			////求漫反射光的反光向
   //         float3 InvseDiffuseDir = -DiffuseDir;
 
			////求出漫反射因子[0.0,1.0]
   //         DiffuseFactor = saturate(dot(InvseDiffuseDir, In.inNormal.xyz));
		
          
			////求出漫射光
   //         DiffuseLight = LightIntensity;
 
			////?色加上漫反射光
   //         color += DiffuseLight;
		
   //         color = saturate(color);
 
        }
        else
        {
            if (ShadowMapDepth < In.LightPos.z - 0.01 /*バイアス*/)
                color.rgb = 0.0;
        }
    }


	
    color = color * TexColor;
    
    float3 Normal = normalize(In.inNormal);
    float3 viewDir = normalize(Light.CameraPos - In.inWorldPos);
    
    float3 result = CalcDirLight(Light, Normal, viewDir, In.inTexCoord);
    result += CalcSpotLight(SpotLight, Normal, In.inWorldPos.xyz, viewDir, In.inTexCoord);
    
    
    
    return float4(result, 1.0) * color;
    
    
    //color.w = 1.0;
    return color;
}




float3 CalcDirLight(LIGHT light, float3 normal, float3 viewDir, float2 coord)
{
    float3 lightDir = normalize(-light.Direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    float3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
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
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.Linear * distance + light.quadratic * (distance * distance));
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
    + light.quadratic * (distance * distance));
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
