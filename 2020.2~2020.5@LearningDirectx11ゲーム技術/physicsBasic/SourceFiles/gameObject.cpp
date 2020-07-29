#include "engine.h"
#include "gameObject.h"

void GameObject::Initialize()
{
}

void GameObject::Update()
{
	for (int index = 0; index < myCollisions.size(); index++)
		myCollisions[index]->Update(this->worldMatrix);
}

void GameObject::Render(bool boundingBox)
{
	if (boundingBox)
	{
		for (int index = 0; index < myCollisions.size(); index++)
			myCollisions[index]->Render();
	}
}

void GameObject::Finalize()
{
	myCollisions.clear();
}

bool GameObject::GetDestroyed()
{
	if (this->destroyed)
	{
		Finalize();
		delete this;
		return true;
	}
	else
		return false;
}