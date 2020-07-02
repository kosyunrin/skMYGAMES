#pragma once
#define ANIMATIONMAX 15

class Collision;

class MultiSkinnedModel
{
private:
	Assimp::Importer importer[ANIMATIONMAX];
	const aiScene* scene[ANIMATIONMAX];

	std::string modelpath;

	std::vector<SkinnedMesh> meshes;

	std::vector<BoneMatrix> bonesMatrix;
	std::map<std::string, UINT> bonesMap;
	UINT bonesCount;

	XMMATRIX GlobalInverse;

	std::vector<XMFLOAT4X4> bonesTransform;

	UINT currentAnimation;
	UINT lastAnimation;

	float animTime1;
	float animTime2;
	float blendTime;

	bool updateCollision;

	void Load(std::string* modelpath, UINT count);
	void ProcessNode(aiNode* node, const XMMATRIX parentMatrix);
	SkinnedMesh ProcessMesh(aiMesh* mesh, XMMATRIX transformMatrix);
	std::vector<Texture> ProcessMaterialTextures(aiMaterial* material);

	void BoneTransform(const aiScene* scene1, const aiScene* scene2, std::vector<XMFLOAT4X4>& transform);
	void ReadNodeHeirarchy(const aiScene* scene, const aiNode* node, const XMMATRIX parentTransform, float time);
	void ReadNodeHeirarchy(const aiScene* scene1, const aiScene* scene2, const aiNode* node1, const aiNode* node2, const XMMATRIX parentTransform, float time1, float time2);

	const aiNodeAnim* FindNodeAnim(const aiAnimation* animation, const std::string nodeName);

	aiVector3D interpolatePosition(float time, const aiNodeAnim* anim);
	aiQuaternion interpolateRotation(float time, const aiNodeAnim* anim);
	aiVector3D interpolateScaling(float time, const aiNodeAnim* anim);

	UINT findPosition(float time, const aiNodeAnim* anim);
	UINT findRotation(float time, const aiNodeAnim* anim);
	UINT findScaling(float time, const aiNodeAnim* anim);

public:
	MultiSkinnedModel(std::string* modelpath, UINT animCount);
	~MultiSkinnedModel();

	void Update(bool updateCollision);
	void Render(XMMATRIX worldMatrix, UINT ID);
	void Render(std::vector<Collision*> collisions, XMMATRIX worldMatrix, UINT ID);

	void RestrictTextures(std::string* texPath, UINT texCount, UINT meshID);

	void ResetTimer();
	void ReduceTimer(float v);

	std::vector<SkinnedMesh> GetSkinnedMesh() { return meshes; }

/*--------------------------------------------------------------------------------
Collision
--------------------------------------------------------------------------------*/
private:
	std::vector<Collision*> myCollisions;
public:
	std::vector<Collision*> GetMyCollisions() { return myCollisions; }
};

