#include"B_header.h"


CMap::CMap()
{
}


CMap::~CMap()
{
}


void CMap::Init()
{
	m_Position = { 0.0f,0.0f,0.0f };
	m_Rotation =	{ 0.0f,0.0f,0.0f };
	m_Scale =		{ 1.0f,1.0f,1.0f };

	XMFLOAT3 pos = { -130.0f,0.0f,90.0f };
	XMFLOAT3 rot = { 0.0f,0.0f,0.0f };
	XMFLOAT3 sca = { 1.0f,1.0f,1.0f };
	//box0
	XMFLOAT3 vmax =		{ 145.0f,10.0f,230.0f };
	XMFLOAT3 vmin =		{ 143.0f,0.0f,-155.0f};
	/*XMFLOAT3 vmax = { 75.0f,10.0f,230.0f };
	XMFLOAT3 vmin = { 73.0f,0.0f,-155.0f };*/
	CCreate::CreateBox(box0, vmax, vmin);

	//box1
	XMFLOAT3 vmax1 = { 150.0f,10.0f,220.0f };
	XMFLOAT3 vmin1 = { 30.0f,0.0f,210.0f };
	CCreate::CreateBox(Box1, vmax1, vmin1);

	//box2
	XMFLOAT3 vmax2 = { 85.0f,10.0f,450.0f };
	XMFLOAT3 vmin2 = { 30.0f,0.0f,220.0f };
	CCreate::CreateBox(Box2, vmax2, vmin2);

	//box3
	XMFLOAT3 vmax3 = { -30,10.0f,450.0f };
	XMFLOAT3 vmin3 = { -85,0.0f,220.0f };
	CCreate::CreateBox(Box3, vmax3, vmin3);

	//box4
	XMFLOAT3 vmax4 = { -30.0f,10.0f,220.0f };
	XMFLOAT3 vmin4 = { -150.0f,0.0f,210.0f };
	CCreate::CreateBox(Box4, vmax4, vmin4);

	//box5
	XMFLOAT3 vmax5 = { -143.0f,10.0f,230.0f };
	XMFLOAT3 vmin5 = { -145.0f,0.0f,-155.0f };
	CCreate::CreateBox(Box5, vmax5, vmin5);

	
	//box6 left 
	XMFLOAT3 vmax6 = { 150.0f,80.0f,-145.0f };
	XMFLOAT3 vmin6 = { -30.0f,0.0f,-210.0f };
	CCreate::CreateBox(Box6, vmax6, vmin6);

	//box7 right 
	XMFLOAT3 vmax7 = { -30.0f,80.0f,-145.0f };
	XMFLOAT3 vmin7 = { -150.0f,0.0f,-210.0f };
	CCreate::CreateBox(Box7, vmax7, vmin7);

	//box8 left 
	XMFLOAT3 vmax8 = { 75.0f,22.0f,-75.0f };
	XMFLOAT3 vmin8 = { 65.0f,0.0f,-155.0f };
	CCreate::CreateBox(Box8, vmax8, vmin8);

	//box9 right 
	XMFLOAT3 vmax9 = { -73.0f,22.0f,-75.0f };
	XMFLOAT3 vmin9 = { -65.0f,0.0f,-155.0f };
	CCreate::CreateBox(Box9, vmax9, vmin9);

	//box10 right 
	XMFLOAT3 vmax10 = { -63.0f,35.0f,-67.0f };
	XMFLOAT3 vmin10 = { -75.0f,0.0f,-78.0f };
	CCreate::CreateBox(Box10, vmax10, vmin10);

	//box11 left 
	XMFLOAT3 vmax11 = { 75.0f,35.0f,-67.0f };
	XMFLOAT3 vmin11 = { 63.0f,0.0f,-78.0f };
	CCreate::CreateBox(Box11, vmax11, vmin11);

	//box12 mid 
	XMFLOAT3 vmax12 = { 63.0f,20.0f,-75.0f };
	XMFLOAT3 vmin12 = { -63.0f,0.0f,-85.0f };
	CCreate::CreateBox(Box12, vmax12, vmin12);

	//box13 left 
	XMFLOAT3 vmax13 = { 37.0f,25.0f,-39.0f };
	XMFLOAT3 vmin13 = { 27.0f,0.0f,-75.0f };
	CCreate::CreateBox(Box13, vmax13, vmin13);

	//box14 right 
	XMFLOAT3 vmax14 = { -27.0f,25.0f,-39.0f };
	XMFLOAT3 vmin14= { -37.0f,0.0f,-75.0f };
	CCreate::CreateBox(Box14, vmax14, vmin14);

	//box15 right  zhu zi
	XMFLOAT3 vmax15 = { -25.0f,35.0f,-39.0f };
	XMFLOAT3 vmin15 = { -40.0f,0.0f,-29.0f };
	CCreate::CreateBox(Box15, vmax15, vmin15);

	//box16 left 
	XMFLOAT3 vmax16 = { 40.0f,35.0f,-39.0f };
	XMFLOAT3 vmin16 = { 25.0f,0.0f,-29.0f };
	CCreate::CreateBox(Box16, vmax16, vmin16);

	//box17  
	XMFLOAT3 vmax17 = { -72.0f,35.0f,230.0f };
	XMFLOAT3 vmin17 = { -106.0f,0.0f,180.0f };
	CCreate::CreateBox(Box17, vmax17, vmin17);

	//box18  
	XMFLOAT3 vmax18 = { -72.0f,35.0f,200.0f };
	XMFLOAT3 vmin18 = { -130.0f,0.0f,170.0f };
	CCreate::CreateBox(Box18, vmax18, vmin18);

	//box19  
	vmax = { 14.0f,12.0f,21.0f };
	vmin = { 0.0f,0.0f,0.0f };
	CCreate::CreateBox(Box19obb, vmax, vmin);

	//box20  
	vmax = { 14.0f,12.0f,21.0f };
	vmin = { 0.0f,0.0f,0.0f };
	CCreate::CreateBox(Box20obb, vmax, vmin);

	//box21  
	XMFLOAT3 vmax21 = { 15.0f,15.0f,23.0f };
	XMFLOAT3 vmin21 = { 0.0f,0.0f,0.0f };
	CCreate::CreateBox(Box21obb, vmax21, vmin21);


	//box22  
	XMFLOAT3 vmax22 = { 16.0f,35.0f,23.0f };
	XMFLOAT3 vmin22 = { 0.0f,0.0f,0.0f };
	CCreate::CreateBox(Box22obb, vmax22, vmin22);


	//box23  
	 vmax = { 14.0f,12.0f,21.0f };
	 vmin = { 0.0f,0.0f,0.0f };
	CCreate::CreateBox(Box23obb, vmax, vmin);

	//zui you
	//box24  
	//障害専用BOX 
	vmax = { 14.0f,12.0f,21.0f };
	vmin = { 0.0f,0.0f,0.0f };
	CCreate::CreateBox(Box24obb, vmax, vmin);

	vmax = { 142.0f,20.0f,208.0f };
	vmin = { -142.0f,0.0f,-143.0f };
	CCreate::CreateBox(Box25obb, vmax, vmin);

	vmax = { 35.0f,20.0f,439.0f };
	vmin = { -35.0f,0.0f, 208.0f};
	CCreate::CreateBox(Box26obb, vmax, vmin);

	vmax = { 43.0f,10.0f,40.0f };
	vmin = { -40.0f,0.0f, -6.0f };
	CCreate::CreateBox(Box27obb, vmax, vmin);

	//Fbox  
	XMFLOAT3 vmaxf0= { 27.0f,25.0f,-35.0f };
	XMFLOAT3 vminf0 = { -27.0f,10.0f,-85.0f };
	CCreate::CreateBox(floorBox0, vmaxf0, vminf0);

	//Fbox 1 
	XMFLOAT3 vmaxf1 = { 70.0f,28.0,-71.0f };
	XMFLOAT3 vminf1 = { -70.0f,20.0f,-150.0f };
	CCreate::CreateBox(floorBox1, vmaxf1, vminf1);

	//Fbox2
	XMFLOAT3 vmaxf2 = { 37.0f,30.0f,-35.0f };
	XMFLOAT3 vminf2 = { 27.0f,28.0f,-75.0f };
	CCreate::CreateBox(floorBox2, vmaxf2, vminf2);

	//Fbox3 right
	XMFLOAT3 vmaxf3 = { -27.0f,30.0f,-35.0f };
	XMFLOAT3 vminf3= { -37.0f,28.0f,-75.0f };
	CCreate::CreateBox(floorBox3, vmaxf3, vminf3);

	XMFLOAT3 v3[8];
	CCreate::CreateV8(floorBox0, v3);

	pWorldCollider = new Line();
	pWorldCollider->InitDrawBox(v3);


	

	//MapSet用
	sBOX.ABOX.push_back(GetWallBox(25));
	sBOX.ABOX.push_back(GetWallBox(26));
	sBOX.OBOX.push_back(Get_OBBOX(9));
	sBOX.OBOX.push_back(Get_OBBOX(10));
	sBOX.OBOX.push_back(Get_OBBOX(11));
	sBOX.OBOX.push_back(Get_OBBOX(12));
	sBOX.OBOX.push_back(Get_OBBOX(13));
	sBOX.OBOX.push_back(Get_OBBOX(6));
	sBOX.OBOX.push_back(Get_OBBOX(5));
	sBOX.OBOX.push_back(Get_OBBOX(4));
	sBOX.OBOX.push_back(Get_OBBOX(3));
	sBOX.OBOX.push_back(Get_OBBOX(2));
	sBOX.OBOX.push_back(Get_OBBOX(1));
	sBOX.OBOX.push_back(Get_OBBOX(0));
	sBOX.BlockABOX.push_back(GetWallBox(8));
	sBOX.BlockABOX.push_back(GetWallBox(9));
	sBOX.BlockABOX.push_back(GetWallBox(10));
	sBOX.BlockABOX.push_back(GetWallBox(11));
	sBOX.BlockABOX.push_back(GetWallBox(12));
	sBOX.BlockABOX.push_back(GetWallBox(13));
	sBOX.BlockABOX.push_back(GetWallBox(14));
	sBOX.BlockABOX.push_back(GetWallBox(15));
	sBOX.BlockABOX.push_back(GetWallBox(16));

	// AI当たり判定用
	
	sBOXBlock.OBOX.push_back(Get_OBBOX(12));
	sBOXBlock.OBOX.push_back(Get_OBBOX(13));
	sBOXBlock.OBOX.push_back(Get_OBBOX(11));
	sBOXBlock.OBOX.push_back(Get_OBBOX(10));
	sBOXBlock.OBOX.push_back(Get_OBBOX(9));
	sBOXBlock.OBOX.push_back(Get_OBBOX(6));
	sBOXBlock.OBOX.push_back(Get_OBBOX(5));
	sBOXBlock.OBOX.push_back(Get_OBBOX(4));
	sBOXBlock.OBOX.push_back(Get_OBBOX(3));
	sBOXBlock.OBOX.push_back(Get_OBBOX(2));
	sBOXBlock.OBOX.push_back(Get_OBBOX(1));
	sBOXBlock.OBOX.push_back(Get_OBBOX(0));
	sBOXBlock.ABOX.push_back(GetWallBox(10));
	sBOXBlock.ABOX.push_back(GetWallBox(11));
	sBOXBlock.ABOX.push_back(GetWallBox(9));
	sBOXBlock.ABOX.push_back(GetWallBox(8));
	sBOXBlock.ABOX.push_back(GetWallBox(12));
	sBOXBlock.ABOX.push_back(GetWallBox(13));
	sBOXBlock.ABOX.push_back(GetWallBox(14));
	sBOXBlock.ABOX.push_back(GetWallBox(15));
	sBOXBlock.ABOX.push_back(GetWallBox(16));
	sBOXBlock.ABOX.push_back(GetWallBox(1));
	sBOXBlock.ABOX.push_back(GetWallBox(2));
	sBOXBlock.ABOX.push_back(GetWallBox(3));
	sBOXBlock.ABOX.push_back(GetWallBox(4));
	sBOXBlock.OBOX.push_back(Get_OBBOX(14));
	sBOXBlock.OBOX.push_back(Get_OBBOX(15));

	SetUpMap(sBOX);
	pA = new AStarPathFinding();
	pA->Init(Map);


	for (int i = 0; i < ENEMY_SIZE; i++)
	{
		CZombie_man* pMan = CManager::GetScene()->GetGmeobj<CZombie_man>(ENEMY_ID,i);
		if (pMan != nullptr)
		{
			AStarPathFinding* ptr = pMan->GetPointForAstar();
			ptr->Init(Map);
			BodyWallMapPos.push_back(ptr->GetUpdateMapPos());
		}
	}
	CEnemy* pe = CManager::GetScene()->GetGmeobjs<CEnemy>(6);
	pe->GetPointForAstar()->Init(Map);


}

void CMap::Uninit()
{
	pWorldCollider->Uninit();
	delete pWorldCollider;
	pA->Uinit();
	delete pA;
}

void CMap::Update(float dt)
{
	//CP0*pp = CManager::GetScene()->GetGmeobjs<CP0>(4);
	//CZombie_man* pMan = CManager::GetScene()->GetGmeobjs<CZombie_man>(7);
	//ZOMBIEDATE* sdate = pMan->Get_Date();
	//AStarPathFinding* pS = pMan->GetAstatptr();
	//XMFLOAT2  thispos = { pp->GetPosition().x,pp->GetPosition().z };
	//pA->SetbeginPos(thispos);
	/*if (CRenderer::Debug_move_v3[0] == 0)
	{
		if (CInput::GetKeyTrigger(VK_SPACE))
		{
			pA->PathReset();
			pA->SetbeginPos({ pMan->GetPosition().x,	pMan->GetPosition().z });
			pA->SetTargetPos({ pp->GetPosition().x, pp->GetPosition().z });

			pA->SetStartNode();
		}
	}*/

	//Astarxun lu 


	//if (sdate->iswall)
	//{
	//	
	//	if (!sdate->isFindPath)
	//	{
	//		pS->PathReset();
	//		pS->SetbeginPos({ pMan->GetPosition().x,	pMan->GetPosition().z });
	//		pS->SetTargetPos({ pp->GetPosition().x, pp->GetPosition().z });

	//		pS->SetStartNode();
	//		sdate->isFindPath = true;
	//	}


	//	XMFLOAT3 pos = pMan->GetPosition();
	//	XMVECTOR Dir = XMVector3Normalize(XMLoadFloat3(&pos));
	//	XMVECTOR Oldface = { 0.0f,0.0f,-1.0f,0.0f };
	//	XMVECTOR Nowface = XMVector3TransformNormal(Oldface, pMan->GetMyMatrix());

	//	pS->Update();

	//	float blendtimer;
	//	float DegControl;
	//	sdate->HP > 20.0f ? pS->Move(pos, dt, Dir, blendtimer, DegControl, ENEMYSP_WALK,sdate->iswall,Nowface) : pS->Move(pos, dt, Dir, blendtimer, DegControl, ENEMYSP_RUN,sdate->iswall,Nowface);
	//	float Deg = XMVectorGetY(XMVector3AngleBetweenVectors(Nowface, Dir));
	//	(DegControl < 0.0f) ? pMan->SetMyRotY(Tool::KeepDecimal2(-Deg * blendtimer,2)) : pMan->SetMyRotY(Tool::KeepDecimal2(Deg * blendtimer,2));
	//	SetObjectHeight(pMan, pos,2.0f);
	//	pMan->SetPosition(pos);

	//}
	//else
	//{
	//	pS->RestIsfindpath();
	//	pS->VPathClear();
	//}
	
	///???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
	AIAction(0,dt);

		
}

void CMap::Draw()
{
	XMMATRIX world;
	world = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);





	//XMFLOAT3 pos = { 0.0f,-19.0f,-9.0f };
	//XMFLOAT3 rot = { XMConvertToRadians(13.0f),0.0f,0.0f };
	//XMFLOAT3 sca = { 1.0f,1.0f,1.0f };

	


	XMMATRIX worlds;
	worlds = XMMatrixRotationRollPitchYaw(XMConvertToRadians(35.0f), 0.0f, 0.0f);
	worlds *= XMMatrixScaling(1.0f, 1.0f, 1.0f);
	worlds *= XMMatrixTranslation(0.0f, -40.0f, -20.0f);

	//XMMATRIX worlds;
	//worlds = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
	//worlds *= XMMatrixScaling(sca.x, sca.y, sca.z);
	//worlds *= XMMatrixTranslation(pos.x, pos.y, pos.z);

	pWorldCollider->DrawLineByPlayerWorld(worlds);
}

bool CMap::AreYouKnockingOnTheABox(CGameObject * pOBj, Ray ray)
{
	for (int i = 0; i < sBOXBlock.ABOX.size(); i++)
	{
		BoundingBox obbox = sBOXBlock.ABOX[i];
		if (ray.Hit(obbox) && CCollider::ISBOXHIT(pOBj->GetSphereBox(), obbox)) { return true; }
	}

	return false;
}

bool CMap::AreYouKnockingOnTheOBox(CGameObject * pOBj, Ray ray)
{
	for (int i = 0; i < sBOXBlock.OBOX.size(); i++)
	{
		BoundingOrientedBox obbox = sBOXBlock.OBOX[i];
		if (ray.Hit(obbox) && CCollider::ISBOXHIT(pOBj->GetSphereBox(), obbox)) { return true; }
	}

	return false;
}

void CMap::SetObjectHeight(CGameObject* pOBj,XMFLOAT3 & outPosH,float ErrorValue)
{

	XMFLOAT3 down{ 0.0f,-1.0f,0.0f };
	Ray ray_down(pOBj->GetPosition(), down);
	
	if (ray_down.Hit(Get_OBBOX(16))) State_floor = FLOOR0;
	else if (ray_down.Hit(GetFloorBox(1))) State_floor = FLOOR1;
	else State_floor = NONE2;
	switch (State_floor)
	{
	case NONE2:
		outPosH.y = 0.0f;
		break;
	case FLOOR0:
	{
		XMFLOAT3 p1 = { 0.0f,0.0f,-32.0f };
		XMFLOAT3 p2 = { 0.0f,0.0f,pOBj->GetPosition().z };
		float distans = Tool::Distance_float(p1, p2);
		float H = tanf(XMConvertToRadians(35.0f))*distans;
		float Height = H - ErrorValue;
		if (Height >= 26.0f) Height = 26.0f;
		outPosH.y = Height;
	}
		break;
	case FLOOR1:
		outPosH.y = 26.0f;
		break;
	}
}

void CMap::SetObjectHeight(XMFLOAT3 RayPos, XMFLOAT3 & outPosH, float ErrorValue)
{
	XMFLOAT3 down{ 0.0f,-1.0f,0.0f };
	Ray ray_down(RayPos, down);

	if (ray_down.Hit(Get_OBBOX(16))) State_floor = FLOOR0;
	else if (ray_down.Hit(GetFloorBox(1))) State_floor = FLOOR1;
	else State_floor = NONE2;
	switch (State_floor)
	{
	case NONE2:
		outPosH.y = 0.0f;
		break;
	case FLOOR0:
	{
		XMFLOAT3 p1 = { 0.0f,0.0f,-32.0f };
		XMFLOAT3 p2 = { 0.0f,0.0f,RayPos.z };
		float distans = Tool::Distance_float(p1, p2);
		float H = tanf(XMConvertToRadians(35.0f))*distans;
		float Height = H - ErrorValue;
		if (Height >= 26.0f) Height = 26.0f;
		outPosH.y = Height;
	}
	break;
	case FLOOR1:
		outPosH.y = 26.0f;
		break;
	}
}

void CMap::AIAction(int ZombieType,float dt)
{
	CP0*pp = CManager::GetScene()->GetGmeobjs<CP0>(4);

	//Astarxun lu 
	switch (ZombieType)
	{
	case 0:
		{
		for (int i = 0; i < ENEMY_SIZE; i++)
		{
			CZombie_man* pMan = CManager::GetScene()->GetGmeobj<CZombie_man>(ENEMY_ID, i);
			if (pMan != nullptr)
			{
				ZOMBIEDATE* sdate = pMan->GetStrutForData();
				AStarPathFinding* pS = pMan->GetPointForAstar();

				//
				//pS->RestMapForWalls(Map, BodyWallMapPos);
				//
				if (sdate->iswall&&!sdate->AnimationShow)
				{

					if (!sdate->isFindPath)
					{
						pS->PathReset();
						pS->SetbeginPos({ pMan->GetPosition().x,	pMan->GetPosition().z });
						pS->SetTargetPos({ pp->GetPosition().x, pp->GetPosition().z });
						//pS->RestMapForwall();
						pS->SetStartNode();
						sdate->isFindPath = true;
					}


					XMFLOAT3 pos = pMan->GetPosition();
					XMVECTOR Dir = XMVector3Normalize(XMLoadFloat3(&pos));
					XMVECTOR Oldface = { 0.0f,0.0f,-1.0f,0.0f };
					XMVECTOR Nowface = XMVector3TransformNormal(Oldface, pMan->GetMatrixForWorld());

					pS->Update();

					float blendtimer;
					float DegControl;
					sdate->HP > 20.0f ? pS->Move(pos, dt, Dir, blendtimer, DegControl, ENEMYSP_WALK, sdate->iswall, Nowface) : pS->Move(pos, dt, Dir, blendtimer, DegControl, ENEMYSP_RUN, sdate->iswall, Nowface);
					float Deg = XMVectorGetY(XMVector3AngleBetweenVectors(Nowface, Dir));
					(DegControl < 0.0f) ? pMan->SetMyRotY(Tool::KeepDecimal2(-Deg * blendtimer, 2)) : pMan->SetMyRotY(Tool::KeepDecimal2(Deg * blendtimer, 2));
					SetObjectHeight(pMan, pos, 2.0f);
					pMan->SetPosition(pos);

				}
				else
				{
					pS->RestIsfindpath();
					pS->VPathClear();
				}

			}
		}
		}
		break;
	}

}

void CMap::SetUpMap(SBOX sbox)
{
	XMFLOAT3 m_Vertex[ab*ab];
	for (int z = 0; z < ab; z++)
	{
		for (int x = 0; x < ab; x++)
		{
			XMMATRIX world;
			world = XMMatrixScaling(12.0f, 12.0f, 12.0f);//拡大
			m_Vertex[z * ab + x].x = x - ab / 2.0f;
			m_Vertex[z * ab + x].z = -z + ab / 2.0f;
			m_Vertex[z * ab + x].y = 0.0f/*sinf( x * 0.1f ) * sinf(z * 0.1f) * 2.0f*/;
			XMVECTOR m_VerXM = XMVector3TransformCoord(XMLoadFloat3(&m_Vertex[z * ab + x]), world);
			XMStoreFloat3(&m_Vertex[z * ab + x], m_VerXM);
		}
	}
	//
	unsigned short index[(ab - 1)*(ab - 1) * 6];
	int count = 0;
	for (int o = 0; o < (ab - 1); o++)
	{
		for (int i = 0; i < (ab - 1); i++)
		{
			index[count] = (o*((ab - 1) + 1)) + i;
			//fang ru jin dian 
			Map[o][i].jinD = m_Vertex[index[count]];
			count++;
			index[count] = (o*((ab - 1) + 1)) + (i + 1);
			count++;
			index[count] = ((o + 1)*((ab - 1) + 1)) + i;
			count++;
			index[count] = (o*((ab - 1) + 1)) + (i + 1);
			count++;
			index[count] = ((o + 1)*((ab - 1) + 1)) + i;
			count++;
			index[count] = ((o + 1)*((ab - 1) + 1)) + (i + 1);
			//fang ru yuan dian 
			Map[o][i].YuanD = m_Vertex[index[count]];
			count++;
			Map[o][i].iswark = false;
			Map[o][i].val = 1;
			float d = 6.0f;
			Map[o][i].Center = { (Map[o][i].jinD.x + d),0,(Map[o][i].jinD.z >= 0) ? (Map[o][i].jinD.z + d) : (Map[o][i].jinD.z - d) };
			if (Map[o][i].Center.z <= 0.0f)
			{

				BoundingSphere _s;
				_s.Center = Map[o][i].Center;
				_s.Radius = 1.5f;

				for (int ii = 0; ii < sbox.ABOX.size(); ii++)
				{
					BoundingBox _box = sbox.ABOX[ii];
					if (_box.Contains(XMLoadFloat3(&Map[o][i].Center)))
						Map[o][i].val = 0;
				}
				for (int oo = 0; oo < sbox.OBOX.size(); oo++)
				{

					BoundingOrientedBox _box = sbox.OBOX[oo];
					if (_box.Contains(_s))
						Map[o][i].val = 1;
				}
				for (int oo = 0; oo < sbox.BlockABOX.size(); oo++)
				{

					BoundingBox _box = sbox.BlockABOX[oo];
					if (_box.Contains(_s))
						Map[o][i].val = 1;
				}

			}
			else
			{
				XMFLOAT3 pos = { Map[o][i].Center.x,0.0f,Map[o][i].Center.z - 10.0f };
				BoundingSphere _s;
				_s.Center = pos;
				_s.Radius = 1.5f;

				for (int ii = 0; ii < sbox.ABOX.size(); ii++)
				{
					BoundingBox _box = sbox.ABOX[ii];
					if (_box.Contains(XMLoadFloat3(&pos)))
						Map[o][i].val = 0;
				}


				for (int oo = 0; oo < sbox.OBOX.size(); oo++)
				{

					BoundingOrientedBox _box = sbox.OBOX[oo];
					if (_box.Contains(_s))
						Map[o][i].val = 1;
				}
				for (int oo = 0; oo < sbox.BlockABOX.size(); oo++)
				{

					BoundingBox _box = sbox.BlockABOX[oo];
					if (_box.Contains(_s))
						Map[o][i].val = 1;
				}

			}

		}
	}
	//
	for (int i = 48; i < 52; i++)
	{
		Map[56][i].val = 0.0f;
	}
}

