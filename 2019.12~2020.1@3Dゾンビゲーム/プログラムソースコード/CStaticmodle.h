#pragma once
#include<map>
//#include"CAx.h"
class CStaticmodle
{
private:

	std::vector<SStaticMode*> meshes;


	void Load(std::string modelpath, int num);
	void ProcessNode(aiNode* node, const aiScene *ai_Scene,int num);
	SStaticMode* ProcessMesh(aiMesh* mesh, const aiScene *ai_Scene ,int num);

public:
	CStaticmodle(std::string modelpath,int num);
	~CStaticmodle();

	void Update();
	void Render(XMMATRIX worldMatrix);
	void RenderWeaPon(XMMATRIX worldMatrix,XMFLOAT4X4 Bonematrix);
	void RenderTranspose(XMMATRIX worldMatrix);

	std::vector<MeshPart> m_GetBoxPinots();
	std::vector<SStaticMode*> GetSkinnedMesh() { return meshes; }
private:
	std::vector<Material> MaterialTexture(const aiScene* scene, aiMaterial* material,int num);
	std::vector<MeshPart> V_m_meshPart;
	std::vector<MeshPart> BoxVertex;

};

