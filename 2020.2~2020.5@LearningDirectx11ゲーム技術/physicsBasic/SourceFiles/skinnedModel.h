#pragma once
class Collision;

struct SkinnedMesh
{
	std::vector<BonesVertex> vertices;
	std::vector<DWORD> indices;
	std::vector<Texture> textures;

	ComPtr<ID3D11Buffer> vertexBuffer;
	ComPtr<ID3D11Buffer> indexBuffer;
};

struct BoneMatrix
{
	XMMATRIX offsetMatrix;
	XMMATRIX finalMatrix;
};

class SkinnedModel
{
private:
	Assimp::Importer importer;
	const aiScene* scene;

	std::string modelpath;

	std::vector<SkinnedMesh> meshes;

	std::vector<BoneMatrix> bonesMatrix;
	std::map<std::string, UINT> bonesMap;
	UINT bonesCount;

	XMMATRIX GlobalInverse;

	std::vector<XMFLOAT4X4> bonesTransform;

	UINT currentAnimation;
	UINT lastAnimation;
	UINT currentAnimationDuration;
	UINT lastAnimationDuration;

	float animTime1;
	float animTime2;
	float blendTime;

	bool updateCollision;

	void Load(std::string modelpath);
	void ProcessNode(aiNode* node,  const XMMATRIX parentMatrix);
	SkinnedMesh ProcessMesh(aiMesh* mesh,  XMMATRIX transformMatrix);
	std::vector<Texture> ProcessMaterialTextures(aiMaterial* material);

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

	void Update(bool updateCollision);
	void Render(XMMATRIX worldMatrix, UINT animation, UINT duration);
	void Render(std::vector<Collision*> collisions, XMMATRIX worldMatrix, UINT animation, UINT duration);

	void RestrictTextures(std::string* modelpath, UINT texCount, UINT meshID);

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
