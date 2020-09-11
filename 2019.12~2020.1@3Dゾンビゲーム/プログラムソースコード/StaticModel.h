#pragma once
#include<map>

class StaticModel
{
private:
	std::vector<MODEL_ASSIMP> meshes;
	std::vector<MeshPart> V_m_meshPart;



public:


	void DrawAny();

public:
	void LoadAny(const char* FileName);
	void StarNodeo(const aiScene* scene, aiNode* Node);
	void UnloadAssimp();
	std::vector<MeshPart> m_GetBoxPinots();
private:
	MODEL_ASSIMP AssimpLoadMesh(const aiScene* scene, aiMesh* mesh);
	std::vector<Material> MaterialTexture(const aiScene* scene, aiMaterial* material);
	std::string modelpath;
	const aiScene* Scene;
	Assimp::Importer m_Importer;
};