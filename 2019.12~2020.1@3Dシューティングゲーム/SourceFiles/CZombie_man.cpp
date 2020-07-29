#include"B_header.h"
#include"CEnemyManager.h"


CZombie_man::CZombie_man()
{
	pModle = new CSkinnedfbxanim(ManDate, MAN_SIZE);
	pModle->SetInitanimation(Man_dead);
	

	BetRoot = new CSequence();
	BetRoot->AddNode(new CSeletor());
	BetRoot->AddNode(new CMove());


	CControlNode* pCnode = new CControlNode();
	pCnode->SetBlackBloadIndex(0);


	BetRoot->m_child[0]->AddNode(pCnode);
	BetRoot->m_child[0]->AddNode(new UnMove());


	ptimer = std::make_unique<Timer>();
	m_music = std::make_unique<Music>();
	
}


CZombie_man::~CZombie_man()
{
}

void CZombie_man::Init()
{
	PhySics = std::make_unique<CObjPhySics>(2.98f, 20.0f,20.0f);

	m_Position = XMFLOAT3(0.0f, 0.0f, 200.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.1f, 0.1f, 0.1f);
	sDate.Currentanim = Manwark_Up;
	sDate.IsDie = false;
	sDate.AnimationShow = false;
	sDate.StopControl = false;
	sDate.ZombieState = zombie_atRest;

	XMVECTOR Vmax = XMLoadFloat3(&pModle->m_GetBoxPinots()[0].m_BoxPoint.Vmax);
	XMVECTOR Vmin = XMLoadFloat3(&pModle->m_GetBoxPinots()[0].m_BoxPoint.Vmin);
	XMFLOAT3 vmax;
	XMFLOAT3 vmin;
	XMFLOAT3 v3[8];
	XMStoreFloat3(&vmax, Vmax);
	XMStoreFloat3(&vmin, Vmin);
	CCreate::CreateBox(m_box, vmax, vmin);
	CCreate::CreateV8(m_box, v3);
	vmax = { 5.0f,10.0f,5.0f };
	vmin = { -5.0f,0.0f,-5.0f };
	CCreate::CreateBox(mheadBox, vmax, vmin);

	m_line = new Line();
	m_line->InitDrawBox(v3);

	pAstar = std::make_unique<AStarPathFinding>();
	sDate.pStopTimer = new Timer();

	SetInitalState(zombie_InitalState);
	sDate.HP = 50;
	//test
	//SetInitalState(zombie_AlreadyDead);

}

void CZombie_man::Uninit()
{
	delete pModle;
	m_line->Uninit();
	delete m_line;
	delete BetRoot->m_child[0]->m_child[0];
	delete BetRoot->m_child[0]->m_child[1];
	delete BetRoot->m_child[1];
	delete BetRoot;
	delete sDate.pStopTimer;

}

void CZombie_man::Update(float dt)
{
	int animationspeed = 1.0f;
	//sDate.StopControl = true;
	//bool NoRun = ObjRun::ZombieDontMove();
	//if (!sDate.StopControl)
	//{
	//	if (!NoRun)
	//	{
	//		if (!sDate.IsDie && !sDate.AnimationShow)
	//		{
	//			BetRoot->Update(State, this);
	//			FSM(dt);
	//		}
	//		else if (sDate.AnimationShow)
	//		{
	//			ptimer->Tick();
	//			CP0* p0 = CManager::GetScene()->GetGmeobjs<CP0>(4);
	//			if (p0->GetP0Dataptr()->BeHurtAnimControl)
	//			{
	//				sDate.Currentanim = Man_attack_DH;
	//				XMVECTOR down = { 0.0f,0.0f,-1.0f };
	//				float deg = Tool::GetDegForP1ToP2(p0->GetPosition(), m_Position, down);
	//				m_Rotation.y = deg;
	//				ptimer->Reset();
	//			}
	//			else
	//			{
	//				sDate.Currentanim = Man_idle;
	//				m_Rotation.x = 0.0f;
	//				m_Rotation.z = 0.0f;
	//				m_Position.y = 0.0f;
	//				if (ptimer->TotalTime() >= 3.0f)
	//				{
	//					sDate.AnimationShow = false;
	//				}
	//			}
	//		}
	//	}
	//	else
	//	{
	//		sDate.Currentanim = Man_idle;
	//		m_Rotation.x = 0.0f;
	//		m_Rotation.z = 0.0f;
	//		m_Position.y = 0.0f;
	//	}
	//}
	//else
	//{
	//	sDate.pStopTimer->Tick();
	//	sDate.Currentanim = Man_idle;
	//	CP0* p0 = CManager::GetScene()->GetGmeobjs<CP0>(4);
	//	XMVECTOR down = { 0.0f,0.0f,-1.0f };
	//	float deg = Tool::GetDegForP1ToP2(p0->GetPosition(), m_Position, down);
	//	m_Rotation.y = deg;
	//	if (sDate.pStopTimer->TotalTime() >= 3.0f) sDate.StopControl = false;
	//}
	switch (sDate.ZombieState)
	{
	case zombie_active:
	{
		bool NoRun = ObjRun::ZombieDontMove();
		if (!sDate.StopControl)
		{
			if (!NoRun)
			{
				if (!sDate.IsDie && !sDate.AnimationShow)
				{
					BetRoot->Update(State, this);
					FSM(dt);
				}
				else if (sDate.AnimationShow)
				{
					ptimer->Tick();
					CP0* p0 = CManager::GetScene()->GetGmeobjs<CP0>(4);
					if (p0->GetP0Dataptr()->BeHurtAnimControl)
					{
						sDate.Currentanim = Man_attack_DH;
						XMVECTOR down = { 0.0f,0.0f,-1.0f };
						float deg = Tool::GetDegForP1ToP2(p0->GetPosition(), m_Position, down);
						m_Rotation.y = deg;
						ptimer->Reset();
					}
					else
					{
						sDate.Currentanim = Man_idle;
						m_Rotation.x = 0.0f;
						m_Rotation.z = 0.0f;
						m_Position.y = 0.0f;
						if (ptimer->TotalTime() >= 3.0f)
						{
							sDate.AnimationShow = false;
						}
					}
				}
			}
			else
			{
				sDate.Currentanim = Man_idle;
				m_Rotation.x = 0.0f;
				m_Rotation.z = 0.0f;
				m_Position.y = 0.0f;
			}
		}
		else
		{
			m_music->Stop(MusicPattern::Sound_StopAttack);
			sDate.pStopTimer->Tick();
			sDate.Currentanim = Man_idle;
			if (sDate.pStopTimer->TotalTime() >= 3.0f) sDate.StopControl = false;
		}
	}
		break;
	case zombie_atRest:
	{
		sDate.pStopTimer->Reset();
		PhySics->Gravity(m_Position,dt) == true ? sDate.ZombieState = zombie_atRest : sDate.ZombieState = zombie_atRestMove;
	}
		break;
	case zombie_atRestMove:
	{
		sDate.pStopTimer->Tick();
		XMVECTOR mVPos = XMLoadFloat3(&m_Position);
		XMVECTOR movedir = XMLoadFloat3(&sDate.BeginDir);
		XMVECTOR facedir = { 0.0f,0.0f,-1.0f };
		m_Rotation.y = Tool::GetDegForP1ToP2(movedir, facedir);
		mVPos += movedir * dt*ENEMYSP_WALK;
		if (sDate.pStopTimer->TotalTime() >= 6.0f)
		{
			sDate.ZombieState = zombie_active;
			sDate.pStopTimer->Reset();
			return;
		}


		XMStoreFloat3(&m_Position, mVPos);
	}
		break;
	case zombie_AlreadyDead:

		//test
		//m_Position = XMFLOAT3(0.0f, 0.0f, 200.0f);
		break;
	case zombie_InitalState:
		animationspeed = Tool::RandomInt(1, 100);
		break;
	}


	
	pModle->Update(dt, animationspeed);
}

void CZombie_man::Draw()
{
	XMMATRIX rotationX =
		XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);//转矩阵全部
	XMMATRIX world;
	world = rotationX;
	world *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMStoreFloat4x4(&m_WorldMatirx, world);
	pModle->Render(world, sDate.Currentanim);

	//
	XMMATRIX M_bodyW;
	M_bodyW= XMMatrixRotationRollPitchYaw(XMConvertToRadians(90), 0.0f, 0.0f);//转矩阵全部
	M_bodyW *= XMMatrixScaling(m_Scale.x-0.065f, m_Scale.y-0.025f, m_Scale.z+0.05f);
	M_bodyW *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMStoreFloat4x4(&Matrix_Box, M_bodyW);

	//
	XMMATRIX M_headW;
	M_headW = XMMatrixRotationRollPitchYaw(XMConvertToRadians(90), 0.0f, 0.0f);//转矩阵全部
	M_headW *= XMMatrixScaling(m_Scale.x - 0.09f, m_Scale.y - 0.08125f, m_Scale.z - 0.025f);
	M_headW *= XMMatrixTranslation(m_Position.x, m_Position.y+7.5f, m_Position.z-1.5f);
	XMStoreFloat4x4(&Matrix_HeadBox, M_headW);

	XMMATRIX Collider;
	Collider = XMMatrixRotationRollPitchYaw(XMConvertToRadians(90), 0.0f, 0.0f);//转矩阵全部
	Collider *= XMMatrixScaling(m_Scale.x - 0.005f, m_Scale.y - 0.025f, m_Scale.z + 0.3f);
	Collider *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	

	//m_line->DrawLineByPlayerWorld(M_bodyW);
}

BoundingBox CZombie_man::Get_box()
{
	BoundingBox box;
	m_box.Transform(box, XMLoadFloat4x4(&Matrix_Box));
	return box;
}

BoundingBox CZombie_man::Get_HeadBox()
{
	XMMATRIX textbox;
	textbox = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);//转矩阵全部
	textbox *= XMMatrixScaling(0.16f, 0.16f, 0.16f);
	textbox *= XMMatrixTranslation(m_Position.x, m_Position.y + 7.9f, m_Position.z);

	BoundingBox box;
	mheadBox.Transform(box, textbox);
	return box;
}

void CZombie_man::SetTriangle(XMFLOAT3 * Vpos)
{
}


void CZombie_man::FSMMove(float dt)
{
	CP0* pP0 = CManager::GetScene()->GetGmeobjs<CP0>(4);
	CMap* pMap = CManager::GetScene()->GetGmeobjs<CMap>(MAP_ID);
	XMVECTOR MyPos = this->GetVectorPos();
	MyPos = XMVectorSetY(MyPos, 0.0f);
	XMVECTOR P0Pos = pP0->GetVectorPos();
	P0Pos = XMVectorSetY(P0Pos, 0.0f);
	XMVECTOR Dir = XMVector3Normalize(P0Pos - MyPos);
	XMFLOAT3 RayDir;
	XMStoreFloat3(&RayDir, Dir);
	Ray ray(m_Position, RayDir);
	XMVECTOR Oldface = { 0.0f,0.0f,-1.0f,0.0f };
	float Deg= XMVectorGetY(XMVector3AngleBetweenVectors(Oldface, Dir));
	XMVECTOR Pos = XMLoadFloat3(&m_Position);
	bool MoveSwitch = true;

	float dis = Tool::Distance_float(pP0->GetPosition(), m_Position);

	switch (sDate.Currentanim)
	{
	case man_run:
		m_music->Stop(MusicPattern::Sound_StopAttack);
		m_music->Stop(MusicPattern::Sound_Attack);
		dis < 50.0f ? m_music->Start(MusicPattern::Sound_Barrking) : m_music->Stop(MusicPattern::Sound_Barrking);
		if (!sDate.iswall)
		{
			sDate.isFindPath = false;
			XMVECTOR MoveDir = Dir;
			if (Tool::Distance_float(pP0->GetPosition(), m_Position) > 8.0f);
			{
				for (int i = 0; i < ENEMY_SIZE; i++)
				{
					CZombie_man* pman = CManager::GetScene()->GetGmeobj<CZombie_man>(ENEMY_ID, i);
					if (pman != nullptr)
					{
						if (pman != this)
						{
							if (ray.Hit(pman->GetSphereBox(1.0f)) && CCollider::ISBOXHIT(this->GetSphereBox(1.0f), pman->Get_ColliderBox()))
							{
								XMVECTOR top = { 0.0f,1.0f,0.0f };
								XMVECTOR left = XMVector3Cross(XMLoadFloat3(&ray.direction), top);
								XMVECTOR targetDir = XMLoadFloat3(&pman->GetPosition()) - Pos;
								Tool::GET_ANGLE_DOT(targetDir, Dir) < 0.0f ? MoveDir = left : MoveDir = -left;
							}
						}
					}
				}
				Pos += MoveDir * dt*ENEMYSP_RUN;
				if (pP0->GetP0Dataptr()->CurrentAnim != _SsangDH)
				{
					if(dis<20.0f)
					{
					sDate.Currentanim = Man_StopAttack;
					}
				}
			}
			Tool::GET_ANGLE(Dir, Oldface) > 0.0f ? m_Rotation.y = -Deg : m_Rotation.y = Deg;
		}
	
		if (pMap->AreYouKnockingOnTheOBox(this, ray)) sDate.iswall = true;
		else if (pMap->AreYouKnockingOnTheABox(this, ray)) sDate.iswall = true;
		else sDate.iswall = false;

		

		break;
	case Manwark_Up:
		m_music->Stop(MusicPattern::Sound_StopAttack);
		m_music->Stop(MusicPattern::Sound_Attack);
		dis < 50.0f ? m_music->Start(MusicPattern::Sound_Barrking) : m_music->Stop(MusicPattern::Sound_Barrking);
		if (!sDate.iswall)
		{
			sDate.isFindPath = false;
			XMVECTOR MoveDir = Dir;
			for (int i = 0; i < ENEMY_SIZE; i++)
			{
				CZombie_man* pman = CManager::GetScene()->GetGmeobj<CZombie_man>(ENEMY_ID, i);
				if (pman != nullptr)
				{
					if (pman != this)
					{
						if (ray.Hit(pman->GetSphereBox(2.0f))&&CCollider::ISBOXHIT(this->GetSphereBox(2.0f),pman->Get_ColliderBox()))
						{
							XMVECTOR top = { 0.0f,1.0f,0.0f };
							XMVECTOR left = XMVector3Cross(XMLoadFloat3(&ray.direction), top);
							XMVECTOR targetDir = XMLoadFloat3(&pman->GetPosition())-Pos;
							
							Tool::GET_ANGLE_DOT(targetDir, Dir) < 0.0f ? MoveDir = left : MoveDir = -left;
						}
					}
				}
			}
			Pos += MoveDir * dt*ENEMYSP_WALK;
			if (pP0->GetP0Dataptr()->CurrentAnim != _SsangDH)
			{
				if (dis < 20.0f)
				{
					sDate.Currentanim = Man_StopAttack;
				}
			}
			Tool::GET_ANGLE(Dir, Oldface) > 0.0f ? m_Rotation.y = -Deg : m_Rotation.y = Deg;
			//sDate.RotDeg = m_Position.y;
		}

		//jian che AI pengzhuang
		if (pMap->AreYouKnockingOnTheOBox(this, ray)) sDate.iswall = true;
		else if (pMap->AreYouKnockingOnTheABox(this, ray)) sDate.iswall = true;
		else sDate.iswall = false;


		break;
	case Manhurt_duzhi:

		MoveSwitch = false;
		if (pModle->AiamFramManager(22.0f, Manhurt_duzhi))
		{
			sDate.Currentanim = Manwark_Up;
		}
		break;
	case Manhurt_head:

		MoveSwitch = false;
		if (pModle->AiamFramManager(20.0f, Manhurt_head))
		{
			sDate.Currentanim = Manwark_Up;
		}
		break;
	case Man_dead:
		m_music->Stop(MusicPattern::Sound_StopAttack);
		m_music->Stop(MusicPattern::Sound_Attack);
		m_music->Stop(MusicPattern::Sound_Barrking);
		m_music->Start(MusicPattern::Sound_die);

		MoveSwitch = false;
		if (pModle->PlayShot())
		{
			sDate.Currentanim = Man_isDie;
			sDate.IsDie = true;
			CFont* pf = CManager::GetScene()->GetGmeobjs<CFont>(FONT_ID);
			pf->GetNumDatePtr()->EnemyCountInTheScene -= 1.0f;
			SetInitalState(zombie_AlreadyDead);
		}
		break;
	case Man_StopAttack:
		m_music->Start(MusicPattern::Sound_StopAttack);
		XMVECTOR MoveDir = Dir;
		for (int i = 0; i < ENEMY_SIZE; i++)
		{
			CZombie_man* pman = CManager::GetScene()->GetGmeobj<CZombie_man>(ENEMY_ID, i);
			if (pman != nullptr)
			{
				if (pman != this)
				{
					if (ray.Hit(pman->GetSphereBox(2.0f)) && CCollider::ISBOXHIT(this->GetSphereBox(2.0f), pman->Get_ColliderBox()))
					{
						XMVECTOR top = { 0.0f,1.0f,0.0f };
						XMVECTOR left = XMVector3Cross(XMLoadFloat3(&ray.direction), top);
						XMVECTOR targetDir = XMLoadFloat3(&pman->GetPosition()) - Pos;

						Tool::GET_ANGLE_DOT(targetDir, Dir) < 0.0f ? MoveDir = left : MoveDir = -left;
					}
				}
			}
		}
		if (!pModle->AiamFramManager(30.0f, Man_StopAttack))
		{
			Pos += MoveDir * dt*ENEMYSP_RUN*1.2f;
		}
		else
		{
			XMVECTOR dir = (Tool::GetNowFaceDir(GetMatrixForWorld()));
			XMFLOAT3 _dir;
			XMStoreFloat3(&_dir, XMVector3Normalize(dir));
			Ray ray(m_Position, _dir);

			if (ray.Hit(CCollider::GetShere(pP0->GetPosition(), 2.0f))&&dis<=8.0f)
			{
				//m_music->Stop(MusicPattern::Sound_StopAttack);
				pP0->GetP0Dataptr()->HP -= 3.0f;
				if (pP0->GetP0Dataptr()->HP < 0.0f) pP0->GetP0Dataptr()->HP = 1.0f;
				pP0->SetShejiBool(false);
				pP0->GetP0Dataptr()->BeHurtAnimControl = true;
				pP0->GetP0Dataptr()->targetID = sDate.ID;
				sDate.AnimationShow = true;
				pP0->SetMovie(LensOne);
				UImanager3D* pUi = CManager::GetScene()->GetGmeobjs<UImanager3D>(UI_ID);
				pUi->RestScene();
				return;
			}
		}
		if (pModle->AiamFramManager(39.0f, Man_StopAttack))
		{
			sDate.pStopTimer->Reset();
			sDate.StopControl = true;
			return;
		}
		break;
	}
	if (sDate.HP > 0)
	{
		if (sDate.Currentanim != Man_StopAttack)
		{
			if (MoveSwitch) (sDate.HP > 20) ? sDate.Currentanim = Manwark_Up : sDate.Currentanim = man_run;
		}
	}
	else
	{
		sDate.Currentanim != Man_isDie ? sDate.Currentanim = Man_dead : sDate.Currentanim = Man_isDie;
	}

	XMFLOAT3 WithOutHeight;
	XMStoreFloat3(&WithOutHeight, Pos);
	pMap->SetObjectHeight(this, WithOutHeight,2.0f);
	m_Position = WithOutHeight;
}

void CZombie_man::UNMove(float dt)
{
	CP0* pP0 = CManager::GetScene()->GetGmeobjs<CP0>(4);
	bool UNMoveSwitch = true;


	switch (sDate.Currentanim)
	{
	case Manhurt_duzhi:
		UNMoveSwitch = false;
		if (pModle->AiamFramManager(22.0f, Manhurt_duzhi))
		{
			sDate.Currentanim = Man_attack;
		}
		break;
	case Manhurt_head:
		UNMoveSwitch = false;
		if (pModle->AiamFramManager(20.0f, Manhurt_head))
		{
			sDate.Currentanim = Man_attack;
		}
		break;
	case Man_attack:
		m_music->Stop(MusicPattern::Sound_StopAttack);
		m_music->Stop(MusicPattern::Sound_Barrking);
		m_music->Start(MusicPattern::Sound_Attack);
		//if (pP0->GetP0Dataptr()->CurrentAnim != _SsangDH)
		//{
		//	if (pModle->AiamFramManager(10.0f, Man_attack))
		//	{
		//		XMVECTOR dir = ( Tool::GetNowFaceDir(GetMatrixForWorld()));
		//		XMFLOAT3 _dir;
		//		XMStoreFloat3(&_dir, XMVector3Normalize( dir));
		//		Ray ray(m_Position, _dir);

		//		if (ray.Hit(CCollider::GetShere(pP0->GetPosition(),2.0f)))
		//		{
		//			pP0->SetShejiBool(false);
		//			pP0->GetP0Dataptr()->BeHurtAnimControl = true;
		//			pP0->GetP0Dataptr()->targetID = sDate.ID;
		//			sDate.AnimationShow = true;
		//			pP0->SetMovie(LensOne);
		//			UImanager3D* pUi = CManager::GetScene()->GetGmeobjs<UImanager3D>(UI_ID);
		//			pUi->RestScene();
		//			return;
		//		}
		//		else
		//		{
		//			sDate.pStopTimer->Reset();
		//			sDate.StopControl = true;
		//			return;
		//		}
		//	}
		//}
		//else
		{
			if (pModle->PlayerOnce(10.0f, Man_attack, once))
			{
				if (pP0->GetP0Dataptr()->HP > 1.0f)
				{
					pP0->GetP0Dataptr()->HP -= 1.0f;
				}
			}
			if (pModle->PlayerOnce(30.0f, Man_attack, once2))
			{
				if (pP0->GetP0Dataptr()->HP > 1.0f)
				{
					pP0->GetP0Dataptr()->HP -= 1.0f;
				}
			}
			
		}
		

		break;
	case Man_dead:
		m_music->Stop(MusicPattern::Sound_StopAttack);
		m_music->Stop(MusicPattern::Sound_Attack);
		m_music->Stop(MusicPattern::Sound_Barrking);
		m_music->Start(MusicPattern::Sound_die);
		UNMoveSwitch = false;
		if (pModle->PlayShot())
		{
			sDate.Currentanim = Man_isDie;
			sDate.IsDie = true;
			CFont* pf = CManager::GetScene()->GetGmeobjs<CFont>(FONT_ID);
			pf->GetNumDatePtr()->EnemyCountInTheScene -= 1.0f;
			SetInitalState(zombie_AlreadyDead);
		}
		break;
	}
	if (sDate.HP > 0)
	{
		if (UNMoveSwitch) sDate.Currentanim = Man_attack;
	}
	else sDate.Currentanim != Man_isDie ? sDate.Currentanim = Man_dead : sDate.Currentanim = Man_isDie;

}

bool CZombie_man::isBool(int index)
{
	switch (index)
	{
	case 0:
					{
						CP0* pP0 = CManager::GetScene()->GetGmeobjs<CP0>(4);
						float dist = Tool::Distance_float(this->GetPosition(), pP0->GetPosition());

						if (sDate.Currentanim != Man_StopAttack)
						{
							if (dist > 8.0f) return true;
							else return false;
						}
						else
						{
							return true;
						}
					}
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	}
	return false;
}

void CZombie_man::SetAtRestPos(int a, int b)
{
	sDate.RestPos = ZombieRestPos(Tool::RandomInt(a, b));
	switch (sDate.RestPos)
	{
	case zombie_posDoor:
	{
		m_Position = { 4.0f,50.0f,470.0f };
		sDate.BeginDir = { 0.0f,0.0f,-1.0f };
		XMVECTOR pos = XMVector3Normalize(XMLoadFloat3(&sDate.BeginDir));
		XMStoreFloat3(&sDate.BeginDir, pos);
		sDate.ZombieState = zombie_atRest;
	}
		break;
	case zombie_posLeft:
	{
		m_Position = { 165.0f,50.0f,80.0f };
		sDate.BeginDir = { -1.0f,0.0f,0.0f };
		XMVECTOR pos = XMVector3Normalize(XMLoadFloat3(&sDate.BeginDir));
		XMStoreFloat3(&sDate.BeginDir, pos);
		sDate.ZombieState = zombie_atRest;
	}
		break;
	case zombie_posRight:
	{
		m_Position = { -165.0f,50.0f,80.0f };
		XMVECTOR pos = { -165.0f,0.0f,80.0f };
		XMVECTOR endpos = { -136.0f,0.0f,106.0f };
		XMStoreFloat3(&sDate.BeginDir, XMVector3Normalize(endpos - pos));
		sDate.ZombieState = zombie_atRest;
	}
		break;
	case zombie_posTop:
	{
		m_Position = {0.0f,50.0f,-120.0f};
		XMVECTOR dir = { 0.0f,0.0f,1.0f };
		XMStoreFloat3(&sDate.BeginDir, XMVector3Normalize(dir));
		sDate.ZombieState = zombie_atRest;
	}
		break;
	}
}
void CZombie_man::SetInitalState(ZombieState state)
{

	//m_Position.y = 200.0f;
	sDate.ZombieState = zombie_InitalState;
	switch (state)
	{
	case zombie_AlreadyDead:
		m_music->Stop(MusicPattern::Sound_Stop);
		sDate.ZombieState = state;
		break;
	case zombie_InitalState:
	{
		CFont* pf = CManager::GetScene()->GetGmeobjs<CFont>(FONT_ID);
		sDate.Currentanim = Manwark_Up;
		if (pf != nullptr)
		{
			sDate.HP = 50+pf->GetNumDatePtr()->StageNum*10.0f;
		}
		sDate.IsDie = false;
		sDate.AnimationShow = false;
		sDate.StopControl = false;

		m_Position.y = 200.0f;
		sDate.ZombieState = state;
	}
		break;
	}
}
