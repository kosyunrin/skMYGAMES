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

struct PointLightSettings
{
    bool Enable;
    float3 Position;
    float4 Diffuse;
    float4 Ambient;
    float4 Attenuation;
    float DiffuseStrength;
    float AmbientStrength;
    float Range;
    float Empty;
};

cbuffer PointLightBuffer : register(b1)
{
    PointLightSettings pointLights[PLMAX];
}

struct SpotLightSettings
{
    bool Enable;
    float3 Position;
    float4 Direction;
    float4 Diffuse;
    float4 Ambient;
    float4 Attenuation;
    float DiffuseStrength;
    float AmbientStrength;
    float Range;
    float Cutoff;
};

cbuffer SpotLightBuffer : register(b2)
{
    SpotLightSettings spotLights[SLMAX];
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

float3 GetBumpNormal(PS_INPUT input, float3 textureNormal);

//Directional Light
float4 GetDirectionalIntensity(PS_INPUT input, float4 textureDiffuse);
//Point Light
float4 GetPointIntensity(PS_INPUT input, float4 textureDiffuse);
//Spot Light
float4 GetSpotIntensity(PS_INPUT input, float4 textureDiffuse);

float4 main(PS_INPUT input) : SV_TARGET
{
    float4 textureDiffuse = g_TextureDiffuse.Sample(g_WrapSamplerState, input.inTexCoord);

    //Initialize final as ambient light
    float4 final = directionLights.Ambient * textureDiffuse;
    
    float4 DL = GetDirectionalIntensity(input, textureDiffuse);
    float4 PL = GetPointIntensity(input, textureDiffuse);
    float4 SL = GetSpotIntensity(input, textureDiffuse);
    
    final += DL;
    
    /*--------------------------------------------------------------------------------
    Shadow
    --------------------------------------------------------------------------------*/
    float2 shadowTexCoord;
    shadowTexCoord.x = input.inDepthPosition.x / input.inDepthPosition.w / 2.0 + 0.5;
    shadowTexCoord.y = -input.inDepthPosition.y / input.inDepthPosition.w / 2.0 + 0.5;

    float4 shadowColor = g_TextureShadow.Sample(g_ClampSamplerState, shadowTexCoord);
    final = final * shadowColor;
    
    final += PL;
    final += SL;
        
    return final;
}



/*--------------------------------------------------------------------------------
Directional Light
--------------------------------------------------------------------------------*/
float4 GetDirectionalIntensity(PS_INPUT input, float4 textureDiffuse)
{
    float4 final = float4(0.0, 0.0, 0.0, 1.0);

    float intensity = saturate(dot(-directionLights.Direction.xyz, input.inNormal));
    final += intensity * directionLights.Diffuse * textureDiffuse;

    return final;
}


/*--------------------------------------------------------------------------------
Point Light
--------------------------------------------------------------------------------*/
float4 GetPointIntensity(PS_INPUT input, float4 textureDiffuse)
{
    float4 final = float4(0.0, 0.0, 0.0, 1.0);

    for (int index = 0; index < PLMAX; index++)
    {
        //Calculate the pixel to light position's vector
        float3 LightToPixel = pointLights[index].Position.xyz - input.inPositionW;
        //Calculate the distance
        float d = length(LightToPixel);

        if (d < pointLights[index].Range)
        {
            LightToPixel = normalize(LightToPixel);
            
            float intensity = saturate(dot(LightToPixel, input.inNormal));
            
            float4 diffuseColor = pointLights[index].Diffuse * pointLights[index].DiffuseStrength;
            diffuseColor /= (pointLights[index].Attenuation.x + (pointLights[index].Attenuation.y * d) + (pointLights[index].Attenuation.z * d * d));
            
            final += intensity * diffuseColor * textureDiffuse;
        }
    }
    return final;
}

/*--------------------------------------------------------------------------------
Spot Light
--------------------------------------------------------------------------------*/
float4 GetSpotIntensity(PS_INPUT input, float4 textureDiffuse)
{
    float4 final = float4(0.0, 0.0, 0.0, 1.0);

    for (int index = 0; index < SLMAX; index++)
    {
        //Calculate the pixel to light position's vector
        float3 LightToPixel = spotLights[index].Position.xyz - input.inPositionW;
        //Calculate the distance
        float d = length(LightToPixel);
        
        float theta = dot(normalize(LightToPixel), normalize(-spotLights[index].Direction.xyz));
        float epsilon = 0.05;
        float intensity = clamp((theta - spotLights[index].Cutoff - 0.05) / epsilon, 0.0, 1.0);
        
        float4 diffuseColor = spotLights[index].Diffuse * spotLights[index].DiffuseStrength * saturate(dot(normalize(LightToPixel), input.inNormal));
        diffuseColor /= (spotLights[index].Attenuation.x + (spotLights[index].Attenuation.y * d) + (spotLights[index].Attenuation.z * d * d));
        
        final += intensity * diffuseColor * textureDiffuse;
    }
    return final;
}