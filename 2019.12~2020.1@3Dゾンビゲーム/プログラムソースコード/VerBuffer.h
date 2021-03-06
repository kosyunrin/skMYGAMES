#pragma once
#include"renderer.h"
template <typename T>
class CVertexBuffer
{
public:
	//VerBuffer();
	//~VerBuffer();
	
	static ID3D11Buffer* CreatVertexBuffer(T* vertices,UINT vertexMax )
	{
		ID3D11Buffer* m_VertexBufferx = NULL;

		D3D11_BUFFER_DESC vetexMemory;//记录4个点的内磥E
		ZeroMemory(&vetexMemory, sizeof(vetexMemory));
		vetexMemory.Usage = D3D11_USAGE_DEFAULT;//用途
		vetexMemory.ByteWidth = sizeof(T) * vertexMax;//缓存的大小
		vetexMemory.BindFlags = D3D11_BIND_VERTEX_BUFFER;// 定义藖E鞘裁词裁茨诖丒
		vetexMemory.CPUAccessFlags = 0;//

		D3D11_SUBRESOURCE_DATA sd;//给协磥E玫哪诖丒
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = vertices;
		CRenderer::GetDevice()->CreateBuffer(&vetexMemory, &sd, &m_VertexBufferx);
		return m_VertexBufferx;
	}
	static void SetVertexBuffer( ID3D11Buffer* VertexBuffer)
	{
		UINT stride = sizeof(T);
		UINT offset = 0;
		ID3D11Buffer* vb[1] = { VertexBuffer };
		CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
	}

private:

};

