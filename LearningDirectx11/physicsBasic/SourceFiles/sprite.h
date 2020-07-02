#pragma once

class Sprite
{
private:
	static ComPtr<ID3D11Buffer> vertexBuffer;

public:
	static void Initialize();

	static void Render(float dx, float dy, float dw, float dh, UINT ID);
	static void Render(float dx, float dy, float dw, float dh, ID3D11ShaderResourceView* srv);
	static void SpriteRender(float dx, float dy, float dw, float dh, UINT ID, UINT x, UINT y, float speed);
};
