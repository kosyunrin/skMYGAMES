#pragma once
#include<map>

class SkinnedModel
{
private:
	 Assimp::Importer importer;
	// Assimp::Importer  sdsd;
	const aiScene* ai_Scene;
	std::string modelpath;

	std::vector<SkinnedMesh*> meshes;

	std::vector<BoneMatrix> bonesMatrix;
	std::map<std::string, UINT> bonesMap;
	UINT bonesCount;
	XMFLOAT4X4 GlobalInversef;
	//XMMATRIX GlobalInverse;

	std::vector<XMFLOAT4X4> currentBonesTransform;
	std::vector<XMFLOAT4X4> nextBonesTransform;

	UINT currentAnimation;
	UINT nextAnimation;

	float animTime1;
	float animTime2;
	float blendTime;

	void Load(std::string modelpath);
	void ProcessNode(aiNode* node);
	SkinnedMesh* ProcessMesh(aiMesh* mesh);
//	std::vector<CTexture> ProcessMaterialTextures(aiMaterial* material);

	void BoneTransform(std::vector<XMFLOAT4X4>& transform);
	void ReadNodeHeirarchy(const aiNode* node, const XMMATRIX parentTransform, float time, UINT action);
	void ReadNodeHeirarchy(const aiNode* node1, const aiNode* node2, const XMMATRIX parentTransform, float time1, float time2, UINT action1, UINT action2);

	const aiNodeAnim* FindNodeAnim(const aiAnimation* animation, const std::string nodeName);

	aiVector3D interpolatePosition(float time, const aiNodeAnim* anim);
	aiQuaternion interpolateRotation(float time, const aiNodeAnim* anim);
	aiVector3D interpolateScaling(float time, const aiNodeAnim* anim);

	UINT findPosition(float time, const aiNodeAnim* anim);
	UINT findRotation(float time, const aiNodeAnim* anim);
	UINT findScaling(float time, const aiNodeAnim* anim);

public:
	SkinnedModel(std::string modelpath);
	~SkinnedModel();

	void Update();
	void Render(XMMATRIX worldMatrix, UINT animation);

	void ResetTimer();
	void SetInitanimation(int nextanim) { currentAnimation = nextanim; }
	std::vector<MeshPart> m_GetBoxPinots();


	std::vector<SkinnedMesh*> GetSkinnedMesh() { return meshes; }
private:
	std::vector<Material> MaterialTexture(const aiScene* scene, aiMaterial* material);
	std::vector<MeshPart> V_m_meshPart;

};
