#include"main.h"
#include"renderer.h"
#include "Line.h"


Line::Line()
{
}


Line::~Line()
{
}


void Line::Init( float radius)
{
	//VERTEX_3D m_Vertex[8];
	//m_Vertex[0].Position = { -radius,radius,-radius };
	////m_Vertex[0].Normal = { 0.0f,1.0f,0.0f };
	//m_Vertex[0].Diffuse = { 1.0f, 0.0f, 0.0f ,1.0f};

	//m_Vertex[1].Position = { radius,radius,-radius };
	////m_Vertex[1].Normal = { 0.0f,1.0f,0.0f };
	//m_Vertex[1].Diffuse = { 1.0f, 0.0f, 0.0f ,1.0f };

	//m_Vertex[2].Position = { radius,radius,radius };
	////m_Vertex[2].Normal = { 0.0f,1.0f,0.0f };
	//m_Vertex[2].Diffuse = { 1.0f, 0.0f, 0.0f ,1.0f };

	//m_Vertex[3].Position = { -radius,radius,radius };
	////m_Vertex[3].Normal = { 0.0f,1.0f,0.0f };
	//m_Vertex[3].Diffuse = { 1.0f, 0.0f, 0.0f ,1.0f };

	//m_Vertex[4].Position = { -radius,-radius,-radius };
	////m_Vertex[4].Normal = { 0.0f,1.0f,0.0f };
	//m_Vertex[4].Diffuse = { 1.0f, 0.0f, 0.0f ,1.0f };

	//m_Vertex[5].Position = { radius,-radius,-radius };
	////m_Vertex[5].Normal = { 0.0f,1.0f,0.0f };
	//m_Vertex[5].Diffuse = { 1.0f, 0.0f, 0.0f ,1.0f };

	//m_Vertex[6].Position = { radius,-radius,radius };
	////m_Vertex[6].Normal = { 0.0f,1.0f,0.0f };
	//m_Vertex[6].Diffuse = { 1.0f, 0.0f, 0.0f ,1.0f };

	//m_Vertex[7].Position = { -radius,-radius,radius };
	////m_Vertex[7].Normal = { 0.0f,1.0f,0.0f };
	//m_Vertex[7].Diffuse = { 1.0f, 0.0f, 0.0f ,1.0f };


	VERTEX_3D m_Vertex[8];
	
	//m_Vertex[0].Position={0.300000012, -0.500000000, -2.50000000 };
	//m_Vertex[1].Position={1.29999995, -0.500000000, -2.50000000 };
	//m_Vertex[2].Position={1.29999995, 0.500000000, -2.50000000 };
	//m_Vertex[3].Position={0.300000012, 0.500000000, -2.50000000 };
	//m_Vertex[4].Position={0.300000012, -0.500000000, -3.50000000 };
	//m_Vertex[5].Position={1.29999995, -0.500000000, -3.50000000 };
	//m_Vertex[6].Position={1.29999995, 0.500000000, -3.50000000 };
	//m_Vertex[7].Position={0.300000012, 0.500000000, -3.50000000 };
	m_Vertex[0].Position={ -0.304167211, -0.304167390, 0.304167271 };
	m_Vertex[1].Position={ 0.304167330, -0.304167390, 0.304167271 };
	m_Vertex[2].Position={ 0.304167330, 0.304167032, 0.304167271 };
	m_Vertex[3].Position={ -0.304167211, 0.304167032, 0.304167271 };
	m_Vertex[4].Position={ -0.304167211, -0.304167390, -0.304167271 };
	m_Vertex[5].Position={ 0.304167330, -0.304167390, -0.304167271 };
	m_Vertex[6].Position={ 0.304167330, 0.304167032, -0.304167271 };
	m_Vertex[7].Position={ -0.304167211, 0.304167032, -0.304167271 }	   ;
	m_Vertex[0].Diffuse = { 1.0f,0.0f,0.0f,1.0f };
	m_Vertex[1].Diffuse = { 1.0f,0.0f,0.0f,1.0f };
	m_Vertex[2].Diffuse = { 1.0f,0.0f,0.0f,1.0f };
	m_Vertex[3].Diffuse = { 1.0f,0.0f,0.0f,1.0f };
	m_Vertex[4].Diffuse = { 1.0f,0.0f,0.0f,1.0f };
	m_Vertex[5].Diffuse = { 1.0f,0.0f,0.0f,1.0f };
	m_Vertex[6].Diffuse = { 1.0f,0.0f,0.0f,1.0f };
	m_Vertex[7].Diffuse = { 1.0f,0.0f,0.0f,1.0f };
	WORD index[24];
	index[0] = 0; index[2] = 1; index[4] = 2; index[6] = 3;
	index[1] = 1; index[3] = 2; index[5] = 3; index[7] = 0;

	index[8] = 4; index[10] = 5; index[12] = 6; index[14] = 7;
	index[9] = 5; index[11] = 6; index[13] = 7; index[15] = 4;

	index[16] = 0; index[18] = 1; index[20] = 2; index[22] = 3;
	index[17] = 4; index[19] = 5; index[21] = 6; index[23] = 7;


	m_VertexBuffer = CVertexBuffer<VERTEX_3D>::CreatVertexBuffer(m_Vertex, 8);

	//indexbuffer
	m_indexBuffer = CIndexBuffer<WORD>::CreatIndexBuffer(index,NULL, 24);
}

void Line::InitDrawBox(XMFLOAT3 * m_Vertex)
{
	VERTEX_3D m_Vertexx[8];
	for (UINT i = 0; i < 8; i++)
	{
		m_Vertexx[i].Position = m_Vertex[i];
		m_Vertexx[i].Diffuse = { 1.0f, 0.0f, 0.0f ,1.0f };
	}

	WORD index[24];
	index[0] = 0; index[2] = 1; index[4] = 2; index[6] = 3;
	index[1] = 1; index[3] = 2; index[5] = 3; index[7] = 0;

	index[8] = 4; index[10] = 5; index[12] = 6; index[14] = 7;
	index[9] = 5; index[11] = 6; index[13] = 7; index[15] = 4;

	index[16] = 0; index[18] = 1; index[20] = 2; index[22] = 3;
	index[17] = 4; index[19] = 5; index[21] = 6; index[23] = 7;

	D3D11_BUFFER_DESC vetexMemory;//记录4个点的内磥E
	ZeroMemory(&vetexMemory, sizeof(vetexMemory));
	vetexMemory.Usage = D3D11_USAGE_DEFAULT;//用途
	vetexMemory.ByteWidth = sizeof(VERTEX_3D) * 8;//缓存的大小
	vetexMemory.BindFlags = D3D11_BIND_VERTEX_BUFFER;// 定义藖E鞘裁词裁茨诖丒
	vetexMemory.CPUAccessFlags = 0;//

	D3D11_SUBRESOURCE_DATA sd;//给协磥E玫哪诖丒
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = m_Vertexx;
	CRenderer::GetDevice()->CreateBuffer(&vetexMemory, &sd, &m_VertexBuffer);

	//indexbuffer
	D3D11_BUFFER_DESC indexM;//记录4个点的内磥E
	ZeroMemory(&indexM, sizeof(indexM));
	indexM.Usage = D3D11_USAGE_DEFAULT;//用途
	indexM.ByteWidth = sizeof(WORD) * 24;//缓存的大小
	indexM.BindFlags = D3D11_BIND_INDEX_BUFFER;// 定义藖E鞘裁词裁茨诖丒
	indexM.CPUAccessFlags = 0;//

	D3D11_SUBRESOURCE_DATA sd0;//给协磥E玫哪诖丒
	ZeroMemory(&sd0, sizeof(sd0));
	sd0.pSysMem = index;
	CRenderer::GetDevice()->CreateBuffer(&indexM, &sd0, &m_indexBuffer);
}

void Line::DrawLine(XMFLOAT3 orgin)
{
	CVertexBuffer<VERTEX_3D>::SetVertexBuffer(m_VertexBuffer);
	CIndexBuffer<WORD>::SetIndexBuffer(m_indexBuffer);
	XMFLOAT3 Scaling = { 1.0f, 1.0f, 1.0f };
	XMFLOAT3 Rotation = { 0.0f, 0.0f, 0.0f };
	CShader::SetWorldMatrix(Scaling, Rotation, orgin);
	CIndexBuffer<WORD>::DRAW_TOPOLOGY_LINELIST(24);
}

void Line::DrawLineByPlayerWorld(XMMATRIX world)
{
	//CRenderer::SetVertexBuffers(m_VertexBuffer);
	//CRenderer::SetIndexBuffer(m_indexBuffer);
	CVertexBuffer<VERTEX_3D>::SetVertexBuffer(m_VertexBuffer);
	CIndexBuffer<WORD>::SetIndexBuffer(m_indexBuffer);//绑定到渲染管线
	//unit and word 16
	CRenderer::SetWorldMatrix(&world);
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	//CRenderer::GetDeviceContext()->iaset
	CRenderer::GetDeviceContext()->DrawIndexed(24, 0, 0);
}

void Line::Uninit()
{
	if (m_VertexBuffer) m_VertexBuffer->Release();
	if (m_indexBuffer) m_indexBuffer->Release();
}

void Line::MapInit()
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;//需要GPU进行读写访问的资源
	//bd.Usage = D3D11_USAGE_DYNAMIC;//GPU（只读）和CPU（仅写葋E┛煞梦实淖试础６杂诮蒀PU至少每帧竵E乱淮蔚淖试矗试词且桓霾淮难≡瘛Ｒ丒露试矗丒褂肕ap方法。 
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;//计算缓冲区大小
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER; //确定缓冲区如何绑定到管道
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//	D3D11_SUBRESOURCE_DATA sd;
	//	ZeroMemory(&sd, sizeof(sd));
	//	sd.pSysMem = vertex;
	CRenderer::GetDevice()->CreateBuffer(&bd, NULL, &m_VertexBuffer);
}

void Line::MapDrawLine()
{
}
