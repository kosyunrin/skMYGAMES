

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
//    float4 TexColor; //�яW��??��?�F
//    float ShadowMapDepth; //a,g,b��?�I�s���[�x
//    float DiffuseFactor;
//    float4 DiffuseLight;
//    float2 ShadowTex; //?�e?����?
//    float4 color = { 0.0f, 0.0f, 0.0f, 0.0f }; //��??�o�I?�F
//    float Depth;
//    float bias;
 
 
//	//?�u�ΎΗ�
//    bias = 0.0001;
 
//	//���,?���??���I��??�F
//    TexColor = g_Texture.Sample(g_SamplerState, In.inTexCoord);
 
//	//���C�s�ǗL�v�L��?�C�s??��??����,����?�����s����?�e,?��??�������ˌ�����?�e
//    color = float4(0.5, 0.5, 0.5, 1.0);
 
	
//	//��O,���o��??�_��???��ShdowMap��I�[�x?
//	//?�擊�e�������I���e?����?�I��??[0.0,1.0]  u=0.5*x+0.5;   v=-0.5*y+0.5;   -1<=x<=1  -1<=y<=1  
//    ShadowTex.x = (In.LightPos.x / In.LightPos.w) * 0.5f + 0.5f;
//    ShadowTex.y = (In.LightPos.y / In.LightPos.w) * (-0.5f) + 0.5f;
	
 
//	//��l,�R��3D�͌^�\���o���e�������I?�B�́C�����e?���\�s��[0.0,1.0],���ȓ�?�s����?��3D���̓��e�I�������ۍ�?�B�̓�(�vSV_POSITION?�� ??�s��?�s�ٙ�)
//    if (saturate(ShadowTex.x) == ShadowTex.x && saturate(ShadowTex.y) == ShadowTex.y)
//    {
//		//���o?�_?����???�I�[�x?
//        ShadowMapDepth = ShadowMap.Sample(ClampSampleType, ShadowTex).rgb;
 
//		//���o?�_��?��?�I�[�x?(�_������?���_�I�[�x?)
//        Depth = In.LightPos.z / In.LightPos.w;
 
//		//?��?�e�ΎΗ�
//        ShadowMapDepth = ShadowMapDepth + bias;
 
//		//�@�ʕs���?,?���̋�?�����ˌ�
//        if (ShadowMapDepth >= Depth)
//        {
//			//���o�����ˌ��I�I����
//            float3 DiffuseDir = In.inWorldPos.xyz - Light.CameraPos.xyz;
 
//			//���o�_���������f�I��?
//            float distance = length(DiffuseDir);
 
//			//���o��?���q
//            float atten1 = 0.5f;
//            float atten2 = 0.1f;
//            float atten3 = 0.0f;
//            float LightIntensity = 1.0f / (atten1 + atten2 * distance + atten3 * distance * distance);
 
//			//�������ˌ��I������
//            float3 InvseDiffuseDir = -DiffuseDir;
 
//			//���o�����ˈ��q[0.0,1.0]
//            DiffuseFactor = saturate(dot(InvseDiffuseDir, In.inNormal.xyz));
		
//			//���o���ˌ�
//            DiffuseLight = DiffuseFactor * float4(0.5, 0.5, 0.5, 1.0) * LightIntensity;
 
//			//?�F���㖟���ˌ�
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
    float4 TexColor; //�яW��??��?�F
    float ShadowMapDepth; //a,g,b��?�I�s���[�x
    float DiffuseFactor;
    float4 DiffuseLight;
    float2 ShadowTex; //?�e?����?
    float4 color = { 0.0f, 0.0f, 0.0f, 0.0f }; //��??�o�I?�F
    float Depth;
    float bias;
 
 
	//?�u�ΎΗ�
    bias = 0.0001;
 
	//���,?���??���I��??�F
    TexColor = g_Texture.Sample(g_SamplerState, In.inTexCoord);
 
	//���C�s�ǗL�v�L��?�C�s??��??����,����?�����s����?�e,?��??�������ˌ�����?�e
    color = float4(0.5, 0.5, 0.5, 1.0);
 
	
	//��O,���o��??�_��???��ShdowMap��I�[�x?
	//?�擊�e�������I���e?����?�I��??[0.0,1.0]  u=0.5*x+0.5;   v=-0.5*y+0.5;   -1<=x<=1  -1<=y<=1  
    ShadowTex.x = (In.LightPos.x / In.LightPos.w) * 0.5f + 0.5f;
    ShadowTex.y = (In.LightPos.y / In.LightPos.w) * (-0.5f) + 0.5f;
    float4 discolor = float4(1.0, 1.0, 1.0, 1.0);
 
	//��l,�R��3D�͌^�\���o���e�������I?�B�́C�����e?���\�s��[0.0,1.0],���ȓ�?�s����?��3D���̓��e�I�������ۍ�?�B�̓�(�vSV_POSITION?�� ??�s��?�s�ٙ�)
   // if (saturate(ShadowTex.x) == ShadowTex.x && saturate(ShadowTex.y) == ShadowTex.y)
    {
		//���o?�_?����???�I�[�x?
        ShadowMapDepth = ShadowMap.Sample(ClampSampleType, ShadowTex).rgb;
 
		//���o?�_��?��?�I�[�x?(�_������?���_�I�[�x?)
        Depth = In.LightPos.z / In.LightPos.w;
 
		//?��?�e�ΎΗ�
        ShadowMapDepth = ShadowMapDepth + bias;
 
		//�@�ʕs���?,?���̋�?�����ˌ�
        if (ShadowMapDepth >= Depth)
        {
			////���o�����ˌ��I�I����
   //         float3 DiffuseDir = In.inWorldPos.xyz - Light.CameraPos.xyz;
 
			////���o�_���������f�I��?
   //         float distance = length(DiffuseDir);
 
			////���o��?���q
   //         float atten1 = 0.5f;
   //         float atten2 = 0.1f;
   //         float atten3 = 0.0f;
   //         float LightIntensity = 1.0f / (atten1 + atten2 * distance);
 
			////�������ˌ��I������
   //         float3 InvseDiffuseDir = -DiffuseDir;
 
			////���o�����ˈ��q[0.0,1.0]
   //         DiffuseFactor = saturate(dot(InvseDiffuseDir, In.inNormal.xyz));
		
          
			////���o���ˌ�
   //         DiffuseLight = LightIntensity;
 
			////?�F���㖟���ˌ�
   //         color += DiffuseLight;
		
   //         color = saturate(color);
 
        }
        else
        {
            if (ShadowMapDepth < In.LightPos.z - 0.01 /*�o�C�A�X*/)
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
