#include "engine.h"
#include "shadow.h"

Shadow::Shadow(UINT width, UINT height)
{
	this->rtt = std::make_unique<RTT>(SCREEN_WIDTH, SCREEN_HEIGHT);
	this->blur = std::make_unique<Blur>(SCREEN_WIDTH, SCREEN_HEIGHT);

	this->width = width;
	this->height = height;
	this->factor = 4.0f;
	this->bias = 0.0002f;
	this->shadowColor = 0.45f;

	this->Initialize();
}

void Shadow::Initialize()
{
	HRESULT hr;

	D3D11_TEXTURE2D_DESC tdDesc;
	ZeroMemory(&tdDesc, sizeof(tdDesc));

	tdDesc.Width = this->width;
	tdDesc.Height = this->height;
	tdDesc.MipLevels = 1;
	tdDesc.ArraySize = 1;
	tdDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	tdDesc.SampleDesc.Count = 1;
	tdDesc.SampleDesc.Quality = 0;
	tdDesc.Usage = D3D11_USAGE_DEFAULT;
	tdDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	tdDesc.CPUAccessFlags = 0;
	tdDesc.MiscFlags = 0;

	hr = Renderer::GetDevice()->CreateTexture2D(&tdDesc, NULL, tex.GetAddressOf());

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(dsvDesc));
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;
	hr = Renderer::GetDevice()->CreateDepthStencilView(tex.Get(), &dsvDesc, dsv.GetAddressOf());
 
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	hr = Renderer::GetDevice()->CreateShaderResourceView(tex.Get(), &srvDesc, srv.GetAddressOf());

	if (FAILED(hr))
		Engine::ErrorMsg("Create Shadow Failed");
}

void Shadow::Begin(XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
	ConstantBuffer::SetViewMatrix(&viewMatrix);
	ConstantBuffer::SetProjectionMatrix(&projectionMatrix);

	Renderer::SetViewport(this->width, this->height);

	ComPtr<ID3D11RenderTargetView> rtv[1] = { 0 };
	Renderer::GetContext()->OMSetRenderTargets(1, rtv->GetAddressOf(), dsv.Get());

	float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	Renderer::GetContext()->ClearDepthStencilView(dsv.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void Shadow::End()
{
	Renderer::SetRenderTarget();
	Texture::SetTexture(this->srv.Get(), TextureMapID::ShadowMap);
}

void Shadow::SecondBegin()
{
	rtt->Begin();

	Shader::SetPSShader(PSShaderID::PS_Shadow);
	Shader::SetRestrictShader();

	ConstantBuffer::SetShadowSettings(ShadowSettings(bias, shadowColor));
}

void Shadow::SecondEnd()
{
	ConstantBuffer::SetShadowSettings(ShadowSettings(bias, shadowColor));

	rtt->End();

	Shader::SetRestrictShader();

	Texture::SetTexture(rtt->GetTexture(), TextureMapID::ShadowMap);

	blur->Render(rtt->GetTexture(), (UINT)factor);

	Texture::SetTexture(blur->GetTexture(), TextureMapID::ShadowMap);

	//Reset back to camera matrix
	ConstantBuffer::SetViewMatrix(&Camera::GetViewMatrix());
	ConstantBuffer::SetProjectionMatrix(&Camera::GetProjectionMatrix());
}

void Shadow::ImGui()
{
	ImGui::Begin("Shadow");
	ImGui::DragFloat("Factor", &factor, 0.1f, 0.0f, 10.0f);
	ImGui::DragFloat("Bias", &bias, 0.00001f, 0.00000001f, 10.0f, "%.6f");
	ImGui::DragFloat("ShadowColor", &shadowColor, 0.01f);
	ImGui::End();
}
