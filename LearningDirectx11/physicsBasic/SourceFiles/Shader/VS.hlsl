cbuffer WorldBuffer : register(b0)
{
    matrix World;
}
cbuffer ViewBuffer : register(b1)
{
    matrix View;
}
cbuffer ProjectionBuffer : register(b2)
{
    matrix Projection;
}

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

cbuffer DirectionLightBuffer : register(b3)
{
    DirectionLightSettings directionLights;
};

cbuffer CameraBuffer : register(b4)
{
    float4 CameraPos;
}

cbuffer ReflectionBuffer : register(b5)
{
    matrix Reflection;
}

struct VS_INPUT
{
    uint inInstanceID : SV_INSTANCEID;
    float3 inPosition : POSITION;
    float2 inTexCoord : TEXCOORD;
    float3 inNormal : NORMAL;
    float3 inTangent : TANGENT;
    float3 inBitangent : BITANGENT;
};

struct VS_OUTPUT
{
    float4 outPosition : SV_POSITION;
    float3 outPositionW : POSITIONW;
    float4 outDepthPosition : DEPTHPOSITION;
    float3 outNormal : NORMAL;
    float2 outTexCoord : TEXCORRD;
    float3 outTangent : TANGENT;
    float3 outBitangent : BITANGENT;
    float3 outViewDirection : VIEWDIRECTION;
    float4 outReflectPosition : REFLECTTEXCORRD;
    float4 outLightViewPosition : LIGHTDIRECTION;
    float3 outLightPosition : LIGHTPOSITION;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;

    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);

    output.outPosition = mul(float4(input.inPosition, 1.0), wvp);
    output.outPositionW = mul(float4(input.inPosition, 1.0), World);

    output.outDepthPosition = output.outPosition;

    output.outNormal = normalize(mul(float4(input.inNormal, 0.0), World));

    output.outTexCoord = input.inTexCoord;

    //Normal Map
    output.outTangent = normalize(mul(float4(input.inTangent, 0.0), World));
    output.outBitangent = normalize(mul(float4(input.inBitangent, 0.0), World));
    
    //Specular Map
    output.outViewDirection = normalize(CameraPos.xyz - output.outPositionW.xyz);

    //Reflect Map
    matrix reflectionMatrix;
    reflectionMatrix = mul(Reflection, Projection);
    reflectionMatrix = mul(World, reflectionMatrix);
    output.outReflectPosition = mul(float4(input.inPosition, 1.0), reflectionMatrix);

    //Light Map
    output.outLightViewPosition = mul(float4(input.inPosition, 1.0), World);
    output.outLightViewPosition = mul(output.outLightViewPosition, directionLights.ViewTransMatrix);
    output.outLightViewPosition = mul(output.outLightViewPosition, directionLights.ProjectionTransMatrix);

    output.outLightPosition = normalize(directionLights.Position - output.outPositionW.xyz);
    
    return output;
}

