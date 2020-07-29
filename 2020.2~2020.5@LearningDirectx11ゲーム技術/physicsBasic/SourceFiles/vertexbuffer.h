#pragma once

struct Vertex
{
	XMFLOAT3 Position;
	XMFLOAT2 TexCoord;
	XMFLOAT3 Normal;
	XMFLOAT3 Tangent;
	XMFLOAT3 Bitangent;
};

struct BonesVertex
{
	XMFLOAT3 Position;
	XMFLOAT2 TexCoord;
	XMFLOAT3 Normal;
	XMFLOAT3 Tangent;
	XMFLOAT3 Bitangent;

	float boneWeights[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	UINT boneID[4] = { 0, 0, 0, 0 };

	void insert(UINT id, float weight)
	{
		for (int index = 0; index < 4; index++)
		{
			if (boneWeights[index] == 0.0f)
			{
				boneID[index] = id;
				boneWeights[index] = weight;
				return;
			}
		}
	}
};

template<class T>
class VertexBuffer
{
public:
	//Creating vertex buffer by passing in the buffer that you want to generate into and data of the vertices.
	static void CreateVertexBuffer(ComPtr<ID3D11Buffer>& buffer, T* vertices, UINT vertexMax)
	{
		D3D11_BUFFER_DESC vertexDesc;
		ZeroMemory(&vertexDesc, sizeof(vertexDesc));
		vertexDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexDesc.ByteWidth = sizeof(T) * vertexMax;
		vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexDesc.CPUAccessFlags = 0;
		vertexDesc.MiscFlags = 0;

		//Vertex subresource data
		D3D11_SUBRESOURCE_DATA vertexsubResourceData;
		ZeroMemory(&vertexsubResourceData, sizeof(vertexsubResourceData));
		vertexsubResourceData.pSysMem = vertices;
		Renderer::GetDevice()->CreateBuffer(&vertexDesc, &vertexsubResourceData, buffer.GetAddressOf());
	}

	//Passing the vertex buffer for shader to render.
	static void SetVertexBuffers(ID3D11Buffer* vertexBuffer)
	{
		UINT stride = sizeof(T);
		UINT offset = 0;
		Renderer::GetContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	}

	//Rendering using line list.
	static void SetLineList(UINT vertexCount, UINT startLocation)
	{
		Renderer::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		Renderer::GetContext()->Draw(vertexCount, startLocation);
	}

	//Rendering using triangle strip.
	static void SetTriangleStrip(UINT vertexCount, UINT startLocation)
	{
		Renderer::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		Renderer::GetContext()->Draw(vertexCount, startLocation);
	}

	//Rendering using triangle list.
	static void SetTriangleList(UINT vertexCount, UINT startLocation)
	{
		Renderer::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Renderer::GetContext()->Draw(vertexCount, startLocation);
	}
};
