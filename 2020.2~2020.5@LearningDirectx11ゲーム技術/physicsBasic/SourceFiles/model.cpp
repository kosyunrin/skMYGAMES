#include "engine.h"
#include "model.h"

Model::Model(std::string modelpath)
{
	this->Load(modelpath);
}

Model::~Model()
{
	meshes.clear();
	myCollisions.clear();
}

void Model::Load(std::string path)
{
	Assimp::Importer importer;
	modelpath = path;

	const aiScene* scene = importer.ReadFile(modelpath, aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_GenSmoothNormals | aiProcess_ConvertToLeftHanded);
	if (scene == nullptr)
	{
		Engine::ErrorMsg("aiScene Create Failed" + path);
		return;
	}

	this->ProcessNode(scene, scene->mRootNode, XMMatrixIdentity());

	/*--------------------------------------------------------------------------------
	Create buffer
	--------------------------------------------------------------------------------*/
	for (int index = 0; index < meshes.size(); index++)
	{
		VertexBuffer<Vertex>::CreateVertexBuffer(meshes[index].vertexBuffer, meshes[index].vertices.data(), meshes[index].vertices.size());
		IndexBuffer::CreateIndexBuffer(meshes[index].indexBuffer, meshes[index].indices.data(), meshes[index].indices.size());
	}

	/*--------------------------------------------------------------------------------
	Create collision
	--------------------------------------------------------------------------------*/
	for (int index = 0; index < meshes.size(); index++)
	{
		Mesh m = meshes[index];

		std::vector<XMFLOAT3> collisionVertices;
		for (int v = 0; v < m.vertices.size(); v++)
			collisionVertices.push_back(Engine::VertexToWorld(m.vertices[v].Position, m.meshMatrix));

		Collision* c = new Collision;
		c->Initialize(collisionVertices, m.indices);
		myCollisions.push_back(c);
	}

	importer.FreeScene();
}

void Model::Render(XMMATRIX worldMatrix)
{
	Shader::SetVSShader(VSShaderID::VS_Basic);

	for (int index = 0; index < meshes.size(); index++)
	{
		for (int tex = 0; tex < meshes[index].textures.size(); tex++)
		{
			switch (meshes[index].textures.size())
			{
				case 1:
					Shader::SetPSShader(PSShaderID::PS_Basic);
					meshes[index].textures[0].SetTexture(TextureMapID::DiffuseMap);
					break;
				case 2:
					Shader::SetPSShader(PSShaderID::PS_Normal);
					meshes[index].textures[0].SetTexture(TextureMapID::DiffuseMap);
					meshes[index].textures[1].SetTexture(TextureMapID::NormalMap);
					break;
				case 3:
					Shader::SetPSShader(PSShaderID::PS_NormalSpecular);
					meshes[index].textures[0].SetTexture(TextureMapID::DiffuseMap);
					meshes[index].textures[1].SetTexture(TextureMapID::NormalMap);
					meshes[index].textures[2].SetTexture(TextureMapID::SpecularMap);
					break;
			}
		}

		VertexBuffer<Vertex>::SetVertexBuffers(meshes[index].vertexBuffer.Get());
		IndexBuffer::SetIndexBuffer(meshes[index].indexBuffer.Get());

		meshes[index].worldMatrix = meshes[index].meshMatrix * worldMatrix;
		ConstantBuffer::SetWorldMatrix(&meshes[index].worldMatrix);
		IndexBuffer::SetTriangleList(meshes[index].indices.size(), 0, 0);
	}
}

void Model::Render(std::vector<Collision*> collisions, XMMATRIX worldMatrix)
{
	Shader::SetVSShader(VSShaderID::VS_Basic);

	for (int index = 0; index < meshes.size(); index++)
	{
		if (Camera::GetVisibility(collisions[index]->GetBoundingBox()->GetMinWorld(), collisions[index]->GetBoundingBox()->GetMaxWorld()));
		{
			for (int tex = 0; tex < meshes[index].textures.size(); tex++)
			{
				switch (meshes[index].textures.size())
				{
				case 1:
					Shader::SetPSShader(PSShaderID::PS_Basic);
					meshes[index].textures[0].SetTexture(TextureMapID::DiffuseMap);
					break;
				case 2:
					Shader::SetPSShader(PSShaderID::PS_Normal);
					meshes[index].textures[0].SetTexture(TextureMapID::DiffuseMap);
					meshes[index].textures[1].SetTexture(TextureMapID::NormalMap);
					break;
				case 3:
					Shader::SetPSShader(PSShaderID::PS_NormalSpecular);
					meshes[index].textures[0].SetTexture(TextureMapID::DiffuseMap);
					meshes[index].textures[1].SetTexture(TextureMapID::NormalMap);
					meshes[index].textures[2].SetTexture(TextureMapID::SpecularMap);
					break;
				}
			}

			VertexBuffer<Vertex>::SetVertexBuffers(meshes[index].vertexBuffer.Get());
			IndexBuffer::SetIndexBuffer(meshes[index].indexBuffer.Get());

			meshes[index].worldMatrix = meshes[index].meshMatrix * worldMatrix;
			ConstantBuffer::SetWorldMatrix(&meshes[index].worldMatrix);
			IndexBuffer::SetTriangleList(meshes[index].indices.size(), 0, 0);
		}
	}
}

void Model::ProcessNode(const aiScene* scene, aiNode* node, const XMMATRIX parentMatrix)
{
	XMMATRIX nodeMatrix = XMMatrixTranspose(XMMATRIX(&node->mTransformation.a1)) * parentMatrix;

	for (UINT index = 0; index < node->mNumMeshes; index++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[index]];
		meshes.push_back(this->ProcessMesh(scene, mesh, nodeMatrix));
	}

	for (UINT index = 0; index < node->mNumChildren; index++)
	{
		this->ProcessNode(scene, node->mChildren[index], nodeMatrix);
	}
}

Mesh Model::ProcessMesh(const aiScene* scene, aiMesh* mesh, const XMMATRIX transformMatrix)
{
	Mesh m;

	/*--------------------------------------------------------------------------------
	Getting vertex
	--------------------------------------------------------------------------------*/
	for (UINT index = 0; index < mesh->mNumVertices; index++)
	{
		Vertex v;
		//Position
		v.Position = XMFLOAT3(mesh->mVertices[index].x, mesh->mVertices[index].y, mesh->mVertices[index].z);
		//Normal
		if (mesh->mNormals != nullptr)
			v.Normal = XMFLOAT3(mesh->mNormals[index].x, mesh->mNormals[index].y, mesh->mNormals[index].z);
		//Texture Coord
		if (mesh->mTextureCoords[0])
			v.TexCoord = XMFLOAT2((float)mesh->mTextureCoords[0][index].x, (float)mesh->mTextureCoords[0][index].y);
		//Tangent
		if(mesh->mTangents != nullptr)
			v.Tangent = XMFLOAT3(mesh->mTangents[index].x, mesh->mTangents[index].y, mesh->mTangents[index].z);
		//BiTangent
		if (mesh->mBitangents != nullptr)
			v.Bitangent = XMFLOAT3(mesh->mBitangents[index].x, mesh->mBitangents[index].y, mesh->mBitangents[index].z);

		m.vertices.push_back(v);
	}

	/*--------------------------------------------------------------------------------
	Getting index
	--------------------------------------------------------------------------------*/
	for (UINT index = 0; index < mesh->mNumFaces; index++)
	{
		aiFace face = mesh->mFaces[index];

		for (UINT count = 0; count < face.mNumIndices; count++)
		{
			m.indices.push_back(face.mIndices[count]);
		}
	}

	/*--------------------------------------------------------------------------------
	Getting material
	--------------------------------------------------------------------------------*/
	aiMaterial* ai_Material = scene->mMaterials[mesh->mMaterialIndex];
	m.textures = this->ProcessMaterialTextures(ai_Material);

	//Matrix
	m.meshMatrix = transformMatrix;

	return m;
}

std::vector<Texture> Model::ProcessMaterialTextures(aiMaterial* material)
{
	std::vector<Texture> textures;
	
	UINT diffuseCount = material->GetTextureCount(aiTextureType_DIFFUSE);
	UINT normalCount = material->GetTextureCount(aiTextureType_HEIGHT);
	UINT specularCount = material->GetTextureCount(aiTextureType_SPECULAR);

	/*--------------------------------------------------------------------------------
	Load Diffuse
	--------------------------------------------------------------------------------*/
	if (diffuseCount == 0)
	{
		aiColor3D aiColor;
		material->Get(AI_MATKEY_COLOR_DIFFUSE, aiColor);
		if (aiColor.IsBlack())
			textures.push_back(Texture(Color(50, 50, 50, 255)));
		else
			textures.push_back(Texture(Color((BYTE)aiColor.r * 255, (BYTE)aiColor.g * 255, (BYTE)aiColor.b * 255, 255)));
	}
	else
	{
		for (UINT index = 0; index < diffuseCount; index++)
		{
			aiString path;

			material->GetTexture(aiTextureType_DIFFUSE, index, &path);

			//Get the texture file location
			size_t pos = modelpath.find_last_of("\\/");
			std::string basePath = modelpath.substr(0, pos + 1);

			std::string texturepath = path.data;
			size_t texPos = texturepath.find_last_of("\\/");
			texturepath = texturepath.substr(texPos + 1, texturepath.size() - texPos - 4);
			std::string fileloc = basePath + texturepath + "png";

			textures.push_back(Texture(fileloc));
		}
	}

	/*--------------------------------------------------------------------------------
	Load Normal
	--------------------------------------------------------------------------------*/
	if (normalCount)
	{
		for (UINT index = 0; index < normalCount; index++)
		{
			aiString path;

			material->GetTexture(aiTextureType_HEIGHT, index, &path);

			//Get the texture file location
			size_t pos = modelpath.find_last_of("\\/");
			std::string basePath = modelpath.substr(0, pos + 1);

			std::string texturepath = path.data;
			size_t texPos = texturepath.find_last_of("\\/");
			texturepath = texturepath.substr(texPos + 1, texturepath.size() - texPos - 4);
			std::string fileloc = basePath + texturepath + "png";

			textures.push_back(Texture(fileloc));
		}
	}

	/*--------------------------------------------------------------------------------
	Load Specular
	--------------------------------------------------------------------------------*/
	if (specularCount)
	{
		for (UINT index = 0; index < specularCount; index++)
		{
			aiString path;

			material->GetTexture(aiTextureType_SPECULAR, index, &path);

			//Get the texture file location
			size_t pos = modelpath.find_last_of("\\/");
			std::string basePath = modelpath.substr(0, pos + 1);

			std::string texturepath = path.data;
			size_t texPos = texturepath.find_last_of("\\/");
			texturepath = texturepath.substr(texPos + 1, texturepath.size() - texPos - 4);
			std::string fileloc = basePath + texturepath + "png";

			textures.push_back(Texture(fileloc));
		}
	}
	return textures;
}