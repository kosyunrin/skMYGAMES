#include "engine.h"
#include "game.h"
#include "title.h"

void Title::Initialize()
{
}

void Title::Update()
{
	Scene::Update();

	if (Input::KeyTrigger(VK_SPACE))
		Manager::setScene<Game>();
}

void Title::Render(bool boundingBox)
{
	Renderer::Begin();
	Scene::Render(boundingBox);
	Renderer::End();
}

void Title::Finalize()
{
	Scene::Finalize();
}