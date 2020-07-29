#pragma once
#include"renderer.h"
#include<typeinfo>
template <typename T>
class CIndexBuffer
{
public:
	static ID3D11Buffer* CreatIndexBuffer(WORD* indices_W,DWORD*indices_D,  UINT indexMax)
	{
		ID3D11Buffer* m_indexBufferx = NULL;
		//indexbuffer
		if (typeid(T) == typeid(WORD))
		{
			D3D11_BUFFER_DESC indexM;//ｼﾇﾂｼ4ｸ羞ﾄﾄﾚｴ・
			ZeroMemory(&indexM, sizeof(indexM));
			indexM.Usage = D3D11_USAGE_DEFAULT;//ﾓﾃﾍｾ
			indexM.ByteWidth = sizeof(WORD) * indexMax;//ｻｺｴ豬ﾄｴ｡
			indexM.BindFlags = D3D11_BIND_INDEX_BUFFER;// ｶｨﾒ衢・ﾇﾊｲﾃｴﾊｲﾃｴﾄﾚｴ・
			indexM.CPUAccessFlags = 0;//

			D3D11_SUBRESOURCE_DATA sd0;//ｸｭｴ・ﾃｵﾄﾄﾚｴ・
			ZeroMemory(&sd0, sizeof(sd0));
			sd0.pSysMem = indices_W;
			CRenderer::GetDevice()->CreateBuffer(&indexM, &sd0, &m_indexBufferx);
			return m_indexBufferx;
		}
		else if (typeid(T) == typeid(DWORD))
		{
			D3D11_BUFFER_DESC indexM;//ｼﾇﾂｼ4ｸ羞ﾄﾄﾚｴ・
			ZeroMemory(&indexM, sizeof(indexM));
			indexM.Usage = D3D11_USAGE_DEFAULT;//ﾓﾃﾍｾ
			indexM.ByteWidth = sizeof(DWORD) * indexMax;//ｻｺｴ豬ﾄｴ｡
			indexM.BindFlags = D3D11_BIND_INDEX_BUFFER;// ｶｨﾒ衢・ﾇﾊｲﾃｴﾊｲﾃｴﾄﾚｴ・
			indexM.CPUAccessFlags = 0;//

			D3D11_SUBRESOURCE_DATA sd0;//ｸｭｴ・ﾃｵﾄﾄﾚｴ・
			ZeroMemory(&sd0, sizeof(sd0));
			sd0.pSysMem = indices_D;
			CRenderer::GetDevice()->CreateBuffer(&indexM, &sd0, &m_indexBufferx);
			return m_indexBufferx;
		}
	}
	static void SetIndexBuffer(ID3D11Buffer* IndexBuffer)
	{
		if(typeid(T)== typeid(DWORD))
		CRenderer::GetDeviceContext()->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		else if(typeid(T) == typeid(WORD))
		CRenderer::GetDeviceContext()->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	}
	static void DRAW_TOPOLOGY_LINELIST(UINT indexMax)
	{
		CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		CRenderer::GetDeviceContext()->DrawIndexed(indexMax, 0, 0);
	}
	static void DRAW_TOPOLOGY_TRIANGLELIST(UINT indexMax)
	{
		CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		CRenderer::GetDeviceContext()->DrawIndexed(indexMax,0, 0);
	}
	static void DRAW_TOPOLOGY_TRIANGLELIST_INSTANCE(UINT indexMax,UINT instanceSize)
	{
		CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		CRenderer::GetDeviceContext()->DrawIndexedInstanced(indexMax, instanceSize, 0,0,0);
	}

private:

};

