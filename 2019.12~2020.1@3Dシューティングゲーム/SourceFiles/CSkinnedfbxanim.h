#pragma once
#include<map>
class CSkinnedfbxanim
{
private:
	//Assimp::Importer importer;
	// Assimp::Importer  sdsd;
	//const aiScene* ai_Scene;
	XMFLOAT4X4 WeaPonMatrix;
	const aiScene* ai_Scenes[16];
	Assimp::Importer importers[16];
	std::vector<SkinnedMesh*> meshes;

	std::vector<BoneMatrix> bonesMatrix;
	std::map<std::string, UINT> bonesMap;
	UINT bonesCount;
	XMFLOAT4X4 GlobalInversef;
	//XMMATRIX GlobalInverse;

	std::vector<XMFLOAT4X4> currentBonesTransform;
	std::vector<XMFLOAT4X4> Framlocalworldmatrix;
	std::vector<XMFLOAT4X4> nextBonesTransform;

	UINT currentAnimation;
	UINT nextAnimation;

	float animTime1;
	float animTime2;
	float blendTime;
	void Load(SFbxanimtype t[], int animCount);
	void ProcessNode(aiNode* node);
	SkinnedMesh* ProcessMesh(aiMesh* mesh);
	//	std::vector<CTexture> ProcessMaterialTextures(aiMaterial* material);
	void BoneTransform(std::vector<XMFLOAT4X4>& transform);
	void InstanceBoneUpdate();
	void ReadNodeHeirarchy(const aiNode* node, const XMMATRIX parentTransform, float time, UINT action, const aiAnimation* animation);
	void ReadNodeHeirarchy(const aiNode* node1, const aiNode* node2, const XMMATRIX parentTransform, float time1, float time2, UINT action1, UINT action2, const aiAnimation* animation, const aiAnimation* animation1s);

	const aiNodeAnim* FindNodeAnim(const aiAnimation* animation, const std::string nodeName);

	aiVector3D interpolatePosition(float time, const aiNodeAnim* anim);
	aiQuaternion interpolateRotation(float time, const aiNodeAnim* anim);
	aiVector3D interpolateScaling(float time, const aiNodeAnim* anim);

	UINT findPosition(float time, const aiNodeAnim* anim);
	UINT findRotation(float time, const aiNodeAnim* anim);
	UINT findScaling(float time, const aiNodeAnim* anim);

public:
	CSkinnedfbxanim(SFbxanimtype t[],int animCount);
	~CSkinnedfbxanim();

	void Update(float dt, float speed);
	void InstanceUpdate(float dt, float speed);
	void Render(XMMATRIX worldMatrix, UINT animation);
	void Render(XMMATRIX worldMatrix, XMMATRIX &outworldMatrix, int num, UINT animation);
	void Render(XMMATRIX worldMatrix, XMMATRIX worldMatrix2, UINT animation);
	void RenderGotimer(XMMATRIX worldMatrix, UINT animation);
	void RenderInstance(XMFLOAT4X4 world[], UINT animation);
	void InsSetIntoAnim(int instanceID, int animtionx) { RunAnimatiom[instanceID] = animtionx; }
	void ResetTimer();
	void SetInitanimation(int nextanim) { currentAnimation = nextanim; }
	void Insanimation(int animtionx);
	std::vector<MeshPart> m_GetBoxPinots();


	std::vector<SkinnedMesh*> GetSkinnedMesh() { return meshes; }
private:
	std::vector<Material> MaterialTexture(const aiScene* scene, aiMaterial* material);
	std::vector<MeshPart> V_m_meshPart;
	void ai_Scenesload( SFbxanimtype t[], int animCount);
	void SetInstanceBoneMatrix(std::vector<XMFLOAT4X4>& transform);
	void SetInsWorldBuffer(XMFLOAT4X4 world[]);
	bool animShow;
public:
	//animfram
	bool AiamFramManager(float FramCount,int currentanim);
	bool AiamFramManager2(float FramCount, int currentanim);
	bool PlayShot();
	bool PlyaerOne(float FramCount, int currentanim,bool& isboolx);
	bool PlayerOnce(float FramCount, int currentanim, bool& isboolx);
	bool AnimShow(float framcount, int currentanim);
	INSTANCEBUFFER* GetInsBuffer();
private:
	float NextAimCurrentFrama;
	float NextAimCurrentFrama2;
	//Instance”√
	INSTANCEBUFFER Insanim[INSTANCEMAX];
	float InsanimTime[INSTANCEMAX];
	float InsanimaTime2[INSTANCEMAX];
	float Insblend[INSTANCEMAX];
	int InscurrentAnimation[INSTANCEMAX];
	int InsnextAnimation[INSTANCEMAX];
	int RunAnimatiom[INSTANCEMAX];
public:
	void CpuPosUpdate();
	void AddPartMeshes(std::vector<SStaticMode*> partmesh);

	XMMATRIX GetBonesTransform(int index) 
	{
		XMFLOAT4X4 bone = currentBonesTransform[index];

	/*	bone._41 = 1.0f;
		bone._42 = 1.0f;
		bone._43 = 1.0f;*/
		

		bone._11 = 1.0f;
		bone._22 = 1.0f;
		bone._33 = 1.0f;
		return XMLoadFloat4x4(&bone);
	}
	XMVECTOR GetBonesTransformPos(int index)
	{
		XMFLOAT4X4 bone =  currentBonesTransform[index];
		XMMATRIX bonexm = XMMatrixTranspose( XMLoadFloat4x4(&bone));
		XMStoreFloat4x4(&bone, bonexm);
		
		XMFLOAT3  pos= { bone._41,bone._42,bone._43 };

		return XMLoadFloat3(&pos);
	}
	XMMATRIX GetFramLocalWorldMatrix(int num)
	{
		XMFLOAT4X4 bone = Framlocalworldmatrix[num];
		//bone._11 = 1.0f;
		//bone._22 = 1.0f;
		//bone._33 = 1.0f;
		//bone._44 = 1.0f;
		return XMLoadFloat4x4(&bone);
	}
	XMFLOAT4X4 GetFramLocalWorldMatrixfloat(int num)
	{
		XMFLOAT4X4 bone = Framlocalworldmatrix[num];
		bone._11 = 1.0f;
		bone._22 = 1.0f;
		bone._33 = 1.0f;
		return bone;
	}
	XMFLOAT3 GetFramLocalWorldMatrixPOS(int num)
	{
		XMFLOAT4X4 bone = Framlocalworldmatrix[num];
		XMMATRIX bonexm = XMMatrixTranspose(XMLoadFloat4x4(&bone));
		XMStoreFloat4x4(&bone, bonexm);

		XMFLOAT3  pos = { bone._41,bone._42,bone._43 };
		return pos;
	}
	void SetWeaponLocalMatrix(XMMATRIX WeaPonLocalMatrix)
	{
		XMStoreFloat4x4(&WeaPonMatrix, WeaPonLocalMatrix);
	}
	//weapon
	void WeaponRender(XMMATRIX worldMatrix, UINT animation);
private:
	void WeaponBoneTransform(std::vector<XMFLOAT4X4>& transform);
	void WeaponReadNodeHeirarchy(const aiNode* node, const XMMATRIX parentTransform, float time, UINT action, const aiAnimation* animation);
	void WeaponReadNodeHeirarchy(const aiNode* node1, const aiNode* node2, const XMMATRIX parentTransform, float time1, float time2, UINT action1, UINT action2, const aiAnimation* animation, const aiAnimation* animation1s);

};

