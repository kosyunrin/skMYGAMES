

#include "main.h"
#include "StaticModel.h"



void StaticModel::DrawAny()
{
	//CRenderer::BoneSL();
	for (int i = 0; i < meshes.size(); i++)
	{
		for (int tex = 0; tex < meshes[i].material.size(); tex++)
		{
			CRenderer::SetTexture2(meshes[i].material[tex].GetMaterial());
		}
		/*CRenderer::SetVertexBuffers(meshes[i].m_VertexBuffer);
		CRenderer::SetIndexBuffer(meshes[i].m_IndexBuffer);
		CRenderer::DrawIndexed(meshes[i].indexNum.size(), 0, 0);*/
		CVertexBuffer<VERTEX_3D>::SetVertexBuffer(meshes[i].m_VertexBuffer);
		CIndexBuffer<WORD>::SetIndexBuffer(meshes[i].m_IndexBuffer);
		CIndexBuffer<WORD>::DRAW_TOPOLOGY_TRIANGLELIST(meshes[i].indexNum.size());
	}
	//CRenderer::BoneBack();

}

void StaticModel::LoadAny(const char * FileName)
{
	Scene = m_Importer.ReadFile(FileName, aiProcess_CalcTangentSpace | //ﾗﾔｶｯｼﾆﾋ翩ﾐﾏﾟｺﾍｷｨﾏﾟ
		aiProcess_Triangulate |//ﾗﾔｶｯﾋﾄｱﾟﾐﾎﾗｪｻｻﾎｪﾈｽﾇﾐﾎ
		aiProcess_JoinIdenticalVertices | //ｺﾏｲ｢ﾏ猩ｬｵﾄｶ･ｵ・
		aiProcess_ConvertToLeftHanded);
	if (Scene == nullptr)
	{
		MessageBox(0, "Modelload  - Failed",
			"Error", MB_OK);
		return;

	}
	this->StarNodeo(Scene, Scene->mRootNode);
	//new
	MeshPart* meshpart = new MeshPart[meshes.size()];

	for (int i = 0; i < meshes.size(); i++)
	{
		meshpart[i].m_BoxPoint.Vmax = meshes[i].vetexNum[0].Position;
		meshpart[i].m_BoxPoint.Vmin = meshes[i].vetexNum[0].Position;
		for (UINT g = 0; g < meshes[i].vetexNum.size(); g++)
		{
			XMFLOAT3 meshPos = meshes[i].vetexNum[g].Position;
			meshpart[i].m_BoxPoint.Vmax = Tool::GET_MAX_VERTEX3(meshPos, meshpart[i].m_BoxPoint.Vmax);
			meshpart[i].m_BoxPoint.Vmin = Tool::GET_MIN_VERTEX3(meshPos, meshpart[i].m_BoxPoint.Vmin);
		}
		V_m_meshPart.push_back(meshpart[i]);
	}
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].m_VertexBuffer = CVertexBuffer<VERTEX_3D>::CreatVertexBuffer(meshes[i].vetexNum.data(), meshes[i].vetexNum.size());
		meshes[i].m_IndexBuffer = CIndexBuffer<WORD>::CreatIndexBuffer(meshes[i].indexNum.data(), NULL, meshes[i].indexNum.size());
	}
}

void StaticModel::StarNodeo(const aiScene * scene, aiNode * Node)//ﾒｻｸﾚｵ耨ﾐNｸeshe｣ｬaisceneｵﾃｵｽｵ･ｸﾄmeshｵﾄｼﾆﾊｵﾈﾓﾚainodeｵﾄｵ･ｸeshｵﾄｼﾆﾊ｣ｻ
{
	for (UINT meshs = 0; meshs < Node->mNumMeshes; meshs++)
	{
		aiMesh* mesh = scene->mMeshes[Node->mMeshes[meshs]];
		meshes.push_back(AssimpLoadMesh(scene, mesh));

	}
	for (UINT i = 0; i < Node->mNumChildren; i++)//ainodeｵﾃｵｽNｸﾓｽﾚｵ羲ﾍｵ･ｸﾄﾗﾓｽﾚｵ罐ｻ
	{
		this->StarNodeo(scene, Node->mChildren[i]);
	}
}

MODEL_ASSIMP StaticModel::AssimpLoadMesh(const aiScene * scene, aiMesh * mesh)
{
	MODEL_ASSIMP fuck;


	for (UINT v = 0; v < mesh->mNumVertices; v++)
	{
		VERTEX_3D Vertex;
		Vertex.Position = XMFLOAT3(mesh->mVertices[v].x, mesh->mVertices[v].y, mesh->mVertices[v].z);
		if (mesh->mNormals != nullptr)
			Vertex.Normal = XMFLOAT3(mesh->mNormals[v].x, mesh->mNormals[v].y, mesh->mNormals[v].z);
		Vertex.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		if (mesh->mTextureCoords[0])
			Vertex.TexCoord = XMFLOAT2((float)mesh->mTextureCoords[0][v].x, (float)mesh->mTextureCoords[0][v].y);
		fuck.vetexNum.push_back(Vertex);
	}

	for (UINT faces = 0; faces < mesh->mNumFaces; faces++)
	{
		aiFace face = mesh->mFaces[faces];
		for (UINT indes = 0; indes < face.mNumIndices; indes++)
		{
			fuck.indexNum.push_back(face.mIndices[indes]);
		}
	}


	//aimaterial
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];//ﾒｻｸｻﾓﾐﾒｻｸｸﾏﾄﾖﾊｵﾄﾋ｣ｻ/阿瑟东
	fuck.material = this->MaterialTexture(scene, material);
	return fuck;
}

std::vector<Material> StaticModel::MaterialTexture(const aiScene * scene, aiMaterial * material)
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
			modelpath = path.data;
			size_t Pos = modelpath.find_last_of("\\/");
			std::string texName = modelpath.substr(Pos + 1, modelpath.size() - Pos);
			GetMaterial.push_back(Material(texName));
		}
		return GetMaterial;
	}
}



void StaticModel::UnloadAssimp()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].m_VertexBuffer->Release();
		meshes[i].m_IndexBuffer->Release();
	}
}

std::vector<MeshPart> StaticModel::m_GetBoxPinots()
{
	return V_m_meshPart;
}



//モデル読込////////////////////////////////////////////




//マテリアル読み込み///////////////////////////////////////////////////////////////////
