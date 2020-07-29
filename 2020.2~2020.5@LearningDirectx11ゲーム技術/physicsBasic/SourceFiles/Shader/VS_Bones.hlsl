#define BONEMAX 100

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

cbuffer BoneTransform : register(b6)
{
    float4x4 BoneTransform[BONEMAX];
}

struct VS_INPUT
{
    uint inInstanceID : SV_INSTANCEID;
    float3 inPosition : POSITION;
    float2 inTexCoord : TEXCOORD;
    float3 inNormal : NORMAL;
    float3 inTangent : TANGENT;
    float3 inBitangent : BITANGENT;
    float4 inBoneWeights : BONEWEIGHTS;
    uint4 inBoneID : BONEID;
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

    float weights[4];
    weights[0] = input.inBoneWeights[0];
    weights[1] = input.inBoneWeights[1];
    weights[2] = input.inBoneWeights[2];
    weights[3] = 1 - weights[0] - weights[1] - weights[2];

    float4 pos = weights[0] * mul(float4(input.inPosition, 1.0), BoneTransform[input.inBoneID[0]]);
    pos += weights[1] * mul(float4(input.inPosition, 1.0), BoneTransform[input.inBoneID[1]]);
    pos += weights[2] * mul(float4(input.inPosition, 1.0), BoneTransform[input.inBoneID[2]]);
    pos += weights[3] * mul(float4(input.inPosition, 1.0), BoneTransform[input.inBoneID[3]]);
    pos.w = 1.0;

    float4 nor = weights[0] * mul(float4(input.inNormal, 0.0), BoneTransform[input.inBoneID[0]]);
    nor += weights[1] * mul(float4(input.inNormal, 0.0), BoneTransform[input.inBoneID[1]]);
    nor += weights[2] * mul(float4(input.inNormal, 0.0), BoneTransform[input.inBoneID[2]]);
    nor += weights[3] * mul(float4(input.inNormal, 0.0), BoneTransform[input.inBoneID[3]]);
    nor.w = 0.0;

    float4 tan = weights[0] * mul(float4(input.inTangent, 0.0), BoneTransform[input.inBoneID[0]]);
    tan += weights[1] * mul(float4(input.inTangent, 0.0), BoneTransform[input.inBoneID[1]]);
    tan += weights[2] * mul(float4(input.inTangent, 0.0), BoneTransform[input.inBoneID[2]]);
    tan += weights[3] * mul(float4(input.inTangent, 0.0), BoneTransform[input.inBoneID[3]]);
    tan.w = 0.0;

    float4 biTan = weights[0] * mul(float4(input.inBitangent, 0.0), BoneTransform[input.inBoneID[0]]);
    biTan += weights[1] * mul(float4(input.inBitangent, 0.0), BoneTransform[input.inBoneID[1]]);
    biTan += weights[2] * mul(float4(input.inBitangent, 0.0), BoneTransform[input.inBoneID[2]]);
    biTan += weights[3] * mul(float4(input.inBitangent, 0.0), BoneTransform[input.inBoneID[3]]);
    biTan.w = 0.0;

    output.outPosition = mul(pos, wvp);
    output.outPositionW = mul(pos, World);
    output.outDepthPosition = output.outPosition;

    output.outNormal = normalize(mul(nor, World));

    output.outTexCoord = input.inTexCoord;

    //Normal Map
    output.outTangent = normalize(mul(tan, World));
    output.outBitangent = normalize(mul(biTan, World));

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

