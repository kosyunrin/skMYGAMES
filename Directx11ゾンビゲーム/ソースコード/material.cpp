#include"main.h"
#include"renderer.h"
#include "material.h"
#include"texture.h"
#include <WICTextureLoader.h>
Material::Material(const MaterialColor* color, UINT width, UINT height)
{
	this->CreateColorMaterial(color, width, height);
}

Material::Material(std::string path)
{
	std::string asd = path;
	int xx = path.length() - 3;
	asd = asd.erase(0, xx);

	if (asd == "png"|| asd == "dds")
	{
		this->LoadTexture(path);
		if (this->srv == nullptr)
			this->loadPng(path);
	}
	else if (asd == "jpg")
		this->LoadTexture(path);
	else if (asd==("tga"))
		this->loadTga(path);
	else if(asd == ("dds"))
		this->loadDDs(path);

	if(asd!="dds")
	assert(this->srv);

	
}

Material::Material(std::string path, int num)
{
	//switch (num)
	//{
	//case 0:
	//{
	//	std::string asd = path;
	//	int xx = path.length() - 3;
	//	asd = asd.erase(0, xx);

	//	if (asd == "png" || asd == "dds")
	//	{
	//		this->LoadTexture(path);
	//		if (this->srv == nullptr)
	//			this->loadPng(path);
	//	}
	//	else if (asd == "jpg")
	//		this->LoadTexture(path);
	//	else if (asd == ("tga"))
	//		this->loadTga(path);
	//	else if (asd == ("dds"))
	//		this->loadDDs(path);

	//	if (asd != "dds")
	//		assert(this->srv);
	//}
	//	break;
	//case 1:
	//	loadDDs(path);
	//	break;
	//case 2:
	//	LoadTexture(path);
	//	break;
	//}
	loadDDs(path);

}


void Material::CreateColorMaterial(const MaterialColor* color, UINT width, UINT height)
{
	HRESULT hr;

	CD3D11_TEXTURE2D_DESC textureDesc(DXGI_FORMAT_R8G8B8A8_UNORM, width, height);
	ID3D11Texture2D* p2DTexture = nullptr;

	D3D11_SUBRESOURCE_DATA initialData{};
	initialData.pSysMem = color;
	initialData.SysMemPitch = width * sizeof(MaterialColor);

	hr = CRenderer::GetDevice()->CreateTexture2D(&textureDesc, &initialData, &p2DTexture);
	if (FAILED(hr))
	{
		MessageBox(0, "Failed To Initialize Texture From Color Data",
			"Error", MB_OK);
		return;
	}

	texture = static_cast<ID3D11Texture2D*>(p2DTexture);

	CD3D11_SHADER_RESOURCE_VIEW_DESC srvDesc(D3D11_SRV_DIMENSION_TEXTURE2D, textureDesc.Format);

	hr = CRenderer::GetDevice()->CreateShaderResourceView(texture, &srvDesc, &this->srv);
	if (FAILED(hr))
	{
		MessageBox(0, "Failed To Generate Color Material",
			"Error", MB_OK);
		return;

	}
}

void Material::LoadTexture(std::string filename)
{
		HRESULT hr;

		std::wstring path = tool.StringToWstring(filename);//
		hr = CreateWICTextureFromFile(CRenderer::GetDevice(), path.c_str(), nullptr, &this->srv);
}

void Material::loadTga(std::string filename)
{
	std::string path = "asset/Onepiece/TGA/" + filename;
	CTexture*m_texture=new CTexture();
	m_texture->Load(path.c_str());
	this->srv = m_texture->GetShaderResourceView();
	assert(this->srv);
	
}

void Material::loadPng(std::string filename)
{
	std::string asd = filename;
	int xx = filename.length() - 3;
	asd = asd.erase(0, xx);
	if (asd == "dds")
		return;
	std::wstring FileName = tool.StringToWstringDX(filename);
	CTexture*m_texture = new CTexture();
	m_texture->LoadAny(FileName.c_str());
	this->srv = m_texture->GetShaderResourceView();
	//assert(this->srv);
	//assert(this->srv);
}

void Material::loadDDs(std::string filename)
{
	HRESULT hr;
	std::string paths = "DDS/" + filename;
	std::wstring path = tool.StringToWstring(paths);//
	hr = CreateDDSTextureFromFile(CRenderer::GetDevice(), path.c_str(), nullptr, &this->srv);
	if (this->srv == nullptr)
	{
		int sd = 2.0f;
	}
}
