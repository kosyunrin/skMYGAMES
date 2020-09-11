#include"B_header.h"
#include"input.h"
SoldierHouseBlue::SoldierHouseBlue()
{
	pMode= new CStaticmodle("asset/Onepiece/house.obj",0);
	m_house.pLife = new CPolygon();
	m_house.pLife->Init3D(3);
	m_timer = new Timer();
	m_t = new Timer();
	pA = new AStarPathFinding();
	pA->Init();
	pA->SetTargetPos({ 0.0f,-20.0f });
	pA->SetbeginPos({ this->m_Position.x,m_Position.z });
	pA->SetStartNode();
}


SoldierHouseBlue::~SoldierHouseBlue()
{
}

void SoldierHouseBlue::Init()
{
	m_Position = XMFLOAT3(1.05f, 0.0f, 7.5f);
	m_Rotation = XMFLOAT3(0.0f, XMConvertToRadians(90.0f), 0.0f);
	m_Scale = XMFLOAT3(0.7f, 0.7f, 0.7f);
	pA->SetbeginPos({ m_Position.x,m_Position.z });
	pA->SetStartNode();
	//setbox
	XMFLOAT3 Vmax;
	XMFLOAT3 Vmin;
	CCreate::CreatVmaxmin(pMode->m_GetBoxPinots()[0].m_BoxPoint.Vmax,
		pMode->m_GetBoxPinots()[0].m_BoxPoint.Vmin,
		m_Scale, m_Rotation, Vmax, Vmin);
	CCreate::CreateBox(m_house.ABOX, Vmax,	Vmin);
	//setline
	m_line = new Line();
	XMFLOAT3 v3[8];
	CCreate::CreateV8(this->m_house.ABOX, v3);
	m_line->InitDrawBox(v3);
	m_house.Target = 100;
	m_house.ABOX.Center = m_Position;
}

void SoldierHouseBlue::Uninit()
{
	delete pMode;
	m_house.pLife->Uninit3D(3);
	delete m_house.pLife;
	delete m_timer;
	delete m_t;
	pA->Uinit();
	delete pA;
}

void SoldierHouseBlue::Update(float dt)
{
	m_house.Target = 100;
	//m_Position.x = CRenderer::Debug_move_v2[0];
	m_timer->Tick();
	//player
	CPlayer* pCplayer = CManager::GetScene()->GetGmeobjs<CPlayer>(_Cplayer);
	if (pCplayer != nullptr)
	{
		if (pCplayer->GetColliderSphere().Contains(m_house.ABOX) && this->m_house.HP > 0)
		{
			m_house.Target = Tama_p0;
		}
	}
	//army
	for (int i = 0; i < 2; i++)
	{
		CRedArmy* pRarmy = CManager::GetScene()->GetGmeobj<CRedArmy>(6, i);
		if (pRarmy != nullptr)
		{
			if (pRarmy->GetColliderSphere().Contains(m_house.ABOX) && this->m_house.HP > 0)
			{
				m_house.Target = Tama_RedXBfromHouse;
				m_house.TargetID = i;
				break;
			}
		}
	}

	//attack
	if (m_timer->TotalTime() > 5.0f)
	{
		switch (m_house.Target)
		{
		case Tama_p0:
		{
			if(pCplayer!=nullptr)
			{
				if (pCplayer->GetColliderSphere().Contains(m_house.ABOX) && this->m_house.HP > 0)
				{
					Cbullet* bullet = CManager::GetScene()->AddGameObject<Cbullet>(12);
					bullet->LoadTex(L"asset/GameTexture/BlueXBtama.png");
					bullet->SetPosition(XMFLOAT3(m_Position.x, m_Position.y + 3.0f, m_Position.z));
					bullet->SetTarget(Tama_p0);
					bullet->SetenemyID(1);
					bullet->SetScale({ 1.0f,1.0f,1.0f });
					bullet->SetPower(500.0f);
				}
			}
			m_timer->Reset();
			break;
		}
		case Tama_RedXBfromHouse:
		{
			CRedArmy* PR = CManager::GetScene()->GetGmeobj<CRedArmy>(6, m_house.TargetID);
			if (PR != nullptr)
			{
				if (PR->GetColliderSphere().Contains(m_house.ABOX) && this->m_house.HP > 0);
				{
					Cbullet* bullet = CManager::GetScene()->AddGameObject<Cbullet>(12);
					bullet->LoadTex(L"asset/GameTexture/BlueXBtama.png");
					bullet->SetPosition(XMFLOAT3(m_Position.x, m_Position.y + 3.0f, m_Position.z));
					bullet->SetTarget(Tama_RedXBfromB);
					bullet->SetenemyID(m_house.TargetID);
					bullet->SetScale({ 1.0f,1.0f,1.0f });
					bullet->SetPower(50.0f);
				}
			}
			m_timer->Reset();
			break;
		}
		default:
			break;
		}
	}
	//life=0;

	m_house.ABOX.Center = m_Position;

	XMFLOAT2  thispos= { m_Position.x,m_Position.z };
	pA->SetbeginPos(thispos);
	//
	m_t->Tick();

	CPlayer* pP0 = CManager::GetScene()->GetGmeobjs<CPlayer>(_Cplayer);
	float distance = Tool::Distance_float(pP0->GetPosition(), this->m_Position);
	

	if (m_t->TotalTime() >= 3.0f)
	{
		
		XMFLOAT2 p02DPO = { pP0->GetPosition().x ,pP0->GetPosition().z };
		if (distance >= 3.0f)
		{
			pA->SetTargetPos(p02DPO);
			pA->SetStartNode();
		}
		m_t->Reset();
	}
	pA->Update();
	if (distance >= 3.0f)
		pA->Move(m_Position, dt);
	else
	{
		pA->VPathClear();
		pA->PathReset();
	}
	


}

void SoldierHouseBlue::Draw()
{
	
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);//×ª¾ØÕóÈ«²¿
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	pMode->Render(world);
	//lineW
	XMMATRIX lineW= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y- XMConvertToRadians(90.0f), m_Rotation.z);
	lineW= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	//lifew
	XMMATRIX lifeW = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	lifeW *= XMMatrixTranslation(m_Position.x, m_Position.y + 3.0f, m_Position.z);
	m_line->DrawLineByPlayerWorld(lineW);
	m_house.pLife->SetWorld(lifeW);
}

House * SoldierHouseBlue::GetDate_house()
{
	return &m_house;
}
