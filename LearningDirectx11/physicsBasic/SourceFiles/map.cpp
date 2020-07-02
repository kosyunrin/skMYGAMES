#include "engine.h"
#include "map.h"

Map::Map()
{
	this->m_Position = XMFLOAT3(25.0f, 0.0f, -5.0f);
	this->m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	ID = ModelID::modelCastle;

	this->Initialize();
}

void Map::Initialize()
{
	std::vector<Collision*> modelCollisions = Material::GetModel(ID).GetMyCollisions();

	for (int index = 0; index < modelCollisions.size(); index++)
	{
		Collision* modelC = modelCollisions[index];
		Collision* c = new Collision;

		c->Initialize(modelC->GetVertices(), modelC->GetIndices());

		myCollisions.push_back(c);
	}
}

void Map::Update()
{
	worldMatrix = Engine::WorldTransform(m_Position, m_Rotation, m_Scale);

	GameObject::Update();
}

void Map::Render(bool boundingBox)
{
	GameObject::Render(boundingBox);

	Material::SetModel(ID, worldMatrix);
}