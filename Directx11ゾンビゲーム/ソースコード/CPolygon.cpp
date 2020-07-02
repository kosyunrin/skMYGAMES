#include"main.h"
#include"renderer.h"
#include"texture.h"
#include"CPolygon.h"

CTexture texture;
CPolygon::CPolygon()
{
	//Count = 0.0f;
}

CPolygon::~CPolygon()
{
}
void CPolygon::Init()
{
	
	//Count = 0.0f;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;//需要GPU进行读写访问的资源
	//bd.Usage = D3D11_USAGE_DYNAMIC;//GPU（只读）和CPU（仅写入）可访问的资源。对于将由CPU至少每帧更新一次的资源，动态资源是一个不错的选择。要更新动态资源，请使用Map方法。 
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;//计算缓冲区大小
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER; //确定缓冲区如何绑定到管道
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	CRenderer::GetDevice()->CreateBuffer(&bd, NULL, &m_VertexBuffer);
}
void CPolygon::Init2D(int nubmber)
{
	m_Texture = new CTexture();
	m_Texture->LoadPJtexture(nubmber);
	//Count = 0.0f;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;//需要GPU进行读写访问的资源
	//bd.Usage = D3D11_USAGE_DYNAMIC;//GPU（只读）和CPU（仅写入）可访问的资源。对于将由CPU至少每帧更新一次的资源，动态资源是一个不错的选择。要更新动态资源，请使用Map方法。 
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;//计算缓冲区大小
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER; //确定缓冲区如何绑定到管道
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	CRenderer::GetDevice()->CreateBuffer(&bd, NULL, &m_VertexBuffer);
}
void CPolygon::Init2D_tga(int nubmber)
{
	m_Texture = new CTexture();
	m_Texture->LoadTga(nubmber);
	//Count = 0.0f;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;//需要GPU进行读写访问的资源
	//bd.Usage = D3D11_USAGE_DYNAMIC;//GPU（只读）和CPU（仅写入）可访问的资源。对于将由CPU至少每帧更新一次的资源，动态资源是一个不错的选择。要更新动态资源，请使用Map方法。 
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;//计算缓冲区大小
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER; //确定缓冲区如何绑定到管道
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	CRenderer::GetDevice()->CreateBuffer(&bd, NULL, &m_VertexBuffer);
}
void CPolygon::Ini3DTex(const wchar_t * FileName)
{
	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0, 0);

	vertex[1].Position = XMFLOAT3(2.0f, 0.0f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1, 0);

	vertex[2].Position = XMFLOAT3(0.0f, 0.0f, 1.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0, 1);

	vertex[3].Position = XMFLOAT3(2.0f, 0.0f, 1.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1, 1);

	D3D11_BUFFER_DESC vetexMemory;//记录4个点的内存
	ZeroMemory(&vetexMemory, sizeof(vetexMemory));
	vetexMemory.Usage = D3D11_USAGE_DEFAULT;//用途
	vetexMemory.ByteWidth = sizeof(VERTEX_3D) * 4;//缓存的大小
	vetexMemory.BindFlags = D3D11_BIND_VERTEX_BUFFER;// 定义它是什么什么内存
	vetexMemory.CPUAccessFlags = 0;//

	D3D11_SUBRESOURCE_DATA sd;//给协达用的内存
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	CRenderer::GetDevice()->CreateBuffer(&vetexMemory, &sd, &m_VertexBuffer);
	m_Texture = new CTexture();
	m_Texture->LoadAny(FileName);
}
void CPolygon::Init3D(int texturenumber)
{
	m_Texture = new CTexture();
	m_Texture->LoadPJtexture(texturenumber);
	
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;//需要GPU进行读写访问的资源
	//bd.Usage = D3D11_USAGE_DYNAMIC;//GPU（只读）和CPU（仅写入）可访问的资源。对于将由CPU至少每帧更新一次的资源，动态资源是一个不错的选择。要更新动态资源，请使用Map方法。 
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;//计算缓冲区大小
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER; //确定缓冲区如何绑定到管道
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	CRenderer::GetDevice()->CreateBuffer(&bd, NULL, &m_VertexBuffer);
}
void CPolygon::Uninit()
{
	m_VertexBuffer->Release();
}

void CPolygon::Uninit3D(int tex)
{
	m_Texture->UnloadPJtex(tex);
	delete m_Texture;
	m_VertexBuffer->Release();
}

void CPolygon::UnintTag(int number)
{
	m_Texture->UnloadTag(number);
	delete m_Texture;
	m_VertexBuffer->Release();
}

void CPolygon::UpDate()
{

}

void CPolygon::Draw_animation2D(float Posx, float Posy, float ScaleW, float ScaleH,int texNum, int anim_lie_count,int anim_hang_count,float anim_speed)
{
	CRenderer::UIBegin();
	Count += anim_speed;
	w = texture.Texture_GetWidth(texNum);
	h = texture.Texture_GetHeight(texNum);
	int page = (int)Count % (anim_lie_count*anim_hang_count);
	int tx = page * w / anim_lie_count;
	int ty = page/ anim_lie_count * h/ anim_hang_count;
	int tw = w / anim_lie_count;
	int th = h / anim_hang_count;
	
	float u0, u1, v0, v1;
	u0 = tx / w;
	u1 = (tx + tw) / w;
	v0 = ty / h;
	v1 = (ty + th) / h;

	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(Posx, Posy, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(u0, v0);

	vertex[1].Position = XMFLOAT3(Posx + ScaleW, Posy, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(u1, v0);

	vertex[2].Position = XMFLOAT3(Posx, Posy + ScaleH, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(u0, v1);

	vertex[3].Position = XMFLOAT3(Posx + ScaleW, Posy + ScaleH, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(u1, v1);

	D3D11_MAPPED_SUBRESOURCE ms;
	CRenderer::GetDeviceContext()->Map(m_VertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, vertex, sizeof(vertex));
	CRenderer::GetDeviceContext()->Unmap(m_VertexBuffer, NULL);

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;

	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	CRenderer::SetTextureIndex(m_Texture, texNum);
	CRenderer::SetWorldViewProjection2D();
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	CRenderer::GetDeviceContext()->Draw(4, 0);
	CRenderer::UIBack();
}
void CPolygon::DrawString2D(float Posx, float Posy, float ScaleW, float ScaleH, int texNum, int anim_lie_count, int anim_hang_count, int number)
{
	w = texture.Texture_GetWidth(texNum);
	h = texture.Texture_GetHeight(texNum);
	int page = number;
	int tx = page * w / anim_lie_count;
	int ty = page / anim_lie_count * h / anim_hang_count;
	int tw = w / anim_lie_count;
	int th = h / anim_hang_count;

	float u0, u1, v0, v1;
	u0 = tx / w;
	u1 = (tx + tw) / w;
	v0 = ty / h;
	v1 = (ty + th) / h;

	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(Posx, Posy, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(u0, v0);

	vertex[1].Position = XMFLOAT3(Posx + ScaleW, Posy, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(u1, v0);

	vertex[2].Position = XMFLOAT3(Posx, Posy + ScaleH, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(u0, v1);

	vertex[3].Position = XMFLOAT3(Posx + ScaleW, Posy + ScaleH, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(u1, v1);

	D3D11_MAPPED_SUBRESOURCE ms;
	CRenderer::GetDeviceContext()->Map(m_VertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, vertex, sizeof(vertex));
	CRenderer::GetDeviceContext()->Unmap(m_VertexBuffer, NULL);

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;

	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	CRenderer::SetTextureIndex(m_Texture, texNum);
	CRenderer::SetWorldViewProjection2D();
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	CRenderer::GetDeviceContext()->Draw(4, 0);
}
void CPolygon::DrawPlayerLife(float Posx,float Posy, float Posz, float ScaleW, float ScaleH, float R, float G, float B, float Alpha, int texNum, XMMATRIX world)
{
	CRenderer::UIBegin();
	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(Posx, Posy, Posz);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(R, G, B, Alpha);
	vertex[0].TexCoord = XMFLOAT2(0, 0);

	vertex[1].Position = XMFLOAT3(Posx + ScaleW, Posy, Posz);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(R, G, B, Alpha);
	vertex[1].TexCoord = XMFLOAT2(1, 0);

	vertex[2].Position = XMFLOAT3(Posx, Posy, Posz + ScaleH);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(R, G, B, Alpha);
	vertex[2].TexCoord = XMFLOAT2(0, 1);

	vertex[3].Position = XMFLOAT3(Posx + ScaleW, Posy, Posz + ScaleH);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(R, G, B, Alpha);
	vertex[3].TexCoord = XMFLOAT2(1, 1);

	D3D11_MAPPED_SUBRESOURCE ms;
	CRenderer::GetDeviceContext()->Map(m_VertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, vertex, sizeof(vertex));
	CRenderer::GetDeviceContext()->Unmap(m_VertexBuffer, NULL);

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;

	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	CRenderer::SetTextureJPGPNG(m_Texture, texNum);
	//CRenderer::SetWorldViewProjection2D();
	CRenderer::SetWorldMatrix(&world);
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	CRenderer::GetDeviceContext()->Draw(4, 0);
	CRenderer::UIBack();
}
void CPolygon::Draw3DTex(XMMATRIX world)
{
	//CRenderer::InstanceBegin();
	CRenderer::SetVertexBuffers(m_VertexBuffer);
	CRenderer::SetTexture(m_Texture);
	//CRenderer::SetTextureJPGPNG(m_Texture, 1);
	CRenderer::SetWorldMatrix(&world);
	//CRenderer::SetInstanceWorld(InstanceWorld);
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	CRenderer::GetDeviceContext()->Draw(4,0);
	//CRenderer::GetDeviceContext()->DrawInstanced(4, 10, 0, 0);
	//CRenderer::InstanceEnd();
}
void CPolygon::PNGDraw2D(float Posx, float Posy, float ScaleW, float ScaleH, int texNum,float color)
{
	CRenderer::UIBegin();
	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(Posx, Posy, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(color, color, color, color);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(Posx + ScaleW, Posy, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(color, color, color, color);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(Posx, Posy + ScaleH, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(color, color, color, color);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(Posx + ScaleW, Posy + ScaleH, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(color, color, color, color);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	D3D11_MAPPED_SUBRESOURCE ms;
	CRenderer::GetDeviceContext()->Map(m_VertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, vertex, sizeof(vertex));
	CRenderer::GetDeviceContext()->Unmap(m_VertexBuffer, NULL);

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;

	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	CRenderer::SetTextureJPGPNG(m_Texture, texNum);
	//CRenderer::SetShadowTex(0);
	CRenderer::SetWorldViewProjection2D();
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	CRenderer::GetDeviceContext()->Draw(4, 0);
	CRenderer::UIBack();
}
void CPolygon::Draw(float Posx, float Posy, float ScaleW, float ScaleH, float tx, float ty, float tw, float th, int texNum)
{
	w = texture.Texture_GetWidth(texNum);
	h = texture.Texture_GetHeight(texNum);
	float u0, u1, v0, v1;
	u0 = tx / w;
	u1 = (tx + tw) / w;
	v0 = ty / h;
	v1 = (ty + th) / h;

	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(Posx, Posy, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(u0, v0);

	vertex[1].Position = XMFLOAT3(Posx + ScaleW, Posy, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(u1, v0);

	vertex[2].Position = XMFLOAT3(Posx, Posy + ScaleH, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(u0, v1);

	vertex[3].Position = XMFLOAT3(Posx + ScaleW, Posy + ScaleH, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(u1, v1);

	D3D11_MAPPED_SUBRESOURCE ms;
	CRenderer::GetDeviceContext()->Map(m_VertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, vertex, sizeof(vertex));
	CRenderer::GetDeviceContext()->Unmap(m_VertexBuffer, NULL);

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;

	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	CRenderer::SetTextureIndex(m_Texture, texNum);
	CRenderer::SetWorldViewProjection2D();
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	CRenderer::GetDeviceContext()->Draw(4, 0);
}

void CPolygon::DrawJpgPng(float Posx, float Posy, float ScaleW, float ScaleH, float R, float G, float B,float Alpha,int texNum)
{
	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(Posx, Posy, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(R, G, B, Alpha);
	vertex[0].TexCoord = XMFLOAT2(0, 0);

	vertex[1].Position = XMFLOAT3(Posx + ScaleW, Posy, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(R, G, B, Alpha);
	vertex[1].TexCoord = XMFLOAT2(1, 0);

	vertex[2].Position = XMFLOAT3(Posx, Posy + ScaleH, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(R, G, B, Alpha);
	vertex[2].TexCoord = XMFLOAT2(0, 1);

	vertex[3].Position = XMFLOAT3(Posx + ScaleW, Posy + ScaleH, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(R, G, B, Alpha);
	vertex[3].TexCoord = XMFLOAT2(1, 1);

	D3D11_MAPPED_SUBRESOURCE ms;
	CRenderer::GetDeviceContext()->Map(m_VertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, vertex, sizeof(vertex));
	CRenderer::GetDeviceContext()->Unmap(m_VertexBuffer, NULL);

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;

	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	CRenderer::SetTextureJPGPNG(m_Texture, texNum);
	CRenderer::SetWorldViewProjection2D();
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	CRenderer::GetDeviceContext()->Draw(4, 0);

}


