#pragma once

enum TextureMapID
{
	DiffuseMap,
	NormalMap,
	SpecularMap,
	ReflectionMap,
	ShadowMap,
	TextureMapMax
};

class Texture
{
private:
	ComPtr<ID3D11Resource> rsc;
	ComPtr<ID3D11ShaderResourceView> srv;

	UINT width;
	UINT height;

	void CreateColor(Color color, UINT width, UINT height);
	void CreateTexture(std::string filepath);

public:
	Texture(Color color);
	Texture(Color color, UINT width, UINT height);
	Texture(std::string path);

	void SetTexture(UINT map);

	UINT GetWidth() { return width; }
	UINT GetHeight() { return height; }

	ID3D11ShaderResourceView* GetTexture() { return srv.Get(); }

	static void SetTexture(ID3D11ShaderResourceView* srv, UINT map);
};