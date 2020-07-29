#include"B_header.h"



CRedArmy::CRedArmy()
{
	pModle = new CSkinnedfbxanim(XBenemy, XBenemysize);
	pModle->SetInitanimation(0);
	sRdate.pLife = new CPolygon();
	sRdate.pLife->Init3D(0);
}


CRedArmy::~CRedArmy()
{
}

void CRedArmy::Init()
{
	sRdate.currAnim = 0;
	m_Scale = { 0.5f,0.5f,0.5f };
	m_Position = { 0.0f,0.0f,0.0f };
	//boxcreateBegin
	XMFLOAT3 maxPos = { pModle->m_GetBoxPinots()[1].m_BoxPoint.Vmax.x + 1.0f,
	pModle->m_GetBoxPinots()[1].m_BoxPoint.Vmax.y + 5.0f,
	pModle->m_GetBoxPinots()[1].m_BoxPoint.Vmax.z + 1.0f };
	XMFLOAT3 minPos = { pModle->m_GetBoxPinots()[1].m_BoxPoint.Vmin.x - 1.0f,
	pModle->m_GetBoxPinots()[1].m_BoxPoint.Vmin.y ,
	pModle->m_GetBoxPinots()[1].m_BoxPoint.Vmin.z };
	CCreate::CreateBox(sRdate.ABox, maxPos, minPos);
	//CreateBoxEnd
	XMFLOAT3 v3[8];
	CCreate::CreateV8(this->sRdate.ABox, v3);
	pLine = new Line();
	pLine->InitDrawBox(v3);
}

void CRedArmy::Uninit()
{
	pLine->Uninit();
	sRdate.pLife->Uninit3D(0);
	delete sRdate.pLife;
	delete pModle;
	delete pLine;
}

void CRedArmy::Update(float dt)
{
	sRdate.currAnim = 0;

	if (CInput::GetKeyPress('Y'))
	{
		m_Position.z += 1.0f;
	}
	////life=0;
	//if (sRdate.life <= 0)
	//{
	//	//pModle->ResetTimer();
	//	sRdate.currAnim = 1;
	//}
	////gongji 
	//CPlayer* pCplayer = CManager::GetScene()->GetGmeobjs<CPlayer>(_Cplayer);
	//if (pCplayer != nullptr)
	//{
	//	if (pCplayer->GetColliderSphere().Contains(sRdate.ABox) && this->sRdate.life > 0)
	//	{
	//		sRdate.currAnim = 2;
	//	}
	//}
	//switch (sRdate.currAnim)
	//{
	//case 1:
	//	//animshow
	//	if (pModle->AnimShow(65.0f, 1))
	//	{
	//		m_Position.z = 1000.0f;
	//		return;
	//	}
	//case 2:
	//	break;
	//default:
	//	break;
	//}



	sRdate.ABox.Center = m_Position;
	pModle->Update(dt, 1.0f);
}

void CRedArmy::Draw()
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
	pModle->Render(world, sRdate.currAnim);
	pLine->DrawLineByPlayerWorld(world);
	sRdate.pLife->SetWorld(world);
}

BARMYDATE * CRedArmy::GetsRdate()
{
	return &sRdate;
}

BoundingSphere CRedArmy::GetColliderSphere()
{
	BoundingSphere Range; Range.Center = m_Position;
	Range.Radius = EnemyAttackRange-2.0f; return Range;
	return Range;
}
