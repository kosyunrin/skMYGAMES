#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Collision;

struct Mesh
{
	std::vector<Vertex> vertices;
	std::vector<DWORD> indices;
	std::vector<Texture> textures;

	ComPtr<ID3D11Buffer> vertexBuffer;
	ComPtr<ID3D11Buffer> indexBuffer;

	XMMATRIX meshMatrix;
	XMMATRIX worldMatrix;
};

class Model
{
private:
	std::vector<Mesh> meshes;

	std::string modelpath;

	void Load(std::string modelpath);
	void ProcessNode(const aiScene* scene, aiNode* node, const XMMATRIX parentMatrix);
	Mesh ProcessMesh(const aiScene* scene, aiMesh* mesh, const XMMATRIX transformMatrix);
	std::vector<Texture> ProcessMaterialTextures(aiMaterial* material);

public:
	Model(std::string modelpath);
	~Model();

	void Render(XMMATRIX worldMatrix);
	void Render(std::vector<Collision*> collisions, XMMATRIX worldMatrix);

	std::vector<Mesh> GetMeshes() { return meshes; }

/*--------------------------------------------------------------------------------
Collision
--------------------------------------------------------------------------------*/
private:
	std::vector<Collision*> myCollisions;
public:
	std::vector<Collision*> GetMyCollisions() { return myCollisions; }
};
