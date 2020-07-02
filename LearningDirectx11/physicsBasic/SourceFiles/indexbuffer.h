#pragma once

class IndexBuffer
{
public:
	//Creating index buffer by passing in the buffer that you want to generate into and data of the indices.
	static void CreateIndexBuffer(ComPtr<ID3D11Buffer>& buffer, DWORD* indices, UINT indexMax)
	{
		D3D11_BUFFER_DESC indexDesc;
		ZeroMemory(&indexDesc, sizeof(indexDesc));
		indexDesc.Usage = D3D11_USAGE_DEFAULT;
		indexDesc.ByteWidth = sizeof(DWORD) * indexMax;
		indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexDesc.CPUAccessFlags = 0;
		indexDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA indexSubResourceData;
		indexSubResourceData.pSysMem = indices;
		Renderer::GetDevice()->CreateBuffer(&indexDesc, &indexSubResourceData, buffer.GetAddressOf());
	}

	//Passing the index buffer for shader to render.
	static void SetIndexBuffer(ID3D11Buffer* indexBuffer)
	{
		Renderer::GetContext()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	}

	//Rendering using triangle list.
	static void SetTriangleList(UINT indexCount, UINT startLocation, UINT baseLocation)
	{
		Renderer::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Renderer::GetContext()->DrawIndexed(indexCount, startLocation, baseLocation);
	}
};
