#pragma once
#define BUFFERMAX 2

class DefferredBuffer
{
private:
	ID3D11Texture2D* rtt[BUFFERMAX];
	ID3D11RenderTargetView* rtv[BUFFERMAX];
	ID3D11ShaderResourceView* srv[BUFFERMAX];
	ID3D11Texture2D* depthStencilBuffer;
	ID3D11DepthStencilView* depthStencilView;

	D3D11_VIEWPORT viewport;

	UINT width;
	UINT height;

	void Initialize();

public:
	DefferredBuffer(UINT width, UINT height);
	
	void Begin();
	void End();

	ID3D11ShaderResourceView* GetTexture(int index) { return srv[index]; }
};
