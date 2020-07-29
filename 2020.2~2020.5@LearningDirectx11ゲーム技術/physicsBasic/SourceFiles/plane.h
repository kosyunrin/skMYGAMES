#pragma once

class Plane :public GameObject
{
private:
	ComPtr<ID3D11Buffer> vertexBuffer;
	ComPtr<ID3D11Buffer> indexBuffer;

	std::vector<XMFLOAT3> vertices;
	std::vector<DWORD> indices;

	UINT ID;

	float seamx;
	float seamz;

	bool enableReflection;

	void Initialize() override;

public:
	Plane(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scaling, UINT ID);

	void Update() override;
	void Render(bool boundingBox) override;

	void SetReflection(bool b) { enableReflection = b; }
};
