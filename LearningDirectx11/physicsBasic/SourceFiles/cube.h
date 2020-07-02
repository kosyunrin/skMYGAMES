#pragma once

class Cube :public GameObject
{
private:
	ComPtr<ID3D11Buffer> vertexBuffer;
	ComPtr<ID3D11Buffer> indexBuffer;

	std::vector<XMFLOAT3> vertices;
	std::vector<DWORD> indices;

	UINT ID;

	float seamx;
	float seamy;
	float seamz;

	void Initialize() override;

public:
	Cube(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scaling, UINT ID);

	void Update() override;
	void Render(bool boundingBox) override;

	std::vector<XMFLOAT3> GetVertices() { return vertices; }
	std::vector<DWORD> GetIndices() { return indices; }
};
