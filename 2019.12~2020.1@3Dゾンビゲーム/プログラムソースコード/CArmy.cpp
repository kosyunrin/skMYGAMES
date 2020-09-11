#include"B_header.h"



CBlueArmy::CBlueArmy()
{
	pModle = new CSkinnedfbxanim(XBenemy, XBenemysize);
	pModle->SetInitanimation(0);
	sBdate.pLife = new CPolygon();
	sBdate.pLife->Init3D(3);
}


CBlueArmy::~CBlueArmy()
{
}

void CBlueArmy::Init()
{
	sBdate.currAnim = 0;
	m_Scale = { 0.5f,0.5f,0.5f };
	m_Position = { 0.0f,0.0f,0.0f };
	//boxcreateBegin
	XMMATRIX Scalecollider= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	XMFLOAT3 maxPos = { pModle->m_GetBoxPinots()[1].m_BoxPoint.Vmax.x + 1.0f,
	pModle->m_GetBoxPinots()[1].m_BoxPoint.Vmax.y + 5.0f,
	pModle->m_GetBoxPinots()[1].m_BoxPoint.Vmax.z + 1.0f };
	XMFLOAT3 minPos = { pModle->m_GetBoxPinots()[1].m_BoxPoint.Vmin.x - 1.0f,
	pModle->m_GetBoxPinots()[1].m_BoxPoint.Vmin.y ,
	pModle->m_GetBoxPinots()[1].m_BoxPoint.Vmin.z };
	XMVECTOR Vmax = XMVector3TransformCoord(XMLoadFloat3(&maxPos), Scalecollider);
	XMVECTOR Vmin= XMVector3TransformCoord(XMLoadFloat3(&minPos), Scalecollider);
	/*XMStoreFloat3(&maxPos, Vmax);
	XMStoreFloat3(&minPos, Vmin);*/
	CCreate::CreateBox(sBdate.ABox, maxPos,	minPos);
	//CreateBoxEnd
	XMFLOAT3 v3[8];
	CCreate::CreateV8(this->sBdate.ABox, v3);
	pLine = new Line();
	pLine->InitDrawBox(v3);
	
	//initDrawBox
	//setlife
	//UImanager3D* Ui = CManager::GetScene()->GetGmeobjs<UImanager3D>(11);
	//Ui->GetpLifelist().push_back(pLife);sBdate
	sBdate.ABox.Center = m_Position;
}

void CBlueArmy::Uninit()
{
	pLine->Uninit();
	sBdate.pLife->Uninit3D(3);
	delete sBdate.pLife;
	delete pModle;
	delete pLine;
}

void CBlueArmy::Update(float dt)
{
	sBdate.currAnim = XBRun;
	//life=0;
	if (sBdate.life <= 0)
	{
		//pModle->ResetTimer();
		sBdate.currAnim = XBDead;
	}
	//gongji 
	//player
	CPlayer* pCplayer = CManager::GetScene()->GetGmeobjs<CPlayer>(_Cplayer);
	if (pCplayer != nullptr)
	{
		if (pCplayer->GetColliderSphere().Contains(sBdate.ABox)&&this->sBdate.life>0)
		{
			sBdate.currAnim = XBAttack;
		}
	}
	//enemy
	//for ( int i = 0; i < 2; i++)
	//{
	//	CRedArmy* pR = CManager::GetScene()->GetGmeobj<CRedArmy>(6, i);
	//	if (pR != nullptr)
	//	{
	//		if (pR->GetColliderSphere().Contains(sBdate.ABox) && this->sBdate.life > 0)
	//		{
	//			sBdate.currAnim = XBAttack;
	//			TargetID = i;
	//			break;
	//		}
	//	}
	//}
	
	switch (sBdate.currAnim)
	{
	case XBDead:
		//animshow
		if (pModle->AnimShow(65.0f, XBDead))
		{
			pModle->ResetTimer();
			m_Position.z = 1000.0f;
		}
		break;
	case XBAttack:
	{
		//face direction
		//player
		if (pCplayer != nullptr)
		{
			XMVECTOR Dir = XMVector3Normalize(XMLoadFloat3(&pCplayer->GetPosition()) - XMLoadFloat3(&m_Position));
			XMMATRIX rotmatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);//‰ñ“]
			XMVECTOR nowFaceDir = { 0.0f,0.0f,-1.0f };
			float Radian = XMVectorGetY(XMVector3AngleBetweenVectors(nowFaceDir, Dir));
			if (XMVectorGetY(XMVector3Cross(nowFaceDir, Dir)) > 0.0f)
				m_Rotation.y = Radian;
			else
				m_Rotation.y = -Radian;
			if (pModle->AnimShow(20.0f, XBAttack))
			{
				Cbullet* bullet = CManager::GetScene()->AddGameObject<Cbullet>(12);
				XMFLOAT3 bulletPos = { m_Position.x,1.0f,m_Position.z };
				XMVECTOR bulletPosx = XMLoadFloat3(&bulletPos) + Dir * 2.0f;
				XMStoreFloat3(&bulletPos, bulletPosx);
				bullet->LoadTex(L"asset/GameTexture/BlueXBtama.png");
				bullet->SetPosition(bulletPos);
				bullet->SetTarget(Tama_p0);
				bullet->SetenemyID(Tama_p0 + 1);
				bullet->SetScale({ 0.1f,0.1f,0.1f });
				bullet->SetPower(10.0f);
			}
		}
		break;
	}
	//{
	//	CRedArmy* PRed = CManager::GetScene()->GetGmeobj<CRedArmy>(6, TargetID);
	//	if (PRed != nullptr)
	//	{
	//		XMVECTOR Dir = XMVector3Normalize(XMLoadFloat3(&PRed->GetPosition()) - XMLoadFloat3(&m_Position));
	//		XMMATRIX rotmatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);//‰ñ“]
	//		XMVECTOR nowFaceDir = { 0.0f,0.0f,-1.0f };
	//		float Radian = XMVectorGetY(XMVector3AngleBetweenVectors(nowFaceDir, Dir));
	//		if (XMVectorGetY(XMVector3Cross(nowFaceDir, Dir)) > 0.0f)
	//			m_Rotation.y = Radian;
	//		else
	//			m_Rotation.y = -Radian;
	//		if (pModle->AnimShow(20.0f, XBAttack))
	//		{
	//			Cbullet* bullet = CManager::GetScene()->AddGameObject<Cbullet>(12);
	//			XMFLOAT3 bulletPos = { m_Position.x,1.0f,m_Position.z };
	//			XMVECTOR bulletPosx = XMLoadFloat3(&bulletPos) + Dir * 2.0f;
	//			XMStoreFloat3(&bulletPos, bulletPosx);
	//			bullet->LoadTex(L"asset/GameTexture/BlueXBtama.png");
	//			bullet->SetPosition(bulletPos);
	//			bullet->SetTarget(Tama_RedXBfromB);
	//			bullet->SetenemyID(TargetID);
	//			bullet->SetScale({ 0.1f,0.1f,0.1f });
	//			bullet->SetPower(10.0f);
	//		}
	//	}
	//	break;
	//}
	case XBRun:
	{
		/*m_Rotation.y = XMConvertToRadians(90.0f);
		m_Position.x -= dt * 3.0f;*/
		break;
	}
	default:
		break;
	}


	//sBdate.ABox.Center = m_Position;
	pModle->Update(dt, 1.0f);
}

void CBlueArmy::Draw()
{
	CCamera* pCam = CManager::GetScene()->GetGmeobjs<CCamera>(_Camera);
	if (!pCam->Getvisibility(m_Position))
		return;
	XMMATRIX rotationX =
		XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);//×ª¾ØÕóÈ«²¿
	XMMATRIX world;
	world = rotationX;
	world *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	//pModle->Render(world, sBdate.currAnim);
	XMMATRIX boxw;
	boxw= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	worldsssss = world;
	pLine->DrawLineByPlayerWorld(boxw);
	sBdate.pLife->SetWorld(world);
}

BARMYDATE * CBlueArmy::GetsBdate()
{
	return &sBdate;
}

BoundingOrientedBox CBlueArmy::GetOBB(XMFLOAT3 m_rot)
{
	XMMATRIX rot= XMMatrixRotationRollPitchYaw(m_rot.x, m_rot.y, m_rot.z);
	BoundingOrientedBox obb;
	BoundingOrientedBox::CreateFromBoundingBox(obb,sBdate.ABox);
	CCamera* pc = CManager::GetScene()->GetGmeobjs<CCamera>(_Camera);
	XMMATRIX boxw;
	boxw = XMMatrixMultiply(pc->GetViewXM(), pc->GetProjXM());
	obb.Transform(obb, boxw);
	return obb;
}


