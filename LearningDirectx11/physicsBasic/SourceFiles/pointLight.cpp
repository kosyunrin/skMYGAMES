#include "engine.h"
#include "pointLight.h"

PointLightSettings PointLight::settings[PLMAX];

ComPtr<ID3D11Buffer> PointLight::constantBuffer;

void PointLight::Initialize()
{
	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);

	hBufferDesc.ByteWidth = sizeof(PointLightSettings) * PLMAX;
	Renderer::GetDevice()->CreateBuffer(&hBufferDesc, NULL, constantBuffer.GetAddressOf());
	Renderer::GetContext()->PSSetConstantBuffers(1, 1, constantBuffer.GetAddressOf());

	//Initialize lighting settings
	settings[0].Enable = true;
	settings[0].Position = XMFLOAT3(-5.0f, 2.0f, -2.0f);
	settings[0].Diffuse = XMFLOAT4(0.5f, 0.0f, 0.0f, 1.0f);
	settings[0].Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	settings[0].Attenuation = XMFLOAT4(0.0f, 0.2f, 0.0f, 0.0f);
	settings[0].DiffuseStrength = 1.0f;
	settings[0].AmbientStrength = 1.0f;
	settings[0].Range = 5.0f;

	settings[1].Enable = true;
	settings[1].Position = XMFLOAT3(5.0f, 2.0f, -2.0f);
	settings[1].Diffuse = XMFLOAT4(0.0f, 0.0f, 0.5f, 1.0f);
	settings[1].Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	settings[1].Attenuation = XMFLOAT4(0.0f, 0.2f, 0.0f, 0.0f);
	settings[1].DiffuseStrength = 1.0f;
	settings[1].AmbientStrength = 1.0f;
	settings[1].Range = 5.0f;

	settings[2].Enable = true;
	settings[2].Position = XMFLOAT3(0.0f, 2.0f, -2.0f);
	settings[2].Diffuse = XMFLOAT4(0.0f, 0.5f, 0.0f, 1.0f);
	settings[2].Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	settings[2].Attenuation = XMFLOAT4(0.0f, 0.2f, 0.0f, 0.0f);
	settings[2].DiffuseStrength = 1.0f;
	settings[2].AmbientStrength = 1.0f;
	settings[2].Range = 5.0f;

	Renderer::GetContext()->UpdateSubresource(constantBuffer.Get(), 0, NULL, &settings, 0, 0);
}

void PointLight::Update()
{
	Renderer::GetContext()->UpdateSubresource(constantBuffer.Get(), 0, NULL, &settings, 0, 0);
}

void PointLight::ImGui()
{
	ImGui::Begin("Pointlight 1");
	ImGui::Button("Enable");
	if (ImGui::IsItemClicked(0))
		settings[0].Enable = !settings[0].Enable;
	ImGui::DragFloat3("Position", &settings[0].Position.x, 0.1f);
	ImGui::DragFloat4("Diffuse", &settings[0].Diffuse.x, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat4("Ambient", &settings[0].Ambient.x, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat4("Attenuation", &settings[0].Attenuation.x, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat("DiffuseStrength", &settings[0].DiffuseStrength, 0.01f);
	ImGui::DragFloat("AmbientStrength", &settings[0].AmbientStrength, 0.01f);
	ImGui::DragFloat("Range", &settings[0].Range, 0.01f, 0.0f, 1000.0f);
	ImGui::End();

	ImGui::Begin("Pointlight 2");
	ImGui::Button("Enable");
	if (ImGui::IsItemClicked(0))
		settings[1].Enable = !settings[1].Enable;
	ImGui::DragFloat3("Position", &settings[1].Position.x, 0.1f);
	ImGui::DragFloat4("Diffuse", &settings[1].Diffuse.x, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat4("Ambient", &settings[1].Ambient.x, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat4("Attenuation", &settings[1].Attenuation.x, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat("DiffuseStrength", &settings[1].DiffuseStrength, 0.01f);
	ImGui::DragFloat("AmbientStrength", &settings[1].AmbientStrength, 0.01f);
	ImGui::DragFloat("Range", &settings[1].Range, 0.01f, 0.0f, 1000.0f);
	ImGui::End();

	ImGui::Begin("Pointlight 3");
	ImGui::Button("Enable");
	if (ImGui::IsItemClicked(0))
		settings[2].Enable = !settings[2].Enable;
	ImGui::DragFloat3("Position", &settings[2].Position.x, 0.1f);
	ImGui::DragFloat4("Diffuse", &settings[2].Diffuse.x, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat4("Ambient", &settings[2].Ambient.x, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat4("Attenuation", &settings[2].Attenuation.x, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat("DiffuseStrength", &settings[2].DiffuseStrength, 0.01f);
	ImGui::DragFloat("AmbientStrength", &settings[2].AmbientStrength, 0.01f);
	ImGui::DragFloat("Range", &settings[2].Range, 0.01f, 0.0f, 1000.0f);
	ImGui::End();

	//Disable Lighting
	for(int index = 0; index < PLMAX; index++)
	{
		if (!settings[index].Enable)
			settings[index].DiffuseStrength = 0.0f;
		else
			if (settings[index].DiffuseStrength < 1.0f)
				settings[index].DiffuseStrength = 1.0f;
	}
}
