#include "engine.h"
#include "boss.h"

Boss::Boss()
{
	this->m_Position = XMFLOAT3(0.0f, 0.0f, -3.0f);
	this->m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->m_Scale = XMFLOAT3(0.01f, 0.01f, 0.01f);

	event = 4;

	this->Initialize();
}

void Boss::Initialize()
{
	std::string path[] =
	{
		{"./Asset/NQ/NQidiot.fbx"},
		{"./Asset/NQ/NQpaobu.fbx"},
		{"./Asset/NQ/NQpgong.fbx"},
		{"./Asset/NQ/NQsaoshe.fbx"},

	};

	model = std::make_unique<MultiSkinnedModel>(path, 4);

	this->myCollisions = model->GetMyCollisions();
}

void Boss::Update()
{
	model->Update(TRUE);
	myCollisions = model->GetMyCollisions();

	GameObject::Update();

	if (Input::KeyTrigger('J'))
	{
		event++;
		model->ResetTimer();
	}
	if (event > 4)
		event = 1;

	if (Input::KeyPress(VK_UP) && !Input::KeyPress(VK_LSHIFT))
		m_Position.z += 0.1f;
	if (Input::KeyPress(VK_DOWN) && !Input::KeyPress(VK_LSHIFT))
		m_Position.z -= 0.1f;
	if (Input::KeyPress(VK_LEFT) && !Input::KeyPress(VK_LSHIFT))
		m_Position.x -= 0.1f;
	if (Input::KeyPress(VK_RIGHT) && !Input::KeyPress(VK_LSHIFT))
		m_Position.x += 0.1f;

	if (Input::KeyPress(VK_LEFT) && Input::KeyPress(VK_LSHIFT))
		m_Rotation.y--;
	if (Input::KeyPress(VK_RIGHT) && Input::KeyPress(VK_LSHIFT))
		m_Rotation.y++;

	m_Position.y = 0.0f;
}

void Boss::Render(bool boundingBox)
{
	GameObject::Render(boundingBox);

	worldMatrix = Engine::WorldTransform(m_Position, m_Rotation, m_Scale);
	model->Render(worldMatrix, event - 1);
}