#pragma once

class Blur
{
private:
	std::unique_ptr<RTT> rtt;

	ComPtr<ID3D11ShaderResourceView> srv;

	UINT width;
	UINT height;

public:
	Blur(UINT width, UINT height);
	
	void Render(ComPtr<ID3D11ShaderResourceView> srv, UINT factor);

	ID3D11ShaderResourceView* GetTexture() { return srv.Get(); }
};