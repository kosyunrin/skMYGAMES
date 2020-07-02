#include "engine.h"
#include "player.h"
#include "spotlight.h"

SpotLightSettings SpotLight::settings[SLMAX];

ComPtr<ID3D11Buffer> SpotLight::constantBuffer;

XMFLOAT3 SpotLight::offset;
XMFLOAT3 SpotLight::at_offset;

void SpotLight::Initialize()
{
	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);

	hBufferDesc.ByteWidth = sizeof(SpotLightSettings) * SLMAX;
	Renderer::GetDevice()->CreateBuffer(&hBufferDesc, NULL, constantBuffer.GetAddressOf());
	Renderer::GetContext()->PSSetConstantBuffers(2, 1, constantBuffer.GetAddressOf());

	//Initialize flashlight settings
	settings[0].Enable = true;
	settings[0].Position = XMFLOAT3(0.0f, 1.0f, -5.0f);
	settings[0].Direction = XMFLOAT4(0.0f, 0.0f, 1.0f, 0.0f);
	settings[0].Diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	settings[0].Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	settings[0].Attenuation = XMFLOAT4(0.0f, 0.13f, 0.0f, 0.0f);
	settings[0].DiffuseStrength = 1.0f;
	settings[0].AmbientStrength = 1.0f;
	settings[0].Range = 20.0f;
	settings[0].Cutoff = 0.85f;

	Renderer::GetContext()->UpdateSubresource(constantBuffer.Get(), 0, NULL, &settings, 0, 0);

	//Flashlight offset initialize
	offset = XMFLOAT3(0.0f, 2.5f, -2.5f);
	at_offset = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

void SpotLight::Update()
{
	//Update flashlight position
	XMVECTOR playerPosVec = Manager::GetScene()->GetGameObject<Player>()->GetPositionVec();
	XMVECTOR playerAt = Manager::GetScene()->GetGameObject<Player>()->GetAt();
	XMVECTOR playerFront = Manager::GetScene()->GetGameObject<Player>()->GetFront();
	XMVECTOR playerUp = Manager::GetScene()->GetGameObject<Player>()->GetUp();
	XMVECTOR playerRight = Manager::GetScene()->GetGameObject<Player>()->GetRight();

	XMVECTOR flashlightPosVec;
	XMVECTOR flashlightAt;

	//Adjust flashlight position
	flashlightPosVec = playerPosVec + (playerFront * offset.z) + (playerUp * offset.y);

	//Adjust flashlight at
	flashlightAt = playerAt + (playerFront * at_offset.z) + (playerUp * at_offset.y) + (playerRight * at_offset.x);

	//Calculate player direction
	XMVECTOR flashlightDir = flashlightAt - flashlightPosVec;
	flashlightDir = XMVector3Normalize(flashlightDir);

	XMFLOAT3 Pos;
	XMFLOAT4 Dir;

	XMStoreFloat3(&Pos, flashlightPosVec);
	XMStoreFloat4(&Dir, flashlightDir);

	settings[0].Position = Pos;
	settings[0].Direction = Dir;

	Renderer::GetContext()->UpdateSubresource(constantBuffer.Get(), 0, NULL, &settings, 0, 0);
}

void SpotLight::ImGui()
{
	ImGui::Begin("Flashlight");
	ImGui::Button("Enable");
	if (ImGui::IsItemClicked(0))
		settings[0].Enable = !settings[0].Enable;
	ImGui::DragFloat4("Offset", &offset.x, 0.01f);
	ImGui::DragFloat4("Position", &settings[0].Position.x, 0.01f);
	ImGui::DragFloat4("Direction", &settings[0].Direction.x, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat4("Diffuse", &settings[0].Diffuse.x, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat4("Ambient", &settings[0].Ambient.x, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat4("Attenuation", &settings[0].Attenuation.x, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat("DiffuseStrength", &settings[0].DiffuseStrength, 0.01f);
	ImGui::DragFloat("AmbientStrength", &settings[0].AmbientStrength, 0.01f);
	ImGui::DragFloat("Range", &settings[0].Range, 0.01f, 0.0f, 1000.0f);
	ImGui::DragFloat("Cutoff", &settings[0].Cutoff, 0.01f, 0.0f, 1.0f);
	ImGui::End();

	//Disable Lighting
	for (int index = 0; index < SLMAX; index++)
	{
		if (!settings[index].Enable)
			settings[index].DiffuseStrength = 0.0f;
		else
			if (settings[index].DiffuseStrength < 1.0f)
				settings[index].DiffuseStrength = 1.0f;
	}
}
