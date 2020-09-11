#define InstanceSize 10
#define BONE_MAX 100

struct INSTANCEBUFFER
{
	float4x4  Instanceworld;
	float4x4 BoneMarix[BONE_MAX];
	int4 BoneSwitch;
};
cbuffer ViewBuffer : register(b1)
{
	matrix View;
}
cbuffer ProjectionBuffer : register(b2)
{
	matrix Projection;
}
struct LIGHT
{
    float4 Direction;
    float4 Diffuse;
    float4 Ambient;
};

cbuffer LightBuffer : register(b4)
{
    LIGHT Light;
}

cbuffer BoneTransformBuffer : register(b5)
{
	float4x4 BoneTransform[BONE_MAX];
}

cbuffer InstanceBuffer : register(b6)
{
	float4x4 InstanceW[InstanceSize];
}
cbuffer InstanceBuffer_anim : register(b7)
{
    INSTANCEBUFFER InsAim[InstanceSize];
}


struct VS_INPUT
{
	uint inInstanceID : SV_INSTANCEID;
	float3 inPosition : POSITION;
	float3 inNormal : NORMAL;
	float2 inTexCoord : TEXCOORD;
	uint4 inBoneID : BONEID;
	float4 inBoneWeights : BONEWEIGHT;
};

struct VS_OUTPUT
{
	float4 outPosition : SV_POSITION;
    float4 outWorldPos : POSITION1;
	float3 outNormal : NORMAL;
	float2 outTexCoord : TEXCOORD;
	float4 outDiffuse : COLOR;
};

VS_OUTPUT main(VS_INPUT input)
{
	
    VS_OUTPUT output;
 
    float4x4 World;
    
    for (int i = 0; i <= input.inInstanceID; i++)
    {
        World = InstanceW[i];
    }
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);

    float weights[4];
    weights[0] = input.inBoneWeights[0];
    weights[1] = input.inBoneWeights[1];
    weights[2] = input.inBoneWeights[2];
    weights[3] = 1 - input.inBoneWeights[0] - input.inBoneWeights[1] - input.inBoneWeights[2];

    float4 pos = weights[0] * mul(float4(input.inPosition, 1.0f), BoneTransform[input.inBoneID[0]]);
    pos += weights[1] * mul(float4(input.inPosition, 1.0f), BoneTransform[input.inBoneID[1]]);
    pos += weights[2] * mul(float4(input.inPosition, 1.0f), BoneTransform[input.inBoneID[2]]);
    pos += weights[3] * mul(float4(input.inPosition, 1.0f), BoneTransform[input.inBoneID[3]]);
    pos.w = 1.0f;

    float4 nor = weights[0] * mul(float4(input.inNormal, 0.0f), BoneTransform[input.inBoneID[0]]);
    nor += weights[1] * mul(float4(input.inNormal, 0.0f), BoneTransform[input.inBoneID[1]]);
    nor += weights[2] * mul(float4(input.inNormal, 0.0f), BoneTransform[input.inBoneID[2]]);
    nor += weights[3] * mul(float4(input.inNormal, 0.0f), BoneTransform[input.inBoneID[3]]);
    nor.w = 0.0f;

    output.outPosition = mul(pos, wvp);

    output.outNormal = normalize(mul(nor, World));
    output.outWorldPos = mul(pos, World);
    //output.outDiffuse = float4(1.0f, 1.0f, 1.0f, 1.0f);

    output.outTexCoord = input.inTexCoord;
    
    
    float3 worldNormal;
    worldNormal = output.outNormal;

    float light = 0.5 - 0.5 * dot(Light.Direction.xyz, worldNormal.xyz);

    output.outDiffuse =  light * Light.Diffuse;
    output.outDiffuse += Light.Ambient;
	//outDiffuse.a = 1.0;
    output.outDiffuse.a = 1.0f;

    return output;
}

