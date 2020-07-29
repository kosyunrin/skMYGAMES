#include"main.h"
#include"renderer.h"
#include"texture.h"
#include"game_object.h"
#include"field.h"

CField::CField()
{
}
CField::~CField()
{
}
void CField::Init()
{
	for (int z = 0; z < aabb; z++)
	{
		for (int x = 0; x < aabb; x++)
		{
			m_Vertex[z * aabb + x].Position.x = x -aabb/2.0f;
			m_Vertex[z * aabb + x].Position.z = -z +aabb/ 2.0f;
			m_Vertex[z * aabb + x].Position.y = 0.0f/*sinf( x * 0.1f ) * sinf(z * 0.1f) * 2.0f*/;
			m_Vertex[z * aabb + x].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			m_Vertex[z * aabb + x].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			m_Vertex[z * aabb + x].TexCoord = XMFLOAT2(x, z);

		}
	}
	for (int z = 1; z < aabb - 1; z++)
	{
		for (int x = 1; x < aabb - 1; x++)
		{
			va.x = m_Vertex[(z - 1) * aabb + x].Position.x - m_Vertex[(z + 1) * aabb + x].Position.x;
			va.y = m_Vertex[(z - 1) * aabb + x].Position.y - m_Vertex[(z + 1) * aabb + x].Position.y;
			va.z = m_Vertex[(z - 1) * aabb + x].Position.z - m_Vertex[(z + 1) * aabb + x].Position.z;


			vb.x = m_Vertex[z * aabb + (x + 1)].Position.x - m_Vertex[(z - 1) * aabb + (x - 1)].Position.x;
			vb.y = m_Vertex[z * aabb + (x + 1)].Position.y - m_Vertex[(z - 1) * aabb + (x - 1)].Position.y;
			vb.z = m_Vertex[z * aabb + (x + 1)].Position.z - m_Vertex[(z - 1) * aabb + (x - 1)].Position.z;
			XMFLOAT3 n;
			n.x = va.y*vb.z - va.z*vb.y;
			n.y = va.z*vb.x - va.x*vb.z;
			n.z = va.x*vb.y - va.y*vb.x;
			float length = sqrtf(n.x*n.x + n.y*n.y + n.z*n.z);
			n.x = n.x / length;
			n.y = n.y / length;
			n.z = n.z / length;
			m_Vertex[z * aabb + x].Normal = n;
		}
	}
	

	/*std::vector<VERTEX_3D> temp;

	for (VERTEX_3D v : m_Vertex)
		temp.push_back(v);
	Ray_collision::BVertex_vec = temp;*/
	/*WORD index[6]
	{
		0,1,2,1,2,3
	};*/

	//xin
	unsigned short index[(aabb - 1)*(aabb - 1) * 6];
	 int count = 0;
	for (int o = 0; o < (aabb-1); o++)
	{
		for (int i = 0; i < (aabb-1); i++)
		{
			index[count] = (o*((aabb - 1) + 1)) + i;
			//fang ru jin dian 
			//jinD.push_back(m_Vertex[index[count]].Position);
			SMap[o][i].pos = { o,i };
			SMap[o][i].jinD = m_Vertex[index[count]].Position;
			count++;
			index[count] = (o*((aabb - 1) + 1)) + (i + 1);
			count++;
			index[count] = ((o + 1)*((aabb - 1) + 1)) + i;
			count++;			
			index[count] = (o*((aabb - 1) + 1)) + (i + 1);
			count++;
			index[count] = ((o + 1)*((aabb - 1) + 1)) + i;
			count++;
			index[count] = ((o + 1)*((aabb - 1) + 1)) + (i + 1);
			//fang ru yuan dian 
			//YuanD.push_back(m_Vertex[index[count]].Position);
			SMap[o][i].YuanD = m_Vertex[index[count]].Position;
			count++;
			
		}
	}
	std::vector<unsigned short> tempx;

	//for (unsigned short i : index)
	//	tempx.push_back(i);

	//Ray_collision::BInt_vec = tempx;




	D3D11_BUFFER_DESC vetexMemory;//记录4个点的内存
	ZeroMemory(&vetexMemory, sizeof(vetexMemory));
	vetexMemory.Usage = D3D11_USAGE_DEFAULT;//用途
	vetexMemory.ByteWidth = sizeof(VERTEX_3D) * aabb*aabb;//缓存的大小
	vetexMemory.BindFlags = D3D11_BIND_VERTEX_BUFFER;// 定义它是什么什么内存
	vetexMemory.CPUAccessFlags = 0;//

	D3D11_SUBRESOURCE_DATA sd;//给协达用的内存
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = m_Vertex;
	CRenderer::GetDevice()->CreateBuffer(&vetexMemory, &sd, &m_VertexBuffer);

	//indexbuffer
	D3D11_BUFFER_DESC indexM;//记录4个点的内存
	ZeroMemory(&indexM, sizeof(indexM));
	indexM.Usage = D3D11_USAGE_DEFAULT;//用途
	indexM.ByteWidth = sizeof(WORD) * (aabb-1)*(aabb-1)*6;//缓存的大小
	indexM.BindFlags = D3D11_BIND_INDEX_BUFFER;// 定义它是什么什么内存
	indexM.CPUAccessFlags = 0;//

	D3D11_SUBRESOURCE_DATA sd0;//给协达用的内存
	ZeroMemory(&sd0, sizeof(sd0));
	sd0.pSysMem = index;
	CRenderer::GetDevice()->CreateBuffer(&indexM, &sd0, &m_indexBuffer);

	m_Texture = new CTexture();
	//m_Texture->LoadALLTga();
	//m_Texture->LoadDDs(L"asset/GameTexture/darkdirt.dds");//XueTiaoGe
	m_Texture->LoadAny(L"asset/GameTexture/JK.jpg");
}
void CField::Uninit()
{
	m_VertexBuffer->Release();
	m_indexBuffer->Release();
	m_Texture->Unload();
	delete m_Texture;
}
void CField::UpDate(float dt)
{
}
void CField::Draw()
{
	
	//UINT stride = sizeof(VERTEX_3D);
	//UINT offset = 0;//

	//CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	CRenderer::SetVertexBuffers(m_VertexBuffer);
	CRenderer::SetIndexBuffer(m_indexBuffer);
	//CRenderer::SetTextureIndex(m_Texture, 1);//绑定一个着色器资源数组到像素着色器管线状态。
	CRenderer::SetTexture(m_Texture);
	//::SetWorldViewProjection2D();
	XMMATRIX world;
	world = XMMatrixScaling(12.0f, 12.0f, 12.0f);//拡大
	world *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);//回転
	world *= XMMatrixTranslation(0.0f, 5.0f, 0.0f);//移動
	CRenderer::SetWorldMatrix(&world);
	/*for (UINT i = 0; i < Ray_collision::BVertex_vec.size(); i++)
	{
		XMVector3TransformCoord(XMLoadFloat3(&Ray_collision::BVertex_vec[i].Position),
			XMMatrixScaling(1.0f, 1.0f, 1.0f));
	}*/
	//for ((UINT  < Ray_collision::BVertex_vec.size(); i++)
	//{
	//	XMVector3TransformCoord(XMLoadFloat3(&Ray_collision::BVertex_vec[i].Position),
	//		world);
	//}

	//CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	CRenderer::GetDeviceContext()->DrawIndexed((aabb - 1)*(aabb - 1) * 6,0, 0);

}

float CField::GetHeight(XMFLOAT3 Postion)
{
	int x,z;
	XMFLOAT3 p0, p1, p2, v01, v02,  v, hp, va, vb;
	float dp0n, dvn, dpn, t;
	v = XMFLOAT3(0.0f, -10.0f, 0.0f);
	x = (Postion.x+aabb/2.0f) / 1.0f;
	z = (-Postion.z+aabb/2.0f)/ 1.0f;

	va.x = m_Vertex[(z + 1) * aabb + (x + 1)].Position.x - m_Vertex[z * aabb + x].Position.x;
	va.y = m_Vertex[(z + 1) * aabb + (x + 1)].Position.y - m_Vertex[z * aabb + x].Position.y;
	va.z = m_Vertex[(z + 1) * aabb + (x + 1)].Position.z - m_Vertex[z * aabb + x].Position.z;

	vb.x = Postion.x - m_Vertex[z * aabb + x].Position.x;
	vb.y = Postion.y - m_Vertex[z * aabb + x].Position.y;
	vb.z = Postion.z - m_Vertex[z * aabb + x].Position.z;
	if (va.z*vb.x - va.x*vb.z > 0.0f)
	{
		p0 = m_Vertex[(z + 1) * aabb + x].Position;
		p1 = m_Vertex[z * aabb + x].Position;
		p2 = m_Vertex[(z + 1) * aabb + (x + 1)].Position;
	}
	else
	{
		p0= m_Vertex[(z * aabb + (x+1))].Position;
		p1= m_Vertex[(z + 1) * aabb + (x + 1)].Position;
		p2= m_Vertex[z * aabb + x].Position;
	}
	//v01 = p1 - p0;
	v01 = XMFLOAT3(p1.x - p0.x, p1.y - p0.y, p1.z - p0.z);
	//v02 = p2 - p0;
	v02 = XMFLOAT3(p2.x - p0.x, p2.y - p0.y, p2.z - p0.z);
	//n = v01 * v02;
	XMFLOAT3 n;
	n.x = v01.y*v02.z - v01.z*v02.y;
	n.y = v01.z*v02.x - v01.x*v02.z;
	n.z = v01.x*v02.y - v01.y*v02.x;
	//dvn = v.n;
	dvn = v.x*n.x + v.y*n.y + v.z*n.z;
	//dp0n = p0.n;
	dp0n = p0.x*n.x + p0.y*n.y + p0.z*n.z;	
	//dpn = Postion.n;
	dpn = Postion.x*n.x + Postion.y*n.y + Postion.z*n.z;
	t = (dp0n - dpn) / dvn;
	//hp = Postion + v * t;
	hp = XMFLOAT3(Postion.x + v.x*t, Postion.y + v.y*t, Postion.z + v.z*t);
	return hp.y;
	
}

//std::vector<VERTEX_3D> CField::Get_floor_vector3D()
//{
//	std::vector<VERTEX_3D> temp;
//
//	for (VERTEX_3D v : m_Vertex)
//		temp.push_back(v);
//
//	return temp;
//}
//
//std::vector<unsigned short> CField::Get_floor_int()
//{
//	std::vector<unsigned short> temp;
//
//	for (unsigned short i : index)
//		temp.push_back(i);
//	return temp;
//}
