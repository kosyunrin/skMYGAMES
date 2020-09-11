
#include "main.h"
#include "renderer.h"
#include "texture.h"

CTexture::CTexture(const char * path)
{
}

void CTexture::LoadALLTga()
{
	unsigned char	header[18];
	unsigned char	*image;
	unsigned int	width, height;
	unsigned char	depth;
	unsigned int	bpp;
	unsigned int	size;

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		// ヘッダ読み込み
		FILE* file;
		file = fopen(g_Files[i].name, "rb");
		assert(file);

		fread(header, sizeof(header), 1, file);


		// 画像サイズ取得
		g_Files[i].width = header[13] * 256 + header[12];
		g_Files[i].height = header[15] * 256 + header[14];
		depth = header[16];

		if (depth == 32)
			bpp = 4;
		else if (depth == 24)
			bpp = 3;
		else
			bpp = 0;

		if (bpp != 4) {
			assert(false);
		}

		size = g_Files[i].width * g_Files[i].height * bpp;

		// メモリ確保
		image = (unsigned char*)new unsigned char[size];

		// 画像読み込み
		fread(image, size, 1, file);

		// R<->B
		for (unsigned int y = 0; y < g_Files[i].height; y++)
		{
			for (unsigned int x = 0; x < g_Files[i].width; x++)
			{
				unsigned char c;
				c = image[(y * g_Files[i].width + x) * bpp + 0];
				image[(y * g_Files[i].width + x) * bpp + 0] = image[(y * g_Files[i].width + x) * bpp + 2];
				image[(y * g_Files[i].width + x) * bpp + 2] = c;
			}
		}

		fclose(file);


		D3D11_TEXTURE2D_DESC desc;
		desc.Width = g_Files[i].width;
		desc.Height = g_Files[i].height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = image;
		initData.SysMemPitch = g_Files[i].width * 4;
		initData.SysMemSlicePitch = size;

		auto hr = CRenderer::GetDevice()->CreateTexture2D(&desc, &initData, &m_Texture);
		if (FAILED(hr)) {
			assert(false);
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
		SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		SRVDesc.Texture2D.MipLevels = 1;

		hr = CRenderer::GetDevice()->CreateShaderResourceView(m_Texture, &SRVDesc, &g_Files[i].m_ShaderResourceView);
		if (FAILED(hr))
		{
			assert(false);
		}


		delete image;
	}
}

void CTexture::Load(const char *FileName)
{/*
	HRESULT hrs;
	hrs = CreateDDSTextureFromFile(CRenderer::GetDevice(), L"skymap.dds", nullptr, &m_ShaderResourceView);
	if (FAILED(hrs))
	{
		MessageBox(nullptr, "create texture failed!", "error", MB_OK);
		return hrs;
	}*/

	unsigned char	header[18];
	unsigned char	*image;
	unsigned int	width, height;
	unsigned char	depth;
	unsigned int	bpp;
	unsigned int	size;


	// ヘッダ読み込み
	FILE* file;
	file = fopen(FileName, "rb");
	assert(file);

	fread(header, sizeof(header), 1, file);


	// 画像サイズ取得
	width = header[13] * 256 + header[12];
	height = header[15] * 256 + header[14];
	depth = header[16];

	if (depth == 32)
		bpp = 4;
	else if (depth == 24)
		bpp = 3;
	else
		bpp = 0;

	if (bpp != 4) {
		assert(false);
	}

	size = width * height * bpp;

	// メモリ確保
	image = (unsigned char*)new unsigned char[size];

	// 画像読み込み
	fread(image, size, 1, file);

	// R<->B
	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			unsigned char c;
			c = image[(y * width + x) * bpp + 0];
			image[(y * width + x) * bpp + 0] = image[(y * width + x) * bpp + 2];
			image[(y * width + x) * bpp + 2] = c;
		}
	}

	fclose(file);


	D3D11_TEXTURE2D_DESC desc;
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = image;
	initData.SysMemPitch = width * 4;
	initData.SysMemSlicePitch = size;

	auto hr = CRenderer::GetDevice()->CreateTexture2D(&desc, &initData, &m_Texture);
	if (FAILED(hr)) {
		assert(false);//bug
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
	SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;

	hr = CRenderer::GetDevice()->CreateShaderResourceView(m_Texture, &SRVDesc, &m_ShaderResourceView);
	if (FAILED(hr))
	{
		assert(false);
	}


	delete image;
}
void CTexture::LoadAny(const wchar_t * FileName)
{
	//创建采样状态对象
	//D3D11_SAMPLER_DESC samDesc;
	//ZeroMemory(&samDesc, sizeof(samDesc));
	//samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;//LINEAR，线性采样。物体远离或靠近时，表面纹理能够平滑过渡
	//samDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;//它的好处就是只需要使用很少量的数据就可以达到整个覆盖的效果
	//samDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	//samDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	//samDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	//samDesc.MinLOD = 0;
	//samDesc.MaxLOD = D3D11_FLOAT32_MAX;
	HRESULT hr;
	hr = CreateWICTextureFromFile(CRenderer::GetDevice(), FileName, nullptr, &m_ShaderResourceView);
}

void CTexture::LoadAnyJpgPng()
{
	for (int i = 0; i < TEXTURE_JpgPngMAX; i++)
	{
		HRESULT hr;
		hr = CreateWICTextureFromFile(CRenderer::GetDevice(), Go_OpenJpgPng[i].name, nullptr, &Go_OpenJpgPng[i].m_ShaderResourceView);
	}
}

void CTexture::LoadPJtexture(int texNumber)
{
		HRESULT hr;
		hr = CreateWICTextureFromFile(CRenderer::GetDevice(), Go_OpenJpgPng[texNumber].name, nullptr, &Go_OpenJpgPng[texNumber].m_ShaderResourceView);
}

void CTexture::LoadTga(int number)
{
	unsigned char	header[18];
	unsigned char	*image;
	unsigned int	width, height;
	unsigned char	depth;
	unsigned int	bpp;
	unsigned int	size;

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		// ヘッダ読み込み
		FILE* file;
		file = fopen(g_Files[number].name, "rb");
		assert(file);

		fread(header, sizeof(header), 1, file);


		// 画像サイズ取得
		g_Files[number].width = header[13] * 256 + header[12];
		g_Files[number].height = header[15] * 256 + header[14];
		depth = header[16];

		if (depth == 32)
			bpp = 4;
		else if (depth == 24)
			bpp = 3;
		else
			bpp = 0;

		if (bpp != 4) {
			assert(false);
		}

		size = g_Files[number].width * g_Files[number].height * bpp;

		// メモリ確保
		image = (unsigned char*)new unsigned char[size];

		// 画像読み込み
		fread(image, size, 1, file);

		// R<->B
		for (unsigned int y = 0; y < g_Files[number].height; y++)
		{
			for (unsigned int x = 0; x < g_Files[number].width; x++)
			{
				unsigned char c;
				c = image[(y * g_Files[number].width + x) * bpp + 0];
				image[(y * g_Files[number].width + x) * bpp + 0] = image[(y * g_Files[number].width + x) * bpp + 2];
				image[(y * g_Files[number].width + x) * bpp + 2] = c;
			}
		}

		fclose(file);


		D3D11_TEXTURE2D_DESC desc;
		desc.Width = g_Files[number].width;
		desc.Height = g_Files[number].height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = image;
		initData.SysMemPitch = g_Files[number].width * 4;
		initData.SysMemSlicePitch = size;

		auto hr = CRenderer::GetDevice()->CreateTexture2D(&desc, &initData, &m_Texture);
		if (FAILED(hr)) {
			assert(false);
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
		SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		SRVDesc.Texture2D.MipLevels = 1;

		hr = CRenderer::GetDevice()->CreateShaderResourceView(m_Texture, &SRVDesc, &g_Files[number].m_ShaderResourceView);
		if (FAILED(hr))
		{
			assert(false);
		}


		delete image;
	}
}

void CTexture::LoadDDs(const wchar_t * FileName)
{
	HRESULT hr;
	hr = CreateDDSTextureFromFile(CRenderer::GetDevice(), FileName, nullptr, &m_ShaderResourceView);
}



void CTexture::Unload()
{
	//m_Texture->Release();
	m_ShaderResourceView->Release();
}

void CTexture::UnloadAllTga()
{
	for (int i = 0; i < TEXTURE_MAX; i++)
	{

		g_Files[i].m_ShaderResourceView->Release();
	}
}

void CTexture::UnloadAllJpgPng()
{
	for (int i = 0; i < TEXTURE_JpgPngMAX; i++)
	{
		Go_OpenJpgPng[i].m_ShaderResourceView->Release();
	}
}

void CTexture::UnloadPJtex(int tex)
{
	Go_OpenJpgPng[tex].m_ShaderResourceView->Release();
}

void CTexture::UnloadTag(int number)
{
	g_Files[number].m_ShaderResourceView->Release();
}

ID3D11ShaderResourceView * CTexture::Gettex()
{
	return m_ShaderResourceView;
}

ID3D11ShaderResourceView * CTexture::GetShaderResourceViewIndex(int texture)
{
	return g_Files[texture].m_ShaderResourceView;
}

ID3D11ShaderResourceView * CTexture::GetShaderResourceViewJpgPng(int texture)
{
	return Go_OpenJpgPng[texture].m_ShaderResourceView;
}

int CTexture::Texture_GetWidth(int texture)
{
	return g_Files[texture].width;
}

int CTexture::Texture_GetHeight(int texture)
{
	return g_Files[texture].height;
}






