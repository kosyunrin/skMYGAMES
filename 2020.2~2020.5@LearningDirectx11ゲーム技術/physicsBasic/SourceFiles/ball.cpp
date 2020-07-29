#include "engine.h"
#include "ball.h"

Ball::Ball(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scaling, UINT ID)
{
	this->m_Position = position;
	this->m_Rotation = rotation;
	this->m_Scale = scaling;
	this->ID = ID;
	this->Initialize();
}

void Ball::Initialize()
{
	quaternion = XMQuaternionIdentity();

	this->myCollisions = Material::GetModel(ID).GetMyCollisions();
}

void Ball::Update()
{
	if (Input::KeyPress(VK_LEFT))
	{
		XMVECTOR axis = XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);
		XMVECTOR rot = XMQuaternionRotationAxis(axis, 0.2f);

		quaternion = XMQuaternionMultiply(quaternion, rot);
		quaternion = XMQuaternionNormalize(quaternion);

		m_Position.x -= 0.05f;
	}
	if (Input::KeyPress(VK_RIGHT))
	{
		XMVECTOR axis = XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);
		XMVECTOR rot = XMQuaternionRotationAxis(axis, -0.2f);

		quaternion = XMQuaternionMultiply(quaternion, rot);
		quaternion = XMQuaternionNormalize(quaternion);

		m_Position.x += 0.05f;
	}
	if (Input::KeyPress(VK_DOWN))
	{
		XMVECTOR axis = XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f);
		XMVECTOR rot = XMQuaternionRotationAxis(axis, -0.2f);

		quaternion = XMQuaternionMultiply(quaternion, rot);
		quaternion = XMQuaternionNormalize(quaternion);

		m_Position.z -= 0.05f;
	}
	if (Input::KeyPress(VK_UP))
	{
		XMVECTOR axis = XMVectorSet(1.0f, 0.0f, 1.0f, 1.0f);
		XMVECTOR rot = XMQuaternionRotationAxis(axis, 0.2f);

		quaternion = XMQuaternionMultiply(quaternion, rot);
		quaternion = XMQuaternionNormalize(quaternion);

		m_Position.z += 0.05f;
	}

	worldMatrix = Engine::WorldTransform(m_Position, quaternion, m_Scale);

	GameObject::Update();
}

void Ball::Render(bool boundingBox)
{
	GameObject::Render(boundingBox);

	Material::SetModel(ID, myCollisions, worldMatrix);
}