#pragma once
#define SLMAX 1

struct SpotLightSettings
{
	BOOL Enable;
	XMFLOAT3 Position;
	XMFLOAT4 Direction;
	XMFLOAT4 Diffuse;
	XMFLOAT4 Ambient;
	XMFLOAT4 Attenuation;
	float DiffuseStrength;
	float AmbientStrength;
	float Range;
	float Cutoff;
};

class SpotLight
{
private:
	static SpotLightSettings settings[SLMAX];

	static ComPtr<ID3D11Buffer> constantBuffer;

	static XMFLOAT3 offset;
	static XMFLOAT3 at_offset;

public:
	static void Initialize();
	static void Update();

	static void ImGui();

	static SpotLightSettings GetSettings(UINT index) { return settings[index]; }
};
