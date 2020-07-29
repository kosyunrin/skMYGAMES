#pragma once


typedef unsigned char BYTE;
class MaterialColor
{
public:
	MaterialColor(BYTE r, BYTE g, BYTE b, BYTE a) { this->r = r; this->g = g; this->b = b; this->a = a; }
	

private:
	BYTE r;
	BYTE g;
	BYTE b;
	BYTE a;

};


class Material
{
private:
	ID3D11Resource* texture;
	ID3D11ShaderResourceView* srv;
	aiTextureType type;
	Tool tool;
	//CTexture* m_texture;

public:
	Material(const MaterialColor* color, UINT width, UINT height);
	Material(std::string path);
	Material(std::string path, int num);
	void CreateColorMaterial(const MaterialColor* color, UINT width, UINT height);
	void LoadTexture(std::string filename);
	void loadTga(std::string filename);
	void loadPng(std::string filename);
	void loadDDs(std::string filename);

	ID3D11ShaderResourceView* GetMaterial(void)
	{
		return srv;
	}
};