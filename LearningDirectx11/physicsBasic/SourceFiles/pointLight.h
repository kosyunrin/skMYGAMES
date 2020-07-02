#pragma once
#define PLMAX 3

struct PointLightSettings
{
	BOOL Enable;
	XMFLOAT3 Position;
	XMFLOAT4 Diffuse;
	XMFLOAT4 Ambient;
	XMFLOAT4 Attenuation;
	float DiffuseStrength;
	float AmbientStrength;
	float Range;
	float Empty;
};

class PointLight
{
private:
	static PointLightSettings settings[PLMAX];

	static ComPtr<ID3D11Buffer> constantBuffer;

public:
	static void Initialize();
	static void Update();

	static void ImGui();

	static PointLightSettings GetSettings(UINT index) { return settings[index]; }
};
