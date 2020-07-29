#include "engine.h"
#include "game.h"
#include "manager.h"

std::unique_ptr<Scene> Manager::scene = nullptr;

void Manager::Initialize()
{
	Engine::Initialize();
	setScene<Game>();
}

void Manager::Update()
{
	Engine::Update();
	scene->Update();
}

void Manager::Render()
{
	scene->Render(TRUE);
}

void Manager::Finalize()
{
	Engine::Finalize();
	scene->Finalize();
}
