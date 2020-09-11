#include"B_header.h"
#include"input.h"



BulletBule::BulletBule()
{
	count = 0;
	Sbullet.Collider.Radius = 0.3f;
	Sbullet.AttackObj = true;
}


BulletBule::~BulletBule()
{
}

void BulletBule::Move()
{
	XMVECTOR bullPos = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	bullPos = XMLoadFloat3(&m_Position);
	XMVECTOR BulletBuleFront = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR NowPlayer1Pos;
	if (Sbullet.AttackObj)
	{
		CPlayer* g_P = CManager::GetScene()->GetGmeobjs<CPlayer>(_Cplayer);
		NowPlayer1Pos = XMLoadFloat3(&g_P->GetPosition());
		BulletBuleFront = NowPlayer1Pos - bullPos;
		BulletBuleFront = XMVector3Normalize(BulletBuleFront);
		bullPos += BulletBuleFront * 0.2f;
	}
	else
	{
		Friend* g_P = CManager::GetScene()->GetGmeobjs<Friend>(_Friend);
		NowPlayer1Pos = XMLoadFloat3(&g_P->GetPosition());
		BulletBuleFront = NowPlayer1Pos - bullPos;
		BulletBuleFront = XMVector3Normalize(BulletBuleFront);
		bullPos += BulletBuleFront * 0.2f;
	}
	XMStoreFloat3(&m_Position, bullPos);
	Sbullet.Collider.Center = m_Position;

}

void BulletBule::State()
{
	CPlayer* g_P = CManager::GetScene()->GetGmeobjs<CPlayer>(_Cplayer);
	Friend* g_P1 = CManager::GetScene()->GetGmeobjs<Friend>(_Friend);
	count++;
	if (count > 500)
	{
		SetDestroy();
		count = 0;

	}
	//if (Sbullet.Collider.Intersects(g_P->GetPlayer1Collide()))
	//{
	//	SetDestroy();
	//}
	//if (Sbullet.Collider.Intersects(g_P1->getSfriend()->Collider))
	//{
	//	SetDestroy();
	//}
}

void BulletBule::Init()
{
	m_Front = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	m_Position = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.5f, 0.5f, 0.5f);
	t_Modle = new StaticModel();
	t_Modle->LoadAny("asset/Onepiece/GunSoldier2.fbx");
}

void BulletBule::Uninit()
{
	t_Modle->UnloadAssimp();
	delete t_Modle;
}

void BulletBule::Update(float dt)
{
	//Move();
	//State();
}

void BulletBule::Draw()
{
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);//×ª¾ØÕóÈ«²¿
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	CRenderer::SetWorldMatrix(&world);
	t_Modle->DrawAny();
}

EnemyBullet * BulletBule::getSbule()
{
	return &Sbullet;
}

