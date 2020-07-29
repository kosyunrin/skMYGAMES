#include "engine.h"
#include "RTT.h"

RTT::RTT(UINT width, UINT height)
{
	this->width = width;
	this->height = height;
	this->Initialize();
}

void RTT::Initialize()
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

	hr = Renderer::GetDevice()->CreateTexture2D(&tdDesc, NULL, tex.GetAddressOf());
	
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	rtvDesc.Format = tdDesc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0;
	hr = Renderer::GetDevice()->CreateRenderTargetView(tex.Get(), &rtvDesc, rtv.GetAddressOf());

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = tdDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	hr = Renderer::GetDevice()->CreateShaderResourceView(tex.Get(), &srvDesc, srv.GetAddressOf());
	if (FAILED(hr))
		Engine::ErrorMsg("Create RTT Failed");
}

/*--------------------------------------------------------------------------------
RTT
--------------------------------------------------------------------------------*/
void RTT::Begin()
{
	Renderer::GetContext()->OMSetRenderTargets(1, rtv.GetAddressOf(), Renderer::GetDepthStencilView());

	float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	Renderer::GetContext()->ClearRenderTargetView(rtv.Get(), color);
	Renderer::GetContext()->ClearDepthStencilView(Renderer::GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	Renderer::SetViewport(width, height);

	viewMatrix = Camera::GetViewMatrix();
	ConstantBuffer::SetViewMatrix(&viewMatrix);

	projectionMatrix = Camera::GetProjectionMatrix();
	ConstantBuffer::SetProjectionMatrix(&projectionMatrix);
}

void RTT::Begin(XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
	Renderer::GetContext()->OMSetRenderTargets(1, rtv.GetAddressOf(), Renderer::GetDepthStencilView());

	float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	Renderer::GetContext()->ClearRenderTargetView(rtv.Get(), color);
	Renderer::GetContext()->ClearDepthStencilView(Renderer::GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	Renderer::SetViewport(width, height);

	ConstantBuffer::SetViewMatrix(&viewMatrix);
	ConstantBuffer::SetProjectionMatrix(&projectionMatrix);
}

/*--------------------------------------------------------------------------------
Reflection
--------------------------------------------------------------------------------*/
void RTT::Begin(float y)
{
	Renderer::GetContext()->OMSetRenderTargets(1, rtv.GetAddressOf(), Renderer::GetDepthStencilView());

	float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	Renderer::GetContext()->ClearRenderTargetView(rtv.Get(), color);
	Renderer::GetContext()->ClearDepthStencilView(Renderer::GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	Renderer::SetViewport(width, height);

	XMFLOAT3 position = Camera::GetPosition();
	XMFLOAT3 rotation = Camera::GetRotation();

	XMVECTOR positionVec = XMVectorSet(position.x, y - (position.y - y), position.z, 1.0f);

	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(XMConvertToRadians(rotation.x), XMConvertToRadians(rotation.y), XMConvertToRadians(rotation.z));
	XMVECTOR atVec = XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);
	atVec = XMVector3TransformCoord(atVec, rotationMatrix);
	XMVECTOR upVec = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	upVec = XMVector3TransformCoord(upVec, rotationMatrix);

	atVec = atVec + positionVec;

	viewMatrix = XMMatrixLookAtLH(positionVec, atVec, upVec);
	ConstantBuffer::SetViewMatrix(&viewMatrix);
	ConstantBuffer::SetReflectionMatrix(&viewMatrix);

	projectionMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(60.0f), (float)width / (float)height, 1.0f, 1000.0f);
	ConstantBuffer::SetProjectionMatrix(&projectionMatrix);
}

/*--------------------------------------------------------------------------------
GameObject LookAt
--------------------------------------------------------------------------------*/
void RTT::Begin(GameObject* target, XMFLOAT3 cameraOffset, XMFLOAT3 targetOffset, XMFLOAT3 up)
{
	Renderer::GetContext()->OMSetRenderTargets(1, rtv.GetAddressOf(), Renderer::GetDepthStencilView());

	float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	Renderer::GetContext()->ClearRenderTargetView(rtv.Get(), color);
	Renderer::GetContext()->ClearDepthStencilView(Renderer::GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	Renderer::SetViewport(width, height);

	XMFLOAT3 position = target->GetPosition();

	XMVECTOR positionVec = XMVectorSet(position.x + cameraOffset.x, position.y + cameraOffset.y, position.z + cameraOffset.z, 1.0f);
	XMVECTOR atVec = XMVectorSet(position.x + targetOffset.x, position.y + targetOffset.y, position.z + targetOffset.z, 1.0f);
	XMVECTOR upVec = XMVectorSet(up.x, up.y, up.z, 1.0f);

	viewMatrix = XMMatrixLookAtLH(positionVec, atVec, upVec);
	ConstantBuffer::SetViewMatrix(&viewMatrix);

	projectionMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(60.0f), (float)width / (float)height, 1.0f, 1000.0f);
	ConstantBuffer::SetProjectionMatrix(&projectionMatrix);
}

void RTT::End()
{
	Renderer::SetRenderTarget();

	Renderer::SetViewport(SCREEN_WIDTH, SCREEN_HEIGHT);
}