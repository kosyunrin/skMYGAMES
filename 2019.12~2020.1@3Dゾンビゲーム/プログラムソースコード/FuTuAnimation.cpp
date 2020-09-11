#include "main.h"
#include "texture.h"
//#include <io.h>
#include "FuTuAnimation.h"



FuTuAnimation::FuTuAnimation()
{
}


FuTuAnimation::~FuTuAnimation()
{
}

void FuTuAnimation::Draw()
{
	/*CRenderer::SetVertexBuffers(m_VertexBuffer);
	CRenderer::SetIndexBuffer(m_IndexBuffer);
	CRenderer::DrawIndexed(m_IndexNum, 0, 0);*/ 
	for (int i = 0; i < m_MeshNum; i++)
	{
		CRenderer::SetVertexBuffers(m_Mesh[i].m_VertexBuffer);
		CRenderer::SetIndexBuffer(m_Mesh[i].m_IndexBuffer);
		CRenderer::DrawIndexed(m_Mesh[i].IndexNum, 0, 0);
	}
}

void FuTuAnimation::Load(const char * FileName)
{		
	m_Scene = aiImportFile(FileName, aiProcessPreset_TargetRealtime_MaxQuality| aiProcess_CalcTangentSpace |//ﾗﾔｶｯｼﾆﾋ翩ﾐﾏﾟｺﾍｷｨﾏﾟ
		aiProcess_Triangulate |//ﾗﾔｶｯﾋﾄｱﾟﾐﾎﾗｪｻｻﾎｪﾈｽﾇﾐﾎ
		aiProcess_JoinIdenticalVertices | //ｺﾏｲ｢ﾏ猩ｬｵﾄｶ･ｵ・
		aiProcess_ConvertToLeftHanded);
	//
	m_MeshNum = m_Scene->mNumMeshes;
	m_Mesh = new MESHs[m_MeshNum];
	for (int m = 0; m < m_MeshNum; m++)
	{
		aiMesh* mesh = m_Scene->mMeshes[m];
		VERTEX_3D* vertex = new VERTEX_3D[mesh->mNumVertices];
		for (int i = 0; i < mesh->mNumVertices; i++)
		{
			vertex[i].Position = XMFLOAT3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
			if (mesh->mNormals != nullptr)
				vertex[i].Normal = XMFLOAT3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
			vertex[i].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			if (mesh->mTextureCoords[0])
				vertex[i].TexCoord = XMFLOAT2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}
		{
			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(VERTEX_3D)*mesh->mNumVertices;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = vertex;

			CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_Mesh[m].m_VertexBuffer);
		}
		delete[] vertex;

		unsigned int short* index;
		index = new unsigned short[mesh->mNumFaces * 3];
		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			index[i * 3 + 0] = mesh->mFaces[i].mIndices[0];
			index[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
			index[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
		}
		m_Mesh[m].IndexNum = mesh->mNumFaces * 3;

		{
			D3D11_BUFFER_DESC bd2;
			ZeroMemory(&bd2, sizeof(bd2));
			bd2.Usage = D3D11_USAGE_DEFAULT;
			bd2.ByteWidth = sizeof(unsigned short)*m_Mesh[m].IndexNum;
			bd2.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd2.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA sd2;
			ZeroMemory(&sd2, sizeof(sd2));
			sd2.pSysMem = index;

			CRenderer::GetDevice()->CreateBuffer(&bd2, &sd2, &m_Mesh[m].m_IndexBuffer);
		}
		delete[] index;
	}
	//
	
	
	
	
}

void FuTuAnimation::Unload()
{
	//m_VertexBuffer->Release();
	//m_IndexBuffer->Release();
	for (int i = 0; i < m_MeshNum; i++)
	{
		m_Mesh[i].m_IndexBuffer->Release();
		m_Mesh[i].m_VertexBuffer->Release();
	}
	delete[] m_Mesh;
	aiReleaseImport(m_Scene);
	
}

void FuTuAnimation::Draw(XMMATRIX Matrix)
{
	DrawMesh(m_Scene->mRootNode, Matrix);
}

void FuTuAnimation::DrawMesh(aiNode * Node, XMMATRIX Matrix)
{
	aiMatrix4x4 matrix = Node->mTransformation;
	aiTransposeMatrix4(&matrix);
	XMMATRIX world = XMLoadFloat4x4((XMFLOAT4X4*)&matrix);
	world *= Matrix;//自身空间转换到世界空间 oya的matrix
	CRenderer::SetWorldMatrix(&world);
	for (int n = 0; n < Node->mNumMeshes; n++)
	{
		unsigned int mm = Node->mMeshes[n];
		//メッシュ描画
		CRenderer::SetVertexBuffers(m_Mesh[mm].m_VertexBuffer);
		CRenderer::SetIndexBuffer(m_Mesh[mm].m_IndexBuffer);
		CRenderer::DrawIndexed(m_Mesh[mm].IndexNum, 0, 0);
	}
	for (size_t i = 0; i < Node->mNumChildren; i++)
	{
		DrawMesh(Node->mChildren[i], world);
	}
}
