#include "main.h"
#include "CStaticmodle.h"


CStaticmodle::CStaticmodle(std::string modelpath, int num)
{
	this->Load(modelpath,num);
}

CStaticmodle::~CStaticmodle()
{
	meshes.clear();
}

void CStaticmodle::Load(std::string path,int num)
{
	Assimp::Importer importer;
	const aiScene* ai_Scene;
	ai_Scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_FlipUVs);
	if (ai_Scene == nullptr)
	{
		MessageBox(0, "Modelload  - Failed",
			"Error", MB_OK);
		return;
	}



	this->ProcessNode(ai_Scene->mRootNode, ai_Scene,num);
	//setboxV
	MeshPart* meshpart = new MeshPart[meshes.size()];
	for (int index = 0; index < meshes.size(); index++)
	{
		meshes[index]->vertexBuffer = CVertexBuffer<VERTEX_3D>::CreatVertexBuffer(meshes[index]->vs.data(), meshes[index]->vs.size());
		meshes[index]->indexBuffer = CIndexBuffer<DWORD>::CreatIndexBuffer(NULL, meshes[index]->indices.data(), meshes[index]->indices.size());

		//getboxVertex
		meshpart[index].m_BoxPoint.Vmax = meshes[index]->vs[0].Position;
		meshpart[index].m_BoxPoint.Vmin = meshes[index]->vs[0].Position;
		for (UINT g = 0; g < meshes[index]->vs.size(); g++)
		{
			XMFLOAT3 meshPos = meshes[index]->vs[g].Position;
			meshpart[index].m_BoxPoint.Vmax = Tool::GET_MAX_VERTEX3(meshPos, meshpart[index].m_BoxPoint.Vmax);
			meshpart[index].m_BoxPoint.Vmin = Tool::GET_MIN_VERTEX3(meshPos, meshpart[index].m_BoxPoint.Vmin);
		}
		V_m_meshPart.push_back(meshpart[index]);
	}
}

void CStaticmodle::Update()
{
}

std::vector<MeshPart> CStaticmodle::m_GetBoxPinots()
{
	return V_m_meshPart;
}

std::vector<Material> CStaticmodle::MaterialTexture(const aiScene * scene, aiMaterial * material,int num)
{
	std::vector<Material> GetMaterial;
	UINT TextureGrainCount = material->GetTextureCount(aiTextureType_DIFFUSE);
	if (TextureGrainCount == 0)
	{
		aiColor3D aicolor;
		material->Get(AI_MATKEY_COLOR_DIFFUSE, aicolor);
		if (aicolor.IsBlack())
		{
			GetMaterial.push_back(Material(&MaterialColor(100, 100, 100, 255), 1, 1));
			return GetMaterial;
		}
		GetMaterial.push_back(Material(&MaterialColor(aicolor.r * 255, aicolor.b * 255, aicolor.g * 255, 255), 1, 1));
		return GetMaterial;
	}
	else
	{
		for (UINT index = 0; index < TextureGrainCount; index++)
		{
			aiString path;
			material->GetTexture(aiTextureType_DIFFUSE, index, &path);//ｴﾓｲﾄﾖﾊｻ｡ﾌﾘｶｨｵﾄｲﾎﾊ
			std::string modelpath;
			modelpath = path.data;
			size_t Pos = modelpath.find_last_of("\\/");
			std::string texName = modelpath.substr(Pos + 1, modelpath.size() - Pos);
			if(num==0)
				GetMaterial.push_back(Material(texName));
			else if(num ==1)
				GetMaterial.push_back(Material(texName, 3.0f));
			//GetMaterial.push_back(Material(texName,num));
		}
		return GetMaterial;
	}
}

void CStaticmodle::Render(XMMATRIX worldMatrix)
{

	CRenderer::SetWorldMatrix(&worldMatrix);
	CRenderer::SetShadowTex(1);
	for (int index = 0; index < meshes.size(); index++)
	{
		for (int tex = 0; tex < meshes[index]->material.size(); tex++)
		{
			CRenderer::SetTexture2(meshes[index]->material[tex].GetMaterial());
		}
		CVertexBuffer<VERTEX_3D>::SetVertexBuffer(meshes[index]->vertexBuffer);
		CIndexBuffer<DWORD>::SetIndexBuffer(meshes[index]->indexBuffer);
		CIndexBuffer<DWORD>::DRAW_TOPOLOGY_TRIANGLELIST(meshes[index]->indices.size());
	}
}

void CStaticmodle::RenderWeaPon(XMMATRIX worldMatrix, XMFLOAT4X4 Bonematrix)
{
	CRenderer::SetWorldMatrix(&worldMatrix);
	CRenderer::WeaponBoneBegin();
	CRenderer::SetWeponBone(Bonematrix);
	for (int index = 0; index < meshes.size(); index++)
	{
		for (int tex = 0; tex < meshes[index]->material.size(); tex++)
		{
			CRenderer::SetTexture2(meshes[index]->material[tex].GetMaterial());
		}
		CVertexBuffer<VERTEX_3D>::SetVertexBuffer(meshes[index]->vertexBuffer);
		CIndexBuffer<DWORD>::SetIndexBuffer(meshes[index]->indexBuffer);
		CIndexBuffer<DWORD>::DRAW_TOPOLOGY_TRIANGLELIST(meshes[index]->indices.size());
	}

	CRenderer::WeaponBoneBack();
}

void CStaticmodle::RenderTranspose(XMMATRIX worldMatrix)
{
	CRenderer::SetWorldMatrixTranspose(&worldMatrix);
	for (int index = 0; index < meshes.size(); index++)
	{
		for (int tex = 0; tex < meshes[index]->material.size(); tex++)
		{
			CRenderer::SetTexture2(meshes[index]->material[tex].GetMaterial());
		}
		CVertexBuffer<VERTEX_3D>::SetVertexBuffer(meshes[index]->vertexBuffer);
		CIndexBuffer<DWORD>::SetIndexBuffer(meshes[index]->indexBuffer);
		CIndexBuffer<DWORD>::DRAW_TOPOLOGY_TRIANGLELIST(meshes[index]->indices.size());
	}
}

void CStaticmodle::ProcessNode(aiNode* node, const aiScene* ai_Scene,int num)
{
	for (UINT index = 0; index < node->mNumMeshes; index++)
	{
		aiMesh* mesh = ai_Scene->mMeshes[node->mMeshes[index]];
		meshes.push_back(this->ProcessMesh(mesh, ai_Scene,num));
	}

	for (UINT index = 0; index < node->mNumChildren; index++)
	{
		//MeshPart* m_Boxvs = new MeshPart[node->mNumChildren];
		/*aiNode* momnode = node->mChildren[index];
		for (int i = 0;i < momnode->mNumMeshes; i++)
		{
			MeshPart* m_Boxvs = new MeshPart[momnode->mNumMeshes];
			aiMesh* mesh = ai_Scene->mMeshes[momnode->mMeshes[i]];
			BoxVertex.push_back(m_Boxvs[index]);
		}*/
		//BoxVertex.push_back(m_Boxvs[index]);
		this->ProcessNode(node->mChildren[index], ai_Scene,num);

	}
}

SStaticMode* CStaticmodle::ProcessMesh(aiMesh* mesh,const aiScene *ai_Scene,int num)
{
	SStaticMode* skinnedMesh = new SStaticMode;

	//Getting Vertex
	for (UINT index = 0; index < mesh->mNumVertices; index++)
	{
		//jingzhi
		VERTEX_3D Vertex;
		Vertex.Position = XMFLOAT3(mesh->mVertices[index].x, mesh->mVertices[index].y, mesh->mVertices[index].z);
		if (mesh->mNormals != nullptr)
			Vertex.Normal = XMFLOAT3(mesh->mNormals[index].x, mesh->mNormals[index].y, mesh->mNormals[index].z);
		Vertex.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		if (mesh->mTextureCoords[0])
			Vertex.TexCoord = XMFLOAT2((float)mesh->mTextureCoords[0][index].x, (float)mesh->mTextureCoords[0][index].y);
		skinnedMesh->vs.push_back(Vertex);
	}

	//Getting Index
	for (UINT index = 0; index < mesh->mNumFaces; index++)
	{
		aiFace ai_Face = mesh->mFaces[index];

		for (UINT count = 0; count < ai_Face.mNumIndices; count++)
		{
			skinnedMesh->indices.push_back(ai_Face.mIndices[count]);
		}
	}


	//aimaterial
	aiMaterial* material = ai_Scene->mMaterials[mesh->mMaterialIndex];//ﾒｻｸｻﾓﾐﾒｻｸｸﾏﾄﾖﾊｵﾄﾋ｣ｻ/阿瑟东
	skinnedMesh->material = this->MaterialTexture(ai_Scene, material,num);

	//Getting Bones Data
	return skinnedMesh;
}










