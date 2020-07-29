#include "engine.h"
#include "title.h"
#include "result.h"

void Result::Initialize()
{
}

void Result::Update()
{
	Scene::Update();

	if (Input::KeyTrigger(VK_SPACE))
		Manager::setScene<Title>();
}

void Result::Render(bool boundingBox)
{
	Renderer::Begin();
	Scene::Render(boundingBox);
	Renderer::End();
}

void Result::Finalize()
{
	Scene::Finalize();
}