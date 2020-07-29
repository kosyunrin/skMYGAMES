#include"main.h"
#include"renderer.h"
#include"texture.h"
#include"game_object.h"
#include"CmeshField.h"
#include<vector>

CmeshField::CmeshField()
{
}
CmeshField::~CmeshField()
{
}
void CmeshField::Init()
{
	setinit(1, 1, 3.0f,0.0f,0.0f,0.0f);
	m_Position.y = 5.0f;
}
void CmeshField::Uninit()
{
	delete[] vertex;
	delete[] index;
	m_VertexBuffer->Release();
	m_indexBuffer->Release();
	m_Texture->Unload();
	delete m_Texture;
}
void CmeshField::UpDate(float dt)
{
}
void CmeshField::Draw()
{

	//UINT stride = sizeof(VERTEX_3D);
	//UINT offset = 0;//

	//CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	CRenderer::SetVertexBuffers(m_VertexBuffer);
	CRenderer::SetIndexBuffer(m_indexBuffer);
	CRenderer::SetTexture(m_Texture);
	//::SetWorldViewProjection2D();
	XMMATRIX world;
	world = XMMatrixScaling(1.0f, 1.0f, 1.0f);//拡大
	world *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);//回転
	world *= XMMatrixTranslation(m_Position.x,m_Position.y, m_Position.z);//移動
	CRenderer::SetWorldMatrix(&world);

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	CRenderer::GetDeviceContext()->DrawIndexed(indexMax, 0, 0);

}

void CmeshField::setinit(int m, int n, float r, float x, float y, float z)
{
	m_Position = { x,y,z };
	vertexMax = (m + 1)*(n + 1);
	indexMax = m * n * 6;
	vertex = new VERTEX_3D[vertexMax];//movememory
	int count = 0;
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= m; j++)
		{
			vertex[count] =
			{
				XMFLOAT3((j*r) - (m*r / 2),0.0f,(i*r) - (n*r / 2)),
				XMFLOAT3(0.0f,1.0f,0.0f),
				XMFLOAT4(1.0f,1.0f,1.0f,1.0f),
				XMFLOAT2(j,i)//
			};
			count++;
		}
	}


	index = new WORD[indexMax];
	count = 0;
	for (int o = 0; o < n; o++)
	{
		for (int i = 0; i < m; i++)
		{
			index[count] = (o*(m + 1)) + i;
			count++;
			index[count] = (o*(m + 1)) + (i + 1);
			count++;
			index[count] = ((o + 1)*(m + 1)) + i;
			count++;
			index[count] = (o*(m + 1)) + (i + 1);
			count++;
			index[count] = ((o + 1)*(m + 1)) + i;
			count++;
			index[count] = ((o + 1)*(m + 1)) + (i + 1);
			count++;
		}
	}


	D3D11_BUFFER_DESC vetexMemory;//记录4个点的内存
	ZeroMemory(&vetexMemory, sizeof(vetexMemory));
	vetexMemory.Usage = D3D11_USAGE_DEFAULT;//用途
	vetexMemory.ByteWidth = sizeof(VERTEX_3D) * vertexMax;//缓存的大小
	vetexMemory.BindFlags = D3D11_BIND_VERTEX_BUFFER;// 定义它是什么什么内存
	vetexMemory.CPUAccessFlags = 0;//

	D3D11_SUBRESOURCE_DATA sd;//给协达用的内存
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	CRenderer::GetDevice()->CreateBuffer(&vetexMemory, &sd, &m_VertexBuffer);

	//indexbuffer
	D3D11_BUFFER_DESC indexM;//记录4个点的内存
	ZeroMemory(&indexM, sizeof(indexM));
	indexM.Usage = D3D11_USAGE_DEFAULT;//用途
	indexM.ByteWidth = sizeof(WORD) * indexMax;//缓存的大小
	indexM.BindFlags = D3D11_BIND_INDEX_BUFFER;// 定义它是什么什么内存
	indexM.CPUAccessFlags = 0;//

	D3D11_SUBRESOURCE_DATA sd0;//给协达用的内存
	ZeroMemory(&sd0, sizeof(sd0));
	sd0.pSysMem = index;
	CRenderer::GetDevice()->CreateBuffer(&indexM, &sd0, &m_indexBuffer);

	m_Texture = new CTexture();
	m_Texture->Load("asset/xx.tga");
}

//void CmeshField::inininn()
//{
//	
//
//
//	Assimp::Importer imp;
//	const auto pModel = imp.ReadFile("asset/Onepiece/miku_01.obj", aiProcess_Triangulate
//		| aiProcess_JoinIdenticalVertices);
//	//const auto PMesh = pModel->mMeshes[1];//网格数组mMeshes
//	//PMesh->mNumVertices;
//	std::vector<Vertex> vertexbuffer;
//	std::vector<unsigned short> indexs;
//	//unsigned int VertexMax=0;
//	unsigned int IndexMax = 0;
//	//vertexbuffer.reserve(PMesh->mNumVertices);//顶点数
//	for (unsigned int i = 0; i < pModel->mNumMeshes; i++)
//	{
//		
//		const auto PMesh = pModel->mMeshes[i];
//		vertexbuffer.reserve(PMesh->mNumVertices);//顶点数
//		for (unsigned int i = 0; i < PMesh->mNumVertices; i++)
//		{
//			++VertexMax;
//			vertexbuffer.push_back({ {PMesh->mVertices[i].x,
//				PMesh->mVertices[i].y,PMesh->mVertices[i].z}
//				});//*reinterpret_cast<XMFLOAT3*>(&PMesh->mNormals[i])
//			
//		}
//		
//		indexs.reserve(PMesh->mNumFaces * 3);//メッシュで作った面
//		for (unsigned int i = 0; i < PMesh->mNumFaces; i++)
//		{
//			++IndexMax;
//			const auto& face = PMesh->mFaces[i];
//			assert(face.mNumIndices == 3);
//			indexs.push_back(face.mIndices[0]);
//			indexs.push_back(face.mIndices[1]);
//			indexs.push_back(face.mIndices[2]);//3jiao cheliang
//		}
//	}
//	Vertex* vs = new Vertex[VertexMax];
//	for (int i = 0; i < VertexMax; i++)
//	{
//		vs[i].pos;
//		
//	}
//	// 頂点バッファ生成
//	{
//		D3D11_BUFFER_DESC bd;
//		ZeroMemory(&bd, sizeof(bd));
//		bd.Usage = D3D11_USAGE_DEFAULT;
//		bd.ByteWidth = sizeof(Vertex) * VertexMax;
//		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//		bd.CPUAccessFlags = 0;
//
//		D3D11_SUBRESOURCE_DATA sd;
//
//		ZeroMemory(&sd, sizeof(sd));
//		sd.pSysMem = vs;
//
//		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
//	}
//
//	unsigned short* index = new unsigned short[IndexMax*3];
//	// インデックスバッファ生成
//	{
//		D3D11_BUFFER_DESC bd;
//		ZeroMemory(&bd, sizeof(bd));
//		bd.Usage = D3D11_USAGE_DEFAULT;
//		bd.ByteWidth = sizeof(unsigned short) *IndexMax*3;
//		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
//		bd.CPUAccessFlags = 0;
//
//		D3D11_SUBRESOURCE_DATA sd;
//		ZeroMemory(&sd, sizeof(sd));
//		sd.pSysMem = index;
//
//		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_indexBuffer);
//		indexMax = IndexMax * 3;
//	}
//}
