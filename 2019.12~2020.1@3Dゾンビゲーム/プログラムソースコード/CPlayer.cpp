#include"B_header.h"
#include<dinput.h>
#include"input.h"
#include"SCRole_move_manager.h"
#include"Ray_collision.h"
#include"BlueTeam.h"
//使用scene时注意要全部inlucd；
//CScene* scene;

CPlayer::CPlayer()
{
	m_model = new CSkinnedfbxanim( NQDate, NQsize);
	Player_1_Date.CurrentAnim = _idie;
	m_model->SetInitanimation(Player_1_Date.CurrentAnim);
	Player_1_Date.UpAnim = true;
	Player_1_Date.pLife = new CPolygon();
	Player_1_Date.pLife->Init3D(0);
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	move.ismove = false;
	m_Position = XMFLOAT3(-9.5, 0.0f, 3.5);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.013f, 0.013f, 0.013f);

	XMVECTOR vmax = XMVector3TransformCoord(
		XMLoadFloat3(&m_model->m_GetBoxPinots()[2].m_BoxPoint.Vmax),
		XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z));
	XMVECTOR vmin = XMVector3TransformCoord(
		XMLoadFloat3(&m_model->m_GetBoxPinots()[2].m_BoxPoint.Vmin),
		XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z));
	XMMATRIX lineRot= XMMatrixRotationRollPitchYaw(m_Rotation.x + XMConvertToRadians(90.0f), m_Rotation.y, m_Rotation.z);
	vmax = XMVector3TransformCoord(vmax, lineRot);
	vmin = XMVector3TransformCoord(vmin, lineRot);
	XMFLOAT3 Vmax;
	XMFLOAT3 Vmin;
	XMStoreFloat3(&Vmax, vmax);
	XMStoreFloat3(&Vmin, vmin);
	CCreate::CreateBox(Player_1_Date.AABBBOX, Vmax,Vmin);
	XMFLOAT3 v3[8];
	CCreate::CreateV8(this->Player_1_Date.AABBBOX, v3);
	m_line = new Line();
	m_line->InitDrawBox(v3);
}

void CPlayer::Uninit()
{
	m_line->Uninit();
	Player_1_Date.pLife->Uninit3D(0);
	delete Player_1_Date.pLife;
	delete m_line;
	delete m_model;
}

void CPlayer::Update(float dt)
{
	if (Player_1_Date.UpAnim)
		Player_1_Date.CurrentAnim = 0;
	//玩家移动开始
	//if(!CAttack::isEnemy())
	static float ratationCount = 0.0f;
	if (MoveCharactersManager::ismove(move.FDirection, move.PointIO, m_Position, move.RXMTRIX, move.Radians,move.isenemy, move.enemyID, Player_1_Date.target))
	{
		Player_1_Date.UpAnim = true;
		move.ismove = true;
		m_model->ResetTimer();
	}
	int Dis=0;
	if (move.isenemy)
	{
		if (move.ismove)
		{
			
			switch (Player_1_Date.target)
			{
			case Tama_BlueXB:
			{
				CBlueArmy* parmy = CManager::GetScene()->GetGmeobj<CBlueArmy>(5, move.enemyID);
				Dis = Tool::Distance(parmy->GetPosition(), m_Position);
				break;
			}
			case Tama_BlueHouse:
			{
				SoldierHouseBlue* pBhouse = CManager::GetScene()->GetGmeobjs<SoldierHouseBlue>(7);
				Dis = Tool::Distance(pBhouse->GetPosition(),m_Position);
				break;
			}
			}
		}
	}
	else  Dis = Tool::Distance(move.PointIO, m_Position);
	if (move.ismove)
	{
		MoveCharactersManager::PlayerMove(m_Position, m_Rotation, move.FDirection, move.RXMTRIX,
			Dis, ORSP, OTSP, ratationCount, move.Radians, dt, move.ismove, move.isenemy,6.0f);
		Player_1_Date.CurrentAnim = _Run;

	}
	else
	{
		if (move.isenemy)
		{
			switch (Player_1_Date.target)
			{
			case Tama_BlueXB:
			{
				CBlueArmy* parmy = CManager::GetScene()->GetGmeobj<CBlueArmy>(5, move.enemyID);
				XMVECTOR emdire = XMLoadFloat3(&parmy->GetPosition());
				XMVECTOR dir = XMVector3Normalize(emdire - XMLoadFloat3(&m_Position));
				MoveCharactersManager::Lookat(m_Rotation, dir, move.RXMTRIX);
				Player_1_Date.UpAnim = false;
				Player_1_Date.CurrentAnim = 1;
				break;
			}
			case Tama_BlueHouse:
			{
				SoldierHouseBlue* pBhouse = CManager::GetScene()->GetGmeobjs<SoldierHouseBlue>(7);
				XMVECTOR emdire = XMLoadFloat3(&pBhouse->GetPosition());
				XMVECTOR dir = XMVector3Normalize(emdire - XMLoadFloat3(&m_Position));
				MoveCharactersManager::Lookat(m_Rotation, dir, move.RXMTRIX);
				Player_1_Date.UpAnim = false;
				Player_1_Date.CurrentAnim = 1;
				break;
			}
			default:
				break;
			}
		}
	}
//普通攻击开始
	if (CInput::GetKeyTrigger('K'))
	{
		//
		if (Player_1_Date.CurrentAnim != _NAttack)
		{
			move.ismove = false;
			Player_1_Date.PlayerOne = false;
			m_model->ResetTimer();
			Player_1_Date.UpAnim = false;
			Player_1_Date.CurrentAnim = _NAttack;
		}
		
	}
	if (CInput::GetKeyPress('J'))
	{
		if (Player_1_Date.CurrentAnim != _Skill_one)
		{
			move.ismove = false;
			//Player_1_Date.PlayerOne = false;
			m_model->ResetTimer();
			Player_1_Date.UpAnim = false;
			Player_1_Date.CurrentAnim = _Skill_one;
		}
	}
	if (m_model->AiamFramManager(80.0f, _NAttack))
	{
		Player_1_Date.UpAnim = true;
	}
	else if(m_model->AiamFramManager(126.0f,_Skill_one))
	{
		Player_1_Date.UpAnim = true;
	}
	else if (m_model->AnimShow(31.0f, 1))
	{
		switch (Player_1_Date.target)
		{
		case Tama_BlueXB:
		{
			Cbullet* bullet = CManager::GetScene()->AddGameObject<Cbullet>(12);
			XMFLOAT3 bulletPos = { m_Position.x,2.0f,m_Position.z };
			bullet->LoadTex(L"asset/GameTexture/zhidan.png");
			bullet->SetPosition(bulletPos);
			bullet->SetTarget(Tama_BlueXB);
			bullet->SetenemyID(move.enemyID);
			bullet->SetPower(50.0f);
			break;
		}
		case Tama_BlueHouse:
		{
			Cbullet* bullet = CManager::GetScene()->AddGameObject<Cbullet>(12);
			XMFLOAT3 bulletPos = { m_Position.x,2.0f,m_Position.z };
			bullet->LoadTex(L"asset/GameTexture/zhidan.png");
			bullet->SetPosition(bulletPos);
			bullet->SetTarget(Tama_BlueHouse);
			bullet->SetenemyID(1);
			bullet->SetPower(500.0f);
			break;
		}
		default:
			break;
		}
	}

	Player_1_Date.AABBBOX.Center = m_Position;
	m_model->Update(dt, 1.0f);
	/*Friend*pFriend = CManager::GetScene()->GetGmeobjs<Friend>(_Friend);
	if(pFriend!=nullptr)
	pFriend->SetPos(m_Position);*/
	CRenderer::Debug_move_Rotation2[0] = m_Position.x;
	CRenderer::Debug_move_Rotation2[1] = m_Position.z;
}

void CPlayer::Draw()
{
	XMMATRIX rotationX=
	XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);//转矩阵全部
	XMMATRIX world;
	world = rotationX;
	world *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMStoreFloat4x4(&move.RXMTRIX, rotationX);

	XMMATRIX worldx;
	worldx = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	worldx *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	XMMATRIX lifeW = XMMatrixScaling(0.5f,0.5f,0.5f);
	lifeW *= XMMatrixTranslation(m_Position.x, m_Position.y+1.0f, m_Position.z);
	//m_model->DrawAny();
	m_model->Render(world, Player_1_Date.CurrentAnim);
	m_line->DrawLineByPlayerWorld(worldx);
	Player_1_Date.pLife->SetWorld(lifeW);

}


BoundingOrientedBox CPlayer::GetBoundingOrientedBox()
{
	BoundingOrientedBox box;
	BoundingOrientedBox::CreateFromBoundingBox(box, Player_1_Date.AABBBOX);
	box.Transform(box, XMLoadFloat4x4(&Player_1_Date.m_WorldXmmrix));
	return box;
}

BoundingSphere CPlayer::GetColliderSphere()
{
	BoundingSphere Range; Range.Center = m_Position;
	Range.Radius = EnemyAttackRange; return Range;
}

LPlayerOneDate * CPlayer::GetP0Date()
{
	return &Player_1_Date;
}









