#define BONE_MAX 100

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
cbuffer BoneTransformBuffer : register(b5)
{
    float4x4 BoneTransform[BONE_MAX];
}




struct VS_INPUT
{
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
    pos.w = 1.0;

    float4 nor = weights[0] * mul(float4(input.inNormal, 0.0f), BoneTransform[input.inBoneID[0]]);
    nor += weights[1] * mul(float4(input.inNormal, 0.0f), BoneTransform[input.inBoneID[1]]);
    nor += weights[2] * mul(float4(input.inNormal, 0.0f), BoneTransform[input.inBoneID[2]]);
    nor += weights[3] * mul(float4(input.inNormal, 0.0f), BoneTransform[input.inBoneID[3]]);
    nor.w = 0.0;

	output.outPosition = mul(pos, wvp);

    output.outNormal = normalize(mul(nor, World));
    output.outWorldPos = mul(pos, World);

	output.outDiffuse = float4(1.0f, 1.0f, 1.0f, 1.0f);

    output.outTexCoord = input.inTexCoord;

    return output;
}

