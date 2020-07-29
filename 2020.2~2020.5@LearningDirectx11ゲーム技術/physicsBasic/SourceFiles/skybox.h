#pragma once

class Skybox :public GameObject
{
private:
	ComPtr<ID3D11Buffer> vertexBuffer;

	XMMATRIX frontMatrix;
	XMMATRIX backMatrix;
	XMMATRIX leftMatrix;
	XMMATRIX rightMatrix;
	XMMATRIX skyMatrix;
	XMMATRIX floorMatrix;

	void Initialize() override;

public:
	Skybox();

	void Update() override;
	void Render(bool boundingBox) override;
};
