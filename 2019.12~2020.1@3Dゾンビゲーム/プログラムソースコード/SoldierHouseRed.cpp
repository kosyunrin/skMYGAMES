#include"B_header.h"
#include"input.h"


float xx2 = 0;
SoldierHouseRed::SoldierHouseRed()
{
}


SoldierHouseRed::~SoldierHouseRed()
{
}

BoundingOrientedBox SoldierHouseRed::GetArmyBox_obb()const
{
	BoundingOrientedBox box;
	BoundingOrientedBox::CreateFromBoundingBox(box, AimryDate.AABBBOX);
	box.Transform(box, XMLoadFloat4x4(&B_worldXMMRIX));
	return box;
}


void SoldierHouseRed::Init()
{
	AimryDate.AABBBOX = BoundingBox();
	m_Position = XMFLOAT3(0.0f, 5.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_quation = XMQuaternionIdentity();
	sss = new StaticModel();
	sss->LoadAny("asset/Onepiece/soldier1.x");
	BoundingBox::CreateFromPoints(AimryDate.AABBBOX, XMLoadFloat3(&sss->m_GetBoxPinots()[0].m_BoxPoint.Vmax),
		XMLoadFloat3(&sss->m_GetBoxPinots()[0].m_BoxPoint.Vmin));
	//l_mode = new SkinnedModel("asset/Onepiece/soldier1.x");
	XMFLOAT3 v3[8];
	this->AimryDate.AABBBOX.GetCorners(v3);
	m_line = new Line();
	m_line->InitDrawBox(v3);
}

void SoldierHouseRed::Uninit()
{
	sss->UnloadAssimp();
	delete sss;
	m_line->Uninit();
	delete m_line;
	
}

void SoldierHouseRed::Update(float dt)
{
//	l_mode->Update();
	 if (CInput::GetKeyPress(VK_LBUTTON))
	 {
		 XMFLOAT3 vz = { 1.0f,0.0f,0.0f };
		 XMVECTOR axis = XMLoadFloat3(&vz);
		 XMVECTOR rotation = XMQuaternionRotationAxis(axis, 0.2f);
		 m_quation = XMQuaternionMultiply(m_quation, rotation);
		 m_quation = XMQuaternionNormalize(m_quation);
	 }
}

void SoldierHouseRed::Draw()
{

	CShader::SetWorldMatrix_Q(m_Scale, m_quation, m_Position,m_line);
	sss->DrawAny();
	//l_mode->Render(world, 0);

}
