#include"main.h"
#include"renderer.h"
#include"texture.h"
#include"game_object.h"
#include "skyBox.h"



void skyBox::Init()
{
	VERTEX_3D vertex[24];
	//zhen
	vertex[0].Position = XMFLOAT3(-0.5f, 0.5f, -0.5f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(0.5f, 0.5f, -0.5f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-0.5f, -0.5f, -0.5f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(0.5, -0.5f, -0.5f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	//hou
	vertex[4].Position = XMFLOAT3(0.5f, 0.5f, 0.5f);
	vertex[4].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[4].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[4].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[5].Position = XMFLOAT3(-0.5f, 0.5f, 0.5f);
	vertex[5].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[5].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[5].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[6].Position = XMFLOAT3(0.5f, -0.5f, 0.5f);
	vertex[6].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[6].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[6].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[7].Position = XMFLOAT3(-0.5, -0.5f, 0.5f);
	vertex[7].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[7].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[7].TexCoord = XMFLOAT2(1.0f, 1.0f);


	//left
	vertex[8].Position = XMFLOAT3(-0.5f, 0.5f, 0.5f);
	vertex[8].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[8].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[8].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[9].Position = XMFLOAT3(-0.5f, 0.5f, -0.5f);
	vertex[9].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[9].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[9].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[10].Position = XMFLOAT3(-0.5f, -0.5f, 0.5f);
	vertex[10].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[10].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[10].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[11].Position = XMFLOAT3(-0.5, -0.5f, -0.5f);
	vertex[11].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[11].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[11].TexCoord = XMFLOAT2(1.0f, 1.0f);

	//Right
	vertex[12].Position = XMFLOAT3(0.5f, 0.5f, -0.5f);
	vertex[12].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[12].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[12].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[13].Position = XMFLOAT3(0.5f, 0.5f, 0.5f);
	vertex[13].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[13].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[13].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[14].Position = XMFLOAT3(0.5f, -0.5f, -0.5f);
	vertex[14].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[14].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[14].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[15].Position = XMFLOAT3(0.5, -0.5f, 0.5f);
	vertex[15].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[15].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[15].TexCoord = XMFLOAT2(1.0f, 1.0f);
	
	//shang 
	vertex[16].Position = XMFLOAT3(-0.5f, 0.5f, 0.5f);
	vertex[16].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[16].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[16].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[17].Position = XMFLOAT3(0.5f, 0.5f, 0.5f);
	vertex[17].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[17].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[17].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[18].Position = XMFLOAT3(-0.5f, 0.5f, -0.5f);
	vertex[18].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[18].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[18].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[19].Position = XMFLOAT3(0.5, 0.5f, -0.5f);
	vertex[19].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[19].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[19].TexCoord = XMFLOAT2(1.0f, 1.0f);

	//xia
	vertex[20].Position = XMFLOAT3(0.5f, -0.5f, 0.5f);
	vertex[20].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[20].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[20].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[21].Position = XMFLOAT3(-0.5f, -0.5f, 0.5f);
	vertex[21].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[21].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[21].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[22].Position = XMFLOAT3(0.5f, -0.5f, -0.5f);
	vertex[22].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[22].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[22].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[23].Position = XMFLOAT3(-0.5, -0.5f, -0.5f);
	vertex[23].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[23].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[23].TexCoord = XMFLOAT2(1.0f, 1.0f);
	/*vertex[0].Position = XMFLOAT3(-5.0f, 0.0f, 5.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(5.0f, 0.0f, 5.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-5.0f, 0.0f, -5.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(5.0f, 0.0f, -5.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);*/

	/*vertex[0].Position = XMFLOAT3(100.0f, 100.0f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(600.0f, 100.0f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(100.0f, 600.0f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(600.0f, 600.0f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);*/




	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 24;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	unsigned int index[10];
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	m_Texturefront = new CTexture();
	m_Texturefront->LoadAny(L"asset/Front.png");
	m_Textureback = new CTexture();
	m_Textureback->LoadAny(L"asset/Back.png");
	m_Textureleft = new CTexture();
	m_Textureleft->LoadAny(L"asset/Right.png");
	m_Textureright = new CTexture();
	m_Textureright->LoadAny(L"asset/Left.png");
	m_Texturetop = new CTexture();
	m_Texturetop->LoadAny(L"asset/Sky.png");
	m_Texturebottom = new CTexture();
	m_Texturebottom->LoadAny(L"asset/Floor.png");

}

void skyBox::Uninit()
{
	m_VertexBuffer->Release();
	m_Texturefront->Unload();
	m_Textureback->Unload();
	m_Textureleft->Unload();
	m_Textureright->Unload();
	m_Texturetop->Unload();
	m_Texturebottom->Unload();

	delete m_Texturefront;
	delete m_Textureback;
	delete m_Textureleft;
	delete m_Textureright;
	delete m_Texturetop;
	delete m_Texturebottom;

}

void skyBox::UpDate()
{
	
}

void skyBox::Draw()
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	//::SetWorldViewProjection2D();
	XMMATRIX world;
	world = XMMatrixScaling(1000.0f, 1000.0f, 1000.0f);//拡大
	world *= XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);//
	world *= XMMatrixTranslation(0.0f, 2.0f, 0.0f);//移動
	CRenderer::SetWorldMatrix(&world);

	CRenderer::SetTexture(m_Texturefront);

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	CRenderer::GetDeviceContext()->Draw(4, 0);

	CRenderer::SetTexture(m_Textureback);

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	CRenderer::GetDeviceContext()->Draw(4, 4);

	CRenderer::SetTexture(m_Textureleft);

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	CRenderer::GetDeviceContext()->Draw(4, 8);


	CRenderer::SetTexture(m_Textureright);

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	CRenderer::GetDeviceContext()->Draw(4, 12);

	CRenderer::SetTexture(m_Texturetop);

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	CRenderer::GetDeviceContext()->Draw(4, 16);

	CRenderer::SetTexture(m_Texturebottom);

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	CRenderer::GetDeviceContext()->Draw(4, 20);


	/*CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	CRenderer::SetTexture(m_Texture);*/
	//::SetWorldViewProjection2D();
	


}
