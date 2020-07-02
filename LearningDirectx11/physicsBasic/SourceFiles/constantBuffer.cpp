#include "engine.h"
#include "constantBuffer.h"

//VS
ComPtr<ID3D11Buffer> ConstantBuffer::worldBuffer = nullptr;
ComPtr<ID3D11Buffer> ConstantBuffer::viewBuffer = nullptr;
ComPtr<ID3D11Buffer> ConstantBuffer::projectionBuffer = nullptr;
ComPtr<ID3D11Buffer> ConstantBuffer::cameraBuffer = nullptr;
ComPtr<ID3D11Buffer> ConstantBuffer::bonesBuffer = nullptr;
ComPtr<ID3D11Buffer> ConstantBuffer::reflectionBuffer = nullptr;

//PS
ComPtr<ID3D11Buffer> ConstantBuffer::shadowBuffer = nullptr;
ComPtr<ID3D11Buffer> ConstantBuffer::blurBuffer = nullptr;

void ConstantBuffer::VS()
{
	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);

	hBufferDesc.ByteWidth = sizeof(XMMATRIX);
	Renderer::GetDevice()->CreateBuffer(&hBufferDesc, NULL, worldBuffer.GetAddressOf());
	Renderer::GetContext()->VSSetConstantBuffers(0, 1, worldBuffer.GetAddressOf());

	hBufferDesc.ByteWidth = sizeof(XMMATRIX);
	Renderer::GetDevice()->CreateBuffer(&hBufferDesc, NULL, viewBuffer.GetAddressOf());
	Renderer::GetContext()->VSSetConstantBuffers(1, 1, viewBuffer.GetAddressOf());

	hBufferDesc.ByteWidth = sizeof(XMMATRIX);
	Renderer::GetDevice()->CreateBuffer(&hBufferDesc, NULL, projectionBuffer.GetAddressOf());
	Renderer::GetContext()->VSSetConstantBuffers(2, 1, projectionBuffer.GetAddressOf());

	//Direction Light

	hBufferDesc.ByteWidth = sizeof(XMFLOAT4);
	Renderer::GetDevice()->CreateBuffer(&hBufferDesc, NULL, cameraBuffer.GetAddressOf());
	Renderer::GetContext()->VSSetConstantBuffers(4, 1, cameraBuffer.GetAddressOf());

	hBufferDesc.ByteWidth = sizeof(XMMATRIX);
	Renderer::GetDevice()->CreateBuffer(&hBufferDesc, NULL, reflectionBuffer.GetAddressOf());
	Renderer::GetContext()->VSSetConstantBuffers(5, 1, reflectionBuffer.GetAddressOf());

	hBufferDesc.ByteWidth = sizeof(XMFLOAT4X4) * BONEMAX;
	Renderer::GetDevice()->CreateBuffer(&hBufferDesc, NULL, bonesBuffer.GetAddressOf());
	Renderer::GetContext()->VSSetConstantBuffers(6, 1, bonesBuffer.GetAddressOf());
}

void ConstantBuffer::PS()
{
	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);

	//Direction Light
	//Point Light
	//Spot Light

	hBufferDesc.ByteWidth = sizeof(ShadowSettings);
	Renderer::GetDevice()->CreateBuffer(&hBufferDesc, NULL, shadowBuffer.GetAddressOf());
	Renderer::GetContext()->PSSetConstantBuffers(3, 1, shadowBuffer.GetAddressOf());

	hBufferDesc.ByteWidth = sizeof(BlurSettings);
	Renderer::GetDevice()->CreateBuffer(&hBufferDesc, NULL, blurBuffer.GetAddressOf());
	Renderer::GetContext()->PSSetConstantBuffers(4, 1, blurBuffer.GetAddressOf());
}

void ConstantBuffer::Initialize()
{
	VS();
	PS();

	SetShadowSettings(ShadowSettings(0.0f, 0.0f));
	SetBlurSettings(BlurSettings(0.0f, 0.0f, 0.0f));
}

/*--------------------------------------------------------------------------------
Vertex Shader
--------------------------------------------------------------------------------*/
void ConstantBuffer::SetWorldMatrix2D()
{
	Renderer::GetContext()->UpdateSubresource(worldBuffer.Get(), 0, NULL, &XMMatrixTranspose(XMMatrixIdentity()), 0, 0);

	Renderer::GetContext()->UpdateSubresource(viewBuffer.Get(), 0, NULL, &XMMatrixTranspose(XMMatrixIdentity()), 0, 0);

	XMMATRIX projection = XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f);
	Renderer::GetContext()->UpdateSubresource(projectionBuffer.Get(), 0, NULL, &XMMatrixTranspose(projection), 0, 0);
}

void ConstantBuffer::SetWorldMatrix(XMMATRIX* matrix)
{
	Renderer::GetContext()->UpdateSubresource(worldBuffer.Get(), 0, NULL, &XMMatrixTranspose(*matrix), 0, 0);
}

void ConstantBuffer::SetViewMatrix(XMMATRIX* matrix)
{
	Renderer::GetContext()->UpdateSubresource(viewBuffer.Get(), 0, NULL, &XMMatrixTranspose(*matrix), 0, 0);
}

void ConstantBuffer::SetProjectionMatrix(XMMATRIX* matrix)
{
	Renderer::GetContext()->UpdateSubresource(projectionBuffer.Get(), 0, NULL, &XMMatrixTranspose(*matrix), 0, 0);
}

void ConstantBuffer::SetCamera(XMFLOAT3 position)
{
	Renderer::GetContext()->UpdateSubresource(cameraBuffer.Get(), 0, NULL, &XMFLOAT4(position.x, position.y, position.z, 0.0f), 0, 0);
}

void ConstantBuffer::SetBones(std::vector<XMFLOAT4X4>& transforms)
{
	XMFLOAT4X4 bones[BONEMAX];
	ZeroMemory(&bones, sizeof(bones));

	for (int index = 0; index < transforms.size(); index++)
		bones[index] = transforms[index];

	Renderer::GetContext()->UpdateSubresource(bonesBuffer.Get(), 0, NULL, &bones, 0, 0);
}

void ConstantBuffer::SetReflectionMatrix(XMMATRIX* matrix)
{
	Renderer::GetContext()->UpdateSubresource(reflectionBuffer.Get(), 0, NULL, &XMMatrixTranspose(*matrix), 0, 0);
}

void ConstantBuffer::SetShadowSettings(ShadowSettings settings)
{
	Renderer::GetContext()->UpdateSubresource(shadowBuffer.Get(), 0, NULL, &settings, 0, 0);
}

void ConstantBuffer::SetBlurSettings(BlurSettings settings)
{
	Renderer::GetContext()->UpdateSubresource(blurBuffer.Get(), 0, NULL, &settings, 0, 0);
}
