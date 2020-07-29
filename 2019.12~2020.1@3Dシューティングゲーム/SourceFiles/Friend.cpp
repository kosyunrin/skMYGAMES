#include"B_header.h"



Friend::Friend()
{
}


Friend::~Friend()
{
}


void Friend::Init()
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.01f, 0.01f, 0.01f);
	//
	//e_Modle = new CSkinnedfbxanim("asset/Onepiece/xbwark.fbx", NQDate, NQsize);
	e_Modle = new CStaticmodle("asset/Onepiece/MOBADX.fbx",0); 
	//e_Modle = new CStaticmodle("asset/Onepiece/xbwark.fbx");
	//setlife
	pLife = new CPolygon();
	pLife->Init3D(3);
	//setbox
	CCreate::CreateBox(sOOU.ABOX, e_Modle->m_GetBoxPinots()[0].m_BoxPoint.Vmax,
		e_Modle->m_GetBoxPinots()[0].m_BoxPoint.Vmin);
	//setline
	m_line = new Line();
	XMFLOAT3 v3[8];
	CCreate::CreateV8(this->sOOU.ABOX, v3);
	m_line->InitDrawBox(v3);

	//xunlu 
	/*Caxin = new CAx();
	Caxin->Init(e_Modle->GetSkinnedMesh());*/
	
}

void Friend::Uninit()
{
	delete e_Modle;
	pLife->Uninit3D(3);
	delete pLife;
	m_line->Uninit();
	delete m_line;
	//delete Caxin;
}

void Friend::Update(float dt)
{
	//Caxin->Update();

	/*if (Caxin->GetenDprint())
	{
		if (Caxin->GetbeginPos().row != Caxin->GetendPos().row ||
			Caxin->GetbeginPos().cow != Caxin->GetendPos().cow)
		{
			int Allsize = Caxin->GetdirectPos1().size();
			for (int i = Allsize-1; i >=0; i--)
			{
				MyDirect smd = Caxin->GetdirectPos1()[i];
				if (Caxin->GetbeginPos().row == smd.Pos.row&&
					Caxin->GetbeginPos().cow == smd.Pos.cow)
				{
					MyDirect smdnext = Caxin->GetdirectPos1()[i-1];
					XMVECTOR dir = XMVector3Normalize( XMLoadFloat3(&smdnext.dire) - XMLoadFloat3(&smd.dire));
					CPlayer* pPlayer = CManager::GetScene()->GetGmeobjs<CPlayer>(_Cplayer);
					if (pPlayer != nullptr)
					{
						XMVECTOR Ppos = XMLoadFloat3(&pPlayer->GetPosition());
						Ppos += dir * dt*1.0f;
						XMFLOAT3 Pposf;
						XMStoreFloat3(&Pposf, Ppos);
						pPlayer->SetPosition(Pposf);
					}
				}
			}
		}
	}*/
	//if (Caxin->GetenDprint())
	//{
	//	int count = 1;
	//	int Allsize = Caxin->GetdirectPos1().size();
	//	CPlayer* pPlayer = CManager::GetScene()->GetGmeobjs<CPlayer>(_Cplayer);
	//	XMFLOAT3 P0Pos = pPlayer->GetPosition();
	//	XMFLOAT3 TotalBeginPos = Caxin->GetdirectPos1()[Allsize-1].dire;
	//	XMFLOAT3 TotalEndPos = Caxin->GetdirectPos1()[0].dire;
	//	float TotalDis_P0toBegin = Tool::Distance_float(P0Pos, TotalBeginPos);
	//	float TotalDis_EndtoBegin= Tool::Distance_float(TotalBeginPos, TotalEndPos);
	//	//CRenderer::Debug_move_Rotation3[0] = TotalDis_P0toBegin;
	//	//CRenderer::Debug_move_Rotation3[1] = TotalDis_EndtoBegin;
	//	if (Caxin->GetbeginPos().row != Caxin->GetendPos().row ||
	//		Caxin->GetbeginPos().cow != Caxin->GetendPos().cow)
	//	{
	//		for (int i = Allsize-1; i >= 0;i--)
	//		{
	//			if (pPlayer != nullptr)
	//			{
	//				//move
	//			if (i == Allsize - count)
	//				{
	//				       XMFLOAT3 BeginPos = Caxin->GetdirectPos1()[i].dire;
	//				       XMFLOAT3 EndPos = Caxin->GetdirectPos1()[i - 1].dire;
	//				       XMVECTOR dir = XMVector3Normalize( XMLoadFloat3(&EndPos) - XMLoadFloat3(&BeginPos));
	//				       float P0_TO_B = Tool::Distance_float(P0Pos, BeginPos);//•Ï‰»
	//				       float END_TO_B = Tool::Distance_float(EndPos, BeginPos);
	//					if (P0_TO_B < END_TO_B)
	//					{
	//						XMVECTOR Ppos = XMLoadFloat3(&P0Pos);
	//						Ppos += dir * dt*8.0f;
	//						XMFLOAT3 Pposf;
	//						XMStoreFloat3(&Pposf, Ppos);
	//						pPlayer->SetPosition(Pposf);
	//					}
	//					else
	//					{
	//						if(count<= Allsize)
	//						count++;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
}

void Friend::Draw()
{
	CCamera* Cam_p = CManager::GetScene()->GetGmeobjs<CCamera>(_Camera);
	/*if (!Cam_p->Getvisibility(m_Position))
		return;*/
	XMMATRIX world;
	world = XMMatrixRotationX(XMConvertToRadians(-90.0f));
	world *= XMMatrixRotationY(XMConvertToRadians(90.0f));
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);//×ª¾ØÕóÈ«²¿
	world *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	//drawlife
	XMFLOAT3 m_lifeRot;
	XMMATRIX worldlife;
	float angle = atan2(m_Position.x - Cam_p->GetPosition().x, m_Position.z - Cam_p->GetPosition().z);
	m_lifeRot = { 0.0f,angle,0.0f };
	worldlife = XMMatrixRotationRollPitchYaw(m_lifeRot.x, m_lifeRot.y, m_lifeRot.z);
	worldlife *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	pLife->DrawPlayerLife(-1.0f, 10.0f, -1.0f, 2.5f, 0.2f, 1.0f, 1.0f, 1.0f, 1.0f, 3, worldlife);


	e_Modle->Render(world);
	//drawline
	//lineworld
	//XMMATRIX lineworld;
	//lineworld= XMMatrixRotationX(XMConvertToRadians(90));
	//lineworld *= world;
	m_line->DrawLineByPlayerWorld(world);
}

void Friend::SetPos(XMFLOAT3 pos)
{
	//Caxin->SetbeginPos(XMFLOAT2(pos.x, pos.z));
}

