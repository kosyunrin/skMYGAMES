#pragma once

struct DirectionLightSettings
{
	BOOL Enable;
	XMFLOAT3 Position;
	XMFLOAT4 Direction;
	XMFLOAT4 Diffuse;
	XMFLOAT4 Ambient;
	XMMATRIX ViewMatrix;
	XMMATRIX ProjectionMatrix;
	XMMATRIX ViewTransMatrix;
	XMMATRIX ProjectionTransMatrix;
};

class DirectionLight
{
private:
	static DirectionLightSettings settings;

	static ComPtr<ID3D11Buffer> VSBuffer;
	static ComPtr<ID3D11Buffer> PSBuffer;

	static XMFLOAT3 offset;

public:
	static void Initialize();
	static void Update();

	static void ImGui();

	static DirectionLightSettings GetSettings() { return settings; }
};