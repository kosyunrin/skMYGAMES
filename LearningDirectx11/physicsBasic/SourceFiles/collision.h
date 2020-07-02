#pragma once

class Collision
{
private:
	std::vector<XMFLOAT3> vertices;
	std::vector<DWORD> indices;

	XMMATRIX worldMatrix;

	BoundingBox* boundingBox;

public:
	void Initialize(std::vector<XMFLOAT3> vertices, std::vector<DWORD> indices);
	void Update(XMMATRIX worldMatrix);
	void Update(std::vector<XMFLOAT3> vertices, std::vector<DWORD> indices);
	void Render();

	std::vector<XMFLOAT3> GetVertices() { return vertices; }
	std::vector<DWORD> GetIndices() { return indices; }

	XMMATRIX GetWorldMatrix() { return worldMatrix; }

	BoundingBox* GetBoundingBox() { return boundingBox; }
};
