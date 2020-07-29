#include "engine.h"
#include "defferredBuffer.h"

DefferredBuffer::DefferredBuffer(UINT width, UINT height)
{
	this->width = width;
	this->height = height;
	this->Initialize();
}

void DefferredBuffer::Initialize()
{
	HRESULT hr;

	D3D11_TEXTURE2D_DESC tdDesc;
	ZeroMemory(&tdDesc, sizeof(tdDesc));

	tdDesc.Width = width;
	tdDesc.Height = height;
	tdDesc.MipLevels = 1;
	tdDesc.ArraySize = 1;
	tdDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	tdDesc.SampleDesc.Count = 1;
	tdDesc.Usage = D3D11_USAGE_DEFAULT;
	tdDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	tdDesc.CPUAccessFlags = 0;
	tdDesc.MiscFlags = 0;

	for (int index = 0; index < BUFFERMAX; index++)
		hr = Renderer::GetDevice()->CreateTexture2D(&tdDesc, NULL, &rtt[index]);

	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	rtvDesc.Format = tdDesc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0;

	for (int index = 0; index < BUFFERMAX; index++)
		hr = Renderer::GetDevice()->CreateRenderTargetView(rtt[index], &rtvDesc, &rtv[index]);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = tdDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	for (int index = 0; index < BUFFERMAX; index++)
		hr = Renderer::GetDevice()->CreateShaderResourceView(rtt[index], &srvDesc, &srv[index]);
	if (FAILED(hr))
		Engine::ErrorMsg("Create Defferred Buffer Failed");
}

void DefferredBuffer::Begin()
{
	Renderer::GetContext()->OMSetRenderTargets(BUFFERMAX, rtv, Renderer::GetDepthStencilView());

	float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	for(int index = 0; index < BUFFERMAX; index++)
		Renderer::GetContext()->ClearRenderTargetView(rtv[index], color);
	Renderer::GetContext()->ClearDepthStencilView(Renderer::GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	Renderer::SetViewport(width, height);

	ConstantBuffer::SetViewMatrix(&Camera::GetViewMatrix());
	ConstantBuffer::SetProjectionMatrix(&Camera::GetProjectionMatrix());
}

void DefferredBuffer::End()
{
	Renderer::SetRenderTarget();

	Renderer::SetViewport(SCREEN_WIDTH, SCREEN_HEIGHT);
}