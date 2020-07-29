#include "engine.h"
#include "staticObject.h"

StaticObject::StaticObject(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scaling, UINT ID)
{
	this->m_Position = position;
	this->m_Rotation = rotation;
	this->m_Scale = scaling;
	this->ID = ID;
	this->Initialize();
}

void StaticObject::Initialize()
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

void StaticObject::Update()
{
	m_Rotation.y += 0.2f;

	worldMatrix = Engine::WorldTransform(m_Position, m_Rotation, m_Scale);

	GameObject::Update();
}

void StaticObject::Render(bool boundingBox)
{
	GameObject::Render(boundingBox);

	Material::SetModel(ID, worldMatrix);
}