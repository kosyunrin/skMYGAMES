

//*****************************************************************************
// �萔�o�b�t�@
//*****************************************************************************

// �}�g���N�X�o�b�t�@
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

// �}�e���A���o�b�t�@
struct MATERIAL
{
	float4		Ambient;
	float4		Diffuse;
	float4		Specular;
	float4		Emission;
	float		Shininess;
	float3		Dummy;//16bit���E�p
};

cbuffer MaterialBuffer : register(b3)
{
	MATERIAL	Material;
}


// ���C�g�o�b�t�@
struct LIGHT
{
	float4		Direction;
	float4		Diffuse;
	float4		Ambient;
};
struct FINALMATRIX
{
	matrix		FMatrix[256];
};

cbuffer LightBuffer : register(b4)
{
	LIGHT		Light;
}
cbuffer CBBoneTranform : register(b5)
{
	FINALMATRIX			Finalmatrix;
}



//=============================================================================
// ���_�V�F�[�_
//=============================================================================
void main(in  float4 inPosition		: POSITION0,
						in  float4 inNormal : NORMAL0,
						in  float4 inDiffuse : COLOR0,
						in  float2 inTexCoord : TEXCOORD0,
						in  uint4 inBoneID : BONEID0,
						in  float4 inBoneWeight : BONEWEIGHT0,

						out float4 outPosition : SV_POSITION,
						out float4 outNormal : NORMAL0,
						out float2 outTexCoord : TEXCOORD0,
						out float4 outDiffuse : COLOR0)
{
	inPosition =	inBoneWeight[0]* mul(inPosition, Finalmatrix.FMatrix[inBoneID[0]])+
					inBoneWeight[1] * mul(inPosition, Finalmatrix.FMatrix[inBoneID[1]])+
					inBoneWeight[2] * mul(inPosition, Finalmatrix.FMatrix[inBoneID[2]])+
					inBoneWeight[3] * mul(inPosition, Finalmatrix.FMatrix[inBoneID[3]]);

	inNormal= inBoneWeight[0] * mul(inNormal, Finalmatrix.FMatrix[inBoneID[0]]) +
			  inBoneWeight[1] * mul(inNormal, Finalmatrix.FMatrix[inBoneID[1]]) +
			  inBoneWeight[2] * mul(inNormal, Finalmatrix.FMatrix[inBoneID[2]]) +
			  inBoneWeight[3] * mul(inNormal, Finalmatrix.FMatrix[inBoneID[3]]);
	
	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);

	outPosition = mul(inPosition, wvp);
	outNormal = inNormal;
	outTexCoord = inTexCoord;

	float4 worldNormal, normal;
	normal = float4(inNormal.xyz, 0.0);
	worldNormal = mul(normal, World);
	worldNormal = normalize(worldNormal);

	float light = 0.5 - 0.5 * dot(Light.Direction.xyz, worldNormal.xyz);

	outDiffuse = inDiffuse * Material.Diffuse * light * Light.Diffuse;
	outDiffuse += inDiffuse * Material.Ambient * Light.Ambient;
	//outDiffuse.a = 1.0;
	outDiffuse.a = inDiffuse.a*Material.Diffuse.a;

}

