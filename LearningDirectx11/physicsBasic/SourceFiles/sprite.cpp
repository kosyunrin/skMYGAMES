#include "engine.h"
#include "sprite.h"

ComPtr<ID3D11Buffer> Sprite::vertexBuffer = nullptr;

void Sprite::Initialize()
{
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));

	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = sizeof(Vertex) * 4;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	Renderer::GetDevice()->CreateBuffer(&bufferDesc, NULL, vertexBuffer.GetAddressOf());
}

/*--------------------------------------------------------------------------------
Render
--------------------------------------------------------------------------------*/
void Sprite::Render(float dx, float dy, float dw, float dh, UINT ID)
{
	Vertex vertex[] =
	{
		{ XMFLOAT3(dx, dy, 0.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(dx + dw, dy, 0.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(dx, dy + dh, 0.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(dx + dw, dy + dh, 0.0f), XMFLOAT2(1.0f, 1.0f) }
	};

	D3D11_MAPPED_SUBRESOURCE ms;
	Renderer::GetContext()->Map(vertexBuffer.Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, vertex, sizeof(vertex));
	Renderer::GetContext()->Unmap(vertexBuffer.Get(), NULL);

	Material::SetTexture(ID, TextureMapID::DiffuseMap);

	VertexBuffer<Vertex>::SetVertexBuffers(vertexBuffer.Get());
	ConstantBuffer::SetWorldMatrix2D();
	VertexBuffer<Vertex>::SetTriangleStrip(4, 0);
}

void Sprite::Render(float dx, float dy, float dw, float dh, ID3D11ShaderResourceView* srv)
{
	Vertex vertex[] =
	{
		{ XMFLOAT3(dx, dy, 0.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(dx + dw, dy, 0.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(dx, dy + dh, 0.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(dx + dw, dy + dh, 0.0f), XMFLOAT2(1.0f, 1.0f) }
	};

	D3D11_MAPPED_SUBRESOURCE ms;
	Renderer::GetContext()->Map(vertexBuffer.Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, vertex, sizeof(vertex));
	Renderer::GetContext()->Unmap(vertexBuffer.Get(), NULL);

	Texture::SetTexture(srv, TextureMapID::DiffuseMap);

	VertexBuffer<Vertex>::SetVertexBuffers(vertexBuffer.Get());
	ConstantBuffer::SetWorldMatrix2D();
	VertexBuffer<Vertex>::SetTriangleStrip(4, 0);
}

/*--------------------------------------------------------------------------------
Sprite Render
--------------------------------------------------------------------------------*/
void Sprite::SpriteRender(float dx, float dy, float dw, float dh, UINT ID, UINT x, UINT y, float speed)
{
	//Calculate use variable
	UINT tx, ty, tw, th;
	UINT textureWidth = Material::GetTexture(ID).GetWidth();
	UINT textureHeight = Material::GetTexture(ID).GetHeight();

	//Calculate the part use of the frame
	UINT count = (UINT)speed % (x * y);

	tx = count * textureWidth / x;
	ty = count / y;
	tw = textureWidth / x;
	th = textureHeight / y;

	float u0 = (float)tx / textureWidth;
	float v0 = (float)ty / textureHeight;
	float u1 = (float)(tx + tw) / textureWidth;
	float v1 = (float)(ty + th) / textureHeight;

	Vertex vertex[] =
	{
		{ XMFLOAT3(dx, dy, 0.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(dx + dw, dy, 0.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(dx, dy + dh, 0.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(dx + dw, dy + dh, 0.0f), XMFLOAT2(1.0f, 1.0f) }
	};

	D3D11_MAPPED_SUBRESOURCE ms;
	Renderer::GetContext()->Map(vertexBuffer.Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, vertex, sizeof(vertex));
	Renderer::GetContext()->Unmap(vertexBuffer.Get(), NULL);

	Material::SetTexture(ID, TextureMapID::DiffuseMap);

	VertexBuffer<Vertex>::SetVertexBuffers(vertexBuffer.Get());
	ConstantBuffer::SetWorldMatrix2D();
	VertexBuffer<Vertex>::SetTriangleStrip(4, 0);
}