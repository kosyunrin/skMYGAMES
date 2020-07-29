#pragma once

class BoundingBox
{
private:
	ComPtr<ID3D11Buffer> vertexBuffer;

	XMFLOAT3 v[8];

	XMFLOAT3 min;
	XMFLOAT3 max;
	XMFLOAT3 minWorld;
	XMFLOAT3 maxWorld;

	XMMATRIX worldMatrix;

	std::vector<XMFLOAT3> boundingVertices;
	std::vector<XMFLOAT3> boundingVerticesWorld;

public:
	void Initialize(std::vector<XMFLOAT3> vertices);
	void Update(XMMATRIX worldMatrix);
	void Update(std::vector<XMFLOAT3> vertices);
	void Render();

	XMFLOAT3 GetMinWorld() { return minWorld; }
	XMFLOAT3 GetMaxWorld() { return maxWorld; }

	XMMATRIX GetWorldMatrix() { return worldMatrix; }

	std::vector<XMFLOAT3> GetVertices() { return boundingVertices; }
	std::vector<XMFLOAT3> GetWorldVertices() { return boundingVerticesWorld; }
};
