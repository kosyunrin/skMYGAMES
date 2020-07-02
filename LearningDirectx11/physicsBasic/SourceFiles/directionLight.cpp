#include "engine.h"
#include "directionLight.h"

DirectionLightSettings DirectionLight::settings;

ComPtr<ID3D11Buffer> DirectionLight::VSBuffer = nullptr;
ComPtr<ID3D11Buffer> DirectionLight::PSBuffer = nullptr;

XMFLOAT3 DirectionLight::offset;

void DirectionLight::Initialize()
{
	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);

	hBufferDesc.ByteWidth = sizeof(DirectionLightSettings);
	Renderer::GetDevice()->CreateBuffer(&hBufferDesc, NULL, VSBuffer.GetAddressOf());
	Renderer::GetContext()->VSSetConstantBuffers(3, 1, VSBuffer.GetAddressOf());

	hBufferDesc.ByteWidth = sizeof(DirectionLightSettings);
	Renderer::GetDevice()->CreateBuffer(&hBufferDesc, NULL, PSBuffer.GetAddressOf());
	Renderer::GetContext()->PSSetConstantBuffers(0, 1, PSBuffer.GetAddressOf());


	//Initialize lighting settings
	offset = XMFLOAT3(-10.0f, 25.0f, -30.0f);

	settings.Enable = true;
	settings.Direction = XMFLOAT4(0.5f, -1.0f, 1.0f, 1.0f);
	settings.Diffuse = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
	settings.Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);

	/*--------------------------------------------------------------------------------
	Update Matrix
	--------------------------------------------------------------------------------*/
	XMFLOAT3 cameraPos = Camera::GetPosition();

	XMFLOAT3 position = XMFLOAT3(offset.x + cameraPos.x + -settings.Direction.x * 10.0f, offset.y + cameraPos.y + -settings.Direction.y * 10.0f, offset.z + cameraPos.z + -settings.Direction.z * 10.0f);
	XMFLOAT3 at = XMFLOAT3(offset.x + cameraPos.x + settings.Direction.x * 10.0f, offset.y + cameraPos.y + settings.Direction.y * 10.0f, offset.z + cameraPos.z + settings.Direction.z * 10.0f);

	settings.Position = position;

	XMVECTOR positionVec = XMVectorSet(position.x, position.y, position.z, 1.0f);
	XMVECTOR atVec = XMVectorSet(at.x, at.y, at.z, 1.0f);
	XMVECTOR upVec = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	settings.ViewMatrix = XMMatrixLookAtLH(positionVec, atVec, upVec);
	settings.ViewTransMatrix = XMMatrixTranspose(settings.ViewMatrix);

	settings.ProjectionMatrix = XMMatrixOrthographicLH(120, 120, 0.0f, 1000.0f);
	settings.ProjectionTransMatrix = XMMatrixTranspose(settings.ProjectionMatrix);

	Renderer::GetContext()->UpdateSubresource(VSBuffer.Get(), 0, NULL, &settings, 0, 0);
	Renderer::GetContext()->UpdateSubresource(PSBuffer.Get(), 0, NULL, &settings, 0, 0);
}

void DirectionLight::Update()
{
	/*--------------------------------------------------------------------------------
	Update Matrix
	--------------------------------------------------------------------------------*/
	XMFLOAT3 cameraPos = Camera::GetPosition();

	XMFLOAT3 position = XMFLOAT3(offset.x + cameraPos.x + -settings.Direction.x * 10.0f, offset.y + cameraPos.y + -settings.Direction.y * 10.0f, offset.z + cameraPos.z + -settings.Direction.z * 10.0f);
	XMFLOAT3 at = XMFLOAT3(offset.x + cameraPos.x + settings.Direction.x * 10.0f, offset.y + cameraPos.y + settings.Direction.y * 10.0f, offset.z + cameraPos.z + settings.Direction.z * 10.0f);

	settings.Position = position;

	XMVECTOR positionVec = XMVectorSet(position.x, position.y, position.z, 1.0f);
	XMVECTOR atVec = XMVectorSet(at.x, at.y, at.z, 1.0f);
	XMVECTOR upVec = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	settings.ViewMatrix = XMMatrixLookAtLH(positionVec, atVec, upVec);
	settings.ViewTransMatrix = XMMatrixTranspose(settings.ViewMatrix);

	settings.ProjectionMatrix = XMMatrixOrthographicLH(120, 120, 0.0f, 1000.0f);
	settings.ProjectionTransMatrix = XMMatrixTranspose(settings.ProjectionMatrix);

	Renderer::GetContext()->UpdateSubresource(VSBuffer.Get(), 0, NULL, &settings, 0, 0);
	Renderer::GetContext()->UpdateSubresource(PSBuffer.Get(), 0, NULL, &settings, 0, 0);
}

void DirectionLight::ImGui()
{
	ImGui::Begin("Directional Light");
	ImGui::Button("Enable");
	if (ImGui::IsItemClicked(0))
		settings.Enable = !settings.Enable;
	ImGui::DragFloat3("Direction", &settings.Direction.x, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat4("Diffuse", &settings.Diffuse.x, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat4("Ambient", &settings.Ambient.x, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat3("Offset", &offset.x, 0.1f);
	ImGui::End();
}
