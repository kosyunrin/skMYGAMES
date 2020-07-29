#include "engine.h"
#include "staticObject.h"
#include "player.h"
#include "enemy.h"
#include "boss.h"
#include "skybox.h"
#include "plane.h"
#include "cube.h"
#include "map.h"
#include "game.h"

bool renderBounding;
bool enableReflection;
bool debugMode;
bool solidMode;

void Game::Initialize()
{
	AddGameObject<Map>(LayerID::LayerScene);
	AddGameObject<Skybox>(LayerID::LayerSkybox);
	AddGameObject<Plane>(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(200.0f, 1.0f, 200.0f), TextureID::textureAsh, LayerID::LayerScene);
 	AddGameObject<StaticObject>(XMFLOAT3(-5.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.2f, 0.2f, 0.2f), ModelID::modelNanosuit, LayerID::LayerEnemy);
 	AddGameObject<StaticObject>(XMFLOAT3(-2.5f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.2f, 0.2f, 0.2f), ModelID::modelNanosuit, LayerID::LayerEnemy);
 	AddGameObject<StaticObject>(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.2f, 0.2f, 0.2f), ModelID::modelNanosuit, LayerID::LayerEnemy);
 	AddGameObject<StaticObject>(XMFLOAT3(2.5f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.2f, 0.2f, 0.2f), ModelID::modelNanosuit, LayerID::LayerEnemy);
 	AddGameObject<StaticObject>(XMFLOAT3(5.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.2f, 0.2f, 0.2f), ModelID::modelNanosuit, LayerID::LayerEnemy);
	AddGameObject<Player>(LayerID::LayerPlayer);
	AddGameObject<Enemy>(LayerID::LayerEnemy);
//	AddGameObject<Enemy>(LayerID::LayerEnemy);
//	AddGameObject<Enemy>(LayerID::LayerEnemy);
	AddGameObject<Enemy>(LayerID::LayerEnemy);
	AddGameObject<Enemy>(LayerID::LayerEnemy);
//	AddGameObject<Boss>(LayerID::LayerEnemy);

	Camera::Initialize();
	DirectionLight::Initialize();
	PointLight::Initialize();
	SpotLight::Initialize();

	reflection = std::make_unique<RTT>(SCREEN_WIDTH, SCREEN_HEIGHT);
	light = std::make_unique<RTT>(SCREEN_WIDTH, SCREEN_HEIGHT);
	shadow = std::make_unique<Shadow>(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
	ray = std::make_unique<Ray>();

	renderBounding = true;
	enableReflection = true;
	debugMode = false;
	solidMode = true;
}

void Game::Update()
{
	Scene::Update();
	Camera::Update();
	CollisionSystem::Update();
	DirectionLight::Update();
	PointLight::Update();
	SpotLight::Update();

	ray->Update();

	if (Input::KeyTrigger(VK_RETURN))
		debugMode = !debugMode;

	if (Input::KeyTrigger('R'))
		enableReflection = !enableReflection;

	if (solidMode)
		Renderer::SetFillMode(D3D11_FILL_SOLID);
	else
		Renderer::SetFillMode(D3D11_FILL_WIREFRAME);

	this->GetGameObject<Player>()->SetRestrictCam(enableReflection);
	this->GetGameObject<Plane>()->SetReflection(enableReflection);
}

void Game::Render(bool boundingBox)
{
	Camera::Render();

	if (debugMode)
	{
		light->Begin(DirectionLight::GetSettings().ViewMatrix, DirectionLight::GetSettings().ProjectionMatrix);
		Shader::SetPSShader(PSShaderID::PS_NoLight);
		Shader::SetRestrictShader();
		Scene::Render(FALSE, LayerID::LayerScene);
		Shader::SetRestrictShader();
		light->End();
	}

	/*--------------------------------------------------------------------------------
	RTT
	--------------------------------------------------------------------------------*/
	if (enableReflection)
	{
		reflection->Begin(0.0f);
		Scene::Render(FALSE, LayerID::LayerSkybox);
		Scene::Render(FALSE, LayerID::LayerScene);
		Scene::Render(FALSE, LayerID::LayerPlayer);
		Scene::Render(FALSE, LayerID::LayerEnemy);
		reflection->End();
		Texture::SetTexture(reflection->GetTexture(), TextureMapID::ReflectionMap);
	}

	shadow->Begin(DirectionLight::GetSettings().ViewMatrix, DirectionLight::GetSettings().ProjectionMatrix);
	Scene::Render(FALSE, LayerID::LayerScene);
	Scene::Render(FALSE, LayerID::LayerPlayer);
	Scene::Render(FALSE, LayerID::LayerEnemy);
	shadow->End();
	shadow->SecondBegin();
	Scene::Render(FALSE, LayerID::LayerScene);
	Scene::Render(FALSE, LayerID::LayerPlayer);
	Scene::Render(FALSE, LayerID::LayerEnemy);
	shadow->SecondEnd();

	/*--------------------------------------------------------------------------------
	Render Scene
	--------------------------------------------------------------------------------*/
	Renderer::Begin();
	
	ImGui();

	Scene::Render(renderBounding, LayerID::LayerSkybox);
	Scene::Render(renderBounding, LayerID::LayerScene);
	Scene::Render(renderBounding, LayerID::LayerPlayer);
	Scene::Render(renderBounding, LayerID::LayerEnemy);

	Shader::SetVSShader(VSShaderID::VS_Basic);
	Shader::SetPSShader(PSShaderID::PS_NoLight);

	if (debugMode)
	{
		Sprite::Render(SCREEN_WIDTH - 1024.0f, SCREEN_HEIGHT - 640.0f, 1024.0f, 640.0f, light->GetTexture());
		Sprite::Render(SCREEN_WIDTH - 2048.0f, SCREEN_HEIGHT - 640.0f, 1024.0f, 640.0f, shadow->GetTexture());
	}

	Sprite::Render(SCREEN_CENTERX - 5.0f, SCREEN_CENTERY - 5.0f, 10.0f, 10.0f, TextureID::textureWhite);

	Renderer::End();
}

void Game::Finalize()
{
	Scene::Finalize();
}

void Game::ImGui()
{
	Camera::ImGui();
	DirectionLight::ImGui();
	PointLight::ImGui();
	SpotLight::ImGui();

	ray->ImGui();

	shadow->ImGui();

	this->GetGameObject<Player>()->ImGui();

	ImGui::Begin("FPS");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Checkbox("Solid", &solidMode);
	ImGui::Checkbox("BoundingBox", &renderBounding);
	ImGui::Checkbox("Reflection", &enableReflection);
	ImGui::End();
}