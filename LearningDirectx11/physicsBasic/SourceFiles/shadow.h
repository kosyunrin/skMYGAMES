#pragma once

class Shadow
{
private:
	std::unique_ptr<RTT> rtt;
	std::unique_ptr<Blur> blur;

	ComPtr<ID3D11Texture2D> tex;
	ComPtr<ID3D11DepthStencilView> dsv;
	ComPtr<ID3D11ShaderResourceView> srv;

	UINT width;
	UINT height;

	float factor;
	float bias;
	float shadowColor;

	void Initialize();

public:
	Shadow(UINT width, UINT height);

	void Begin(XMMATRIX viewMatrix, XMMATRIX projectionMatrix);
	void End();
	void SecondBegin();
	void SecondEnd();

	void ImGui();

	ID3D11ShaderResourceView* GetTexture() { return blur->GetTexture(); }
};