#pragma once
class GameObject;

class RTT
{
private:
	ComPtr<ID3D11Texture2D> tex;
	ComPtr<ID3D11RenderTargetView> rtv;
	ComPtr<ID3D11ShaderResourceView> srv;

	UINT width;
	UINT height;

	XMMATRIX viewMatrix;
	XMMATRIX projectionMatrix;

	void Initialize();

public:
	RTT(UINT width, UINT height);

	void Begin();
	void Begin(XMMATRIX viewMatrix, XMMATRIX projectionMatrix);
	void Begin(float y);
	void Begin(GameObject* target, XMFLOAT3 cameraOffset, XMFLOAT3 targetOffset, XMFLOAT3 up);
	void End();

	XMMATRIX GetViewMatrix() { return viewMatrix; }
	XMMATRIX GetProjectionMatrix() { return projectionMatrix; }

	ID3D11ShaderResourceView* GetTexture() { return srv.Get(); }
};