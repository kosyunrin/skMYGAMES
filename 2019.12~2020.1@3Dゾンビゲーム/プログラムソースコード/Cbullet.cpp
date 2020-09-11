#include"B_header.h"
#include"Timer.h"



Cbullet::Cbullet()
{
}

Cbullet::~Cbullet()
{
}
void Cbullet::Init()
{
	
	//m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.3f, 0.3f, 0.3f);
	ptimer = new Timer();
	ptimer->Reset();
	Qidian = m_Position;
	EnemyID = -1;
	dist = 1000.0f;
}

void Cbullet::Uninit()
{
	//if (pBullet != nullptr)
	{
		pBullet->Uninit();
		delete pBullet;
	}
	delete ptimer;
}

void Cbullet::Update(float dt)
{
	//zhidanMOveBegin
	XMVECTOR bullPos;
	bullPos = XMLoadFloat3(&m_Position);
	ptimer->Tick();
	
	if (EnemyID <= 0)
	{
		if (ptimer->TotalTime() >= 1.0f)
		{
			SetDestroy();
		}
		//CRenderer::Debug_move_v2[0] = ptimer->TotalTime();

		m_Front = XMVector3Normalize(m_Front);

		XMMATRIX rotmatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);//回転
		XMVECTOR nowFaceDir = { 1.0f,0.0f,0.0f };
		nowFaceDir = XMVector3TransformNormal(nowFaceDir, rotmatrix);
		float Radian = XMVectorGetY(XMVector3AngleBetweenVectors(nowFaceDir, m_Front));
		if (XMVectorGetY(XMVector3Cross(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), m_Front)) > 0.0f)
			m_Rotation.y += Radian;
		else
			m_Rotation.y -= Radian;
		bullPos += m_Front * dt*10.0f;
	}
	else
	{
		//zidan fangxiang
		XMVECTOR Dir = {0.0f,0.0f,0.0f,0.0f};
			switch (target)
			{
			case Tama_BlueXB:
			{
				CBlueArmy* PBarmy = CManager::GetScene()->GetGmeobj<CBlueArmy>(5, EnemyID);
				if (PBarmy != nullptr)
				{
					Dir = XMVector3Normalize(XMLoadFloat3(&PBarmy->GetPosition()) - bullPos);
					XMMATRIX rotmatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);//回転
					XMVECTOR nowFaceDir = { 1.0f,0.0f,0.0f };
					//nowFaceDir = XMVector3TransformNormal(nowFaceDir, rotmatrix);
					float Radian = XMVectorGetY(XMVector3AngleBetweenVectors(nowFaceDir, Dir));
					if (XMVectorGetY(XMVector3Cross(nowFaceDir, Dir)) > 0.0f)
						m_Rotation.y = Radian;
					else
						m_Rotation.y = -Radian;
					//collider
					BARMYDATE *sBadte = PBarmy->GetsBdate();
					BoundingSphere m_collider;
					m_collider.Center = m_Position;
					m_collider.Radius = 0.5f;
					BoundingOrientedBox E_collider;
					BoundingOrientedBox::CreateFromBoundingBox(E_collider, sBadte->ABox);
					if (E_collider.Intersects(m_collider))
					{
						sBadte->life -= Power;
						SetDestroy();
					}
				}
				bullPos += Dir * dt*p0TAMA_SPEED;
				break;
			}
			case Tama_p0:
			{
				CPlayer* pPlyaer = CManager::GetScene()->GetGmeobjs<CPlayer>(_Cplayer);
				if (pPlyaer != nullptr)
				{
					Dir = XMVector3Normalize(XMLoadFloat3(&pPlyaer->GetPosition()) - bullPos);

					//collider
					LPlayerOneDate *pP0 = pPlyaer->GetP0Date();
					BoundingSphere m_collider;
					m_collider.Center = m_Position;
					m_collider.Radius = 0.01f;
					BoundingOrientedBox E_collider;
					BoundingOrientedBox::CreateFromBoundingBox(E_collider, pP0->AABBBOX);
					if (E_collider.Intersects(m_collider))
					{
						pP0->life -= Power;
						SetDestroy();
					}
				}
				bullPos += Dir * dt*XBTAMA_SPEED;
				break;
			}
			case Tama_RedXBfromB:
			{
				//for (int i = 0; i < 2; i++)
				//{
				//	CRedArmy* pRed = CManager::GetScene()->GetGmeobj<CRedArmy>(6, i);
				//	XMFLOAT3 pRpos = pRed->GetPosition();
				//	float _dist = Tool::Distance(userPos, pRpos);
				//	if (_dist < dist)
				//	{
				//		dist = _dist;
				//		EnemyID = i;
				//	}
				//}
				//CRedArmy* pRedGo = CManager::GetScene()->GetGmeobj<CRedArmy>(6, EnemyID);
				//if (pRedGo != nullptr)
				//{
				//	Dir = XMVector3Normalize(XMLoadFloat3(&pRedGo->GetPosition()) - bullPos);
				//	
				//	//rot user
				//	CBlueArmy* pBDate = pUserDate.pB;
				//	XMVECTOR RotDir= XMVector3Normalize(XMLoadFloat3(&pRedGo->GetPosition()) - XMLoadFloat3( &pBDate->GetPosition()));
				//	XMVECTOR nowFaceDir = { 0.0f,0.0f,-1.0f };
				//	float Radian = XMVectorGetY(XMVector3AngleBetweenVectors(nowFaceDir, RotDir));
				//	if (XMVectorGetY(XMVector3Cross(nowFaceDir, RotDir)) > 0.0f)
				//		pBDate->SetRotation({ 0.0f,Radian ,0.0f });
				//	else
				//		pBDate->SetRotation({ 0.0f,-Radian ,0.0f });

				//	//collider
				//	BARMYDATE *pReds = pRedGo->GetsRdate();
				//	BoundingSphere m_collider;
				//	m_collider.Center = m_Position;
				//	m_collider.Radius = 0.01f;
				//	BoundingOrientedBox E_collider;
				//	BoundingOrientedBox::CreateFromBoundingBox(E_collider, pReds->ABox);
				//	if (E_collider.Intersects(m_collider))
				//	{
				//		pReds->life -= 10.0f;
				//		SetDestroy();
				//	}
				//}
				CRedArmy* PBarmy = CManager::GetScene()->GetGmeobj<CRedArmy>(6, EnemyID);
				if (PBarmy != nullptr)
				{
					Dir = XMVector3Normalize(XMLoadFloat3(&PBarmy->GetPosition()) - bullPos);
					//collider
					BARMYDATE *sBadte = PBarmy->GetsRdate();
					BoundingSphere m_collider;
					m_collider.Center = m_Position;
					m_collider.Radius = 0.01f;
					BoundingOrientedBox E_collider;
					BoundingOrientedBox::CreateFromBoundingBox(E_collider, sBadte->ABox);
					if (E_collider.Intersects(m_collider))
					{
						sBadte->life -= Power;
						SetDestroy();
					}
				}

				bullPos += Dir * dt*XBTAMA_SPEED;
			break;
			}
			case Tama_BlueXBfromR:
			{
				break;
			}
			case Tama_BlueHouse:
			{
				SoldierHouseBlue* pBhouse = CManager::GetScene()->GetGmeobjs<SoldierHouseBlue>(7);
				if (pBhouse != nullptr)
				{
					Dir = XMVector3Normalize(XMLoadFloat3(&pBhouse->GetPosition()) - bullPos);
					XMVECTOR nowFaceDir = { 1.0f,0.0f,0.0f };
					float Radian = XMVectorGetY(XMVector3AngleBetweenVectors(nowFaceDir, Dir));
					if (XMVectorGetY(XMVector3Cross(nowFaceDir, Dir)) > 0.0f)
						m_Rotation.y = Radian;
					else
						m_Rotation.y = -Radian;
					//collider
					House *phouse = pBhouse->GetDate_house();
					BoundingSphere m_collider;
					m_collider.Center = m_Position;
					m_collider.Radius = 0.5f;
					BoundingOrientedBox E_collider;
					BoundingOrientedBox::CreateFromBoundingBox(E_collider, phouse->ABOX);
					if (E_collider.Intersects(m_collider))
					{
						phouse->HP -= Power;
						SetDestroy();
					}
				}
				bullPos += Dir * dt*p0TAMA_SPEED;
				break;
			}
			}
	}
	XMStoreFloat3(&m_Position, bullPos);

	//collider
	/*switch (target)
	{
	case Tama_BlueXB:
		for (int i = 0; i < 2; i++)
		{
			CBlueArmy* pBarmy = CManager::GetScene()->GetGmeobj<CBlueArmy>(5, i);
			if (pBarmy != nullptr)
			{
				BARMYDATE *sBadte = pBarmy->GetsBdate();
				BoundingSphere m_collider;
				m_collider.Center = m_Position;
				m_collider.Radius = 0.01f;
				BoundingOrientedBox E_collider;
				BoundingOrientedBox::CreateFromBoundingBox(E_collider, sBadte->ABox);
				if (E_collider.Intersects(m_collider))
				{
					sBadte->life -= 50.0f;
					SetDestroy();
				}
			}
		}

		break;
	}*/
	

}

void Cbullet::Draw()
{
	XMMATRIX world;
	//world = XMMatrixRotationY(XMConvertToRadians(90.0f));
	world = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);//回転
	world *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);//拡大
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);//移動
	if(pBullet!=nullptr)
	pBullet->Draw3DTex(world);
}

void Cbullet::LoadTex(const wchar_t * path)
{
	pBullet = new CPolygon();
	pBullet->Ini3DTex(path);
}




