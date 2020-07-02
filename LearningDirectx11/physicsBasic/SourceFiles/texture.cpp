#include <WICTextureLoader.h>
#include "engine.h"
#include "texture.h"

Texture::Texture(Color color)
{
	this->CreateColor(color, 1, 1);
}

Texture::Texture(Color color, UINT width, UINT height)
{
	this->CreateColor(color, width, height);
}

Texture::Texture(std::string path)
{
	this->CreateTexture(path);
}

void Texture::SetTexture(UINT map)
{
	Renderer::GetContext()->PSSetShaderResources(map, 1, srv.GetAddressOf());
}

void Texture::SetTexture(ID3D11ShaderResourceView* srv, UINT map)
{
	Renderer::GetContext()->PSSetShaderResources(map, 1, &srv);
}

void Texture::CreateTexture(std::string filepath)
{
	HRESULT hr;

	std::wstring path = Engine::StringToWString(filepath);

	hr = CreateWICTextureFromFile(Renderer::GetDevice(), path.c_str(), NULL, srv.GetAddressOf());
	if (FAILED(hr))
		Engine::ErrorMsg("Failed to create" + filepath);

	ComPtr<ID3D11Texture2D> pTextureInterface = nullptr;
	ComPtr<ID3D11Resource> resource;
	srv->GetResource(resource.GetAddressOf());
	resource->QueryInterface<ID3D11Texture2D>(pTextureInterface.GetAddressOf());

	D3D11_TEXTURE2D_DESC desc;
	pTextureInterface->GetDesc(&desc);

	this->width = desc.Width;
	this->height = desc.Height;
}

void Texture::CreateColor(Color color, UINT width, UINT height)
{
	HRESULT hr;

	CD3D11_TEXTURE2D_DESC textureDesc(DXGI_FORMAT_R8G8B8A8_UNORM, width, height);
	ComPtr<ID3D11Texture2D> p2DTexture = nullptr;

	D3D11_SUBRESOURCE_DATA initialData{};
	initialData.pSysMem = &color;
	initialData.SysMemPitch = width * sizeof(Color);

	hr = Renderer::GetDevice()->CreateTexture2D(&textureDesc, &initialData, p2DTexture.GetAddressOf());
	if (FAILED(hr))
		Engine::ErrorMsg("Failed to create color texture");

	rsc = static_cast<ComPtr<ID3D11Texture2D>>(p2DTexture.Get());

	CD3D11_SHADER_RESOURCE_VIEW_DESC srvDesc(D3D11_SRV_DIMENSION_TEXTURE2D, textureDesc.Format);

	hr = Renderer::GetDevice()->CreateShaderResourceView(rsc.Get(), &srvDesc, srv.GetAddressOf());
	if (FAILED(hr))
		Engine::ErrorMsg("Failed to create color texture");
}
