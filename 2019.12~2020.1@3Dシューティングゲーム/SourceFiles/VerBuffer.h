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

		D3D11_BUFFER_DESC vetexMemory;//ｼﾇﾂｼ4ｸ羞ﾄﾄﾚｴ・
		ZeroMemory(&vetexMemory, sizeof(vetexMemory));
		vetexMemory.Usage = D3D11_USAGE_DEFAULT;//ﾓﾃﾍｾ
		vetexMemory.ByteWidth = sizeof(T) * vertexMax;//ｻｺｴ豬ﾄｴ｡
		vetexMemory.BindFlags = D3D11_BIND_VERTEX_BUFFER;// ｶｨﾒ衢・ﾇﾊｲﾃｴﾊｲﾃｴﾄﾚｴ・
		vetexMemory.CPUAccessFlags = 0;//

		D3D11_SUBRESOURCE_DATA sd;//ｸｭｴ・ﾃｵﾄﾄﾚｴ・
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

