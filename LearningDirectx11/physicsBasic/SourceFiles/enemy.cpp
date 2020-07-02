#include "engine.h"
#include "player.h"
#include "enemy.h"

Enemy::Enemy()
{
	std::string path[] =
	{
		{"./Asset/ZombieMutant/Attack1_.fbx"},
		{"./Asset/ZombieMutant/Attack2_.fbx"},
		{"./Asset/ZombieMutant/Attack3_.fbx"},
		{"./Asset/ZombieMutant/Dead_.fbx"},
		{"./Asset/ZombieMutant/Die1_.fbx"},
		{"./Asset/ZombieMutant/Die2_.fbx"},
		{"./Asset/ZombieMutant/Hit_.fbx"},
		{"./Asset/ZombieMutant/Run2_.fbx"},
		{"./Asset/ZombieMutant/Shout_.fbx"},
		{"./Asset/ZombieMutant/Walk2_.fbx"}
	};

	model = std::make_unique<MultiSkinnedModel>(path, 10);

	this->myCollisions = model->GetMyCollisions();

	this->Initialize();
}

void Enemy::Initialize()
{
	this->m_Position = XMFLOAT3(rand() % 10 - 5.0f, 0.0f, rand() % 10 - 5.0f);
	this->m_Rotation = XMFLOAT3(0.0f, 180.0f, 0.0f);
	this->m_Scale = XMFLOAT3(1.5f, 1.5f, 1.5f);

	this->m_Front = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	this->health = 50;

	this->event = Idle;
	this->targetLocation = m_Position;
	this->speed = 0.0f;
	this->counter = rand() % 20;
	this->deadCounter = 0.0f;

	this->targeted = false;
	this->onceTargeted = false;
	this->shouted = false;
	this->dead = false;
	this->shoutResetedTimer = false;
	this->deadResetedTimer = false;

	m_PositionVec = XMLoadFloat3(&m_Position);
}

void Enemy::Update()
{
	if (dead)
	{
		this->Initialize();
		dead = false;
	}

	model->Update(FALSE);
	myCollisions = model->GetMyCollisions();

	XMFLOAT3 playerPos = Manager::GetScene()->GetGameObject<Player>()->GetPosition();

	/*--------------------------------------------------------------------------------
	Movement
	--------------------------------------------------------------------------------*/
	if (targeted)
		onceTargeted = true;

	if (!onceTargeted)
		event = Event::Idle;
	else
	{
		//Run
		if (abs(playerPos.x - m_Position.x) > 1.0f || abs(playerPos.z - m_Position.z) > 1.0f)
			event = Event::Run;

		//Attack
		if (abs(playerPos.x - m_Position.x) <= 1.0f && abs(playerPos.z - m_Position.z) <= 1.0f)
			event = Event::Attack;

		//Shout
		if (!shouted)
			event = Event::Shout;

		//Hit
		if (Input::MouseLeftDown())
			if (targeted)
				event = Event::Hit;
	}

	//Dead
	if (health <= 0)
		event = Event::Dead;

	switch (event)
	{
	case Event::Idle:
		Idle_Action();
		break;
	case Event::Shout:
		Shout_Action();
		break;
	case Event::Run:
		Run_Action();
		break;
	case Event::Attack:
		Attack_Action();
		break;
	case Event::Hit:
		Hit_Action();
		break;
	case Event::Dead:
		Dead_Action();
		break;
	}

	worldMatrix = Engine::WorldTransform(m_Position, m_Rotation, m_Scale);

	GameObject::Update();
}

void Enemy::Render(bool boundingBox)
{
	GameObject::Render(boundingBox);

	switch (event)
	{
	case Event::Idle:
		model->Render(worldMatrix, 5);
		break;
	case Event::Shout:
		model->Render(worldMatrix, 8);
		break;
	case Event::Walk:
		model->Render(worldMatrix, 9);
		break;
	case Event::Run:
		model->Render(worldMatrix, 7);
		break;
	case Event::Attack:
		model->Render(worldMatrix, 0);
		break;
	case Event::Hit:
		model->Render(worldMatrix, 6);
		break;
	case Event::Dead:
		model->Render(worldMatrix, 3);
		break;
	}
}

void Enemy::Idle_Action()
{
	if (targetLocation.x - m_Position.x > 1.0f || targetLocation.z - m_Position.z > 1.0f)
	{
		if (m_Position.x < targetLocation.x)
			m_Position.x += speed / 2.0f;
		if (m_Position.x > targetLocation.x)
			m_Position.x -= speed / 2.0f;
		if (m_Position.z < targetLocation.z)
			m_Position.z += speed / 2.0f;
		if (m_Position.z > targetLocation.z)
			m_Position.z -= speed / 2.0f;

		event = Event::Walk;
	}
	else
	{
		if (counter < 15.0f)
			counter++;
		else
		{
			counter = 0.0f;
			targetLocation = XMFLOAT3(rand() % 50 - 25.0f, 0.0f, rand() % 50 - 25.0f);

			m_PositionVec = XMLoadFloat3(&m_Position);
			XMVECTOR targetPosVec = XMLoadFloat3(&targetLocation);

			//Rotation
			XMVECTOR dir = targetPosVec - m_PositionVec;

			float angle = XMVectorGetY(XMVector3AngleBetweenVectors(m_Front, dir));

			if (XMVectorGetY(XMVector3Cross(m_Front, dir)) > 0.0f)
				m_Rotation.y = XMConvertToDegrees(angle);
			else
				m_Rotation.y = -XMConvertToDegrees(angle);
		}
	}
}

void Enemy::Shout_Action()
{
	//Rotation
	XMVECTOR playerPosVec = Manager::GetScene()->GetGameObject<Player>()->GetPositionVec();
	XMVECTOR dir = playerPosVec - m_PositionVec;

	float angle = XMVectorGetY(XMVector3AngleBetweenVectors(m_Front, dir));

	if (XMVectorGetY(XMVector3Cross(m_Front, dir)) > 0.0f)
		m_Rotation.y = XMConvertToDegrees(angle);
	else
		m_Rotation.y = -XMConvertToDegrees(angle);

	if (!shoutResetedTimer)
	{
		model->ResetTimer();
		shoutResetedTimer = true;
	}

	event = Event::Shout;
	counter++;

	if (counter >= 80.0f)
	{
		counter = 0.0f;
		shouted = true;
	}
}

void Enemy::Run_Action()
{
	XMFLOAT3 playerPos = Manager::GetScene()->GetGameObject<Player>()->GetPosition();

	if (m_Position.x < playerPos.x)
		m_Position.x += speed;
	if (m_Position.x > playerPos.x)
		m_Position.x -= speed;
	if (m_Position.z < playerPos.z)
		m_Position.z += speed;
	if (m_Position.z > playerPos.z)
		m_Position.z -= speed;

	m_PositionVec = XMLoadFloat3(&m_Position);

	//Rotation
	XMVECTOR playerPosVec = Manager::GetScene()->GetGameObject<Player>()->GetPositionVec();
	XMVECTOR dir = playerPosVec - m_PositionVec;

	float angle = XMVectorGetY(XMVector3AngleBetweenVectors(m_Front, dir));

	if (XMVectorGetY(XMVector3Cross(m_Front, dir)) > 0.0f)
		m_Rotation.y = XMConvertToDegrees(angle);
	else
		m_Rotation.y = -XMConvertToDegrees(angle);
}

void Enemy::Attack_Action()
{
	m_PositionVec = XMLoadFloat3(&m_Position);

	//Rotation
	XMVECTOR playerPosVec = Manager::GetScene()->GetGameObject<Player>()->GetPositionVec();
	XMVECTOR dir = playerPosVec - m_PositionVec;

	float angle = XMVectorGetY(XMVector3AngleBetweenVectors(m_Front, dir));

	if (XMVectorGetY(XMVector3Cross(m_Front, dir)) > 0.0f)
		m_Rotation.y = XMConvertToDegrees(angle);
	else
		m_Rotation.y = -XMConvertToDegrees(angle);
}

void Enemy::Hit_Action()
{
	model->ReduceTimer(0.2f);
	ReduceHealth(1);

	m_PositionVec = XMLoadFloat3(&m_Position);

	//Rotation
	XMVECTOR playerPosVec = Manager::GetScene()->GetGameObject<Player>()->GetPositionVec();
	XMVECTOR dir = playerPosVec - m_PositionVec;

	float angle = XMVectorGetY(XMVector3AngleBetweenVectors(m_Front, dir));

	if (XMVectorGetY(XMVector3Cross(m_Front, dir)) > 0.0f)
		m_Rotation.y = XMConvertToDegrees(angle);
	else
		m_Rotation.y = -XMConvertToDegrees(angle);
}

void Enemy::Dead_Action()
{
	if (!deadResetedTimer)
	{
		model->ResetTimer();
		deadResetedTimer = true;
	}

	deadCounter++;
	if (deadCounter > 30.0f)
		dead = true;
}