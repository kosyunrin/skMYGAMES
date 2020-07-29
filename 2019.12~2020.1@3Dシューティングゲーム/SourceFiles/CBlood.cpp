#include"B_header.h"


CBlood::CBlood()
{
	pModle = new CSkinnedfbxanim(BloodDate, BLOOD_SIZE);
	pModle->SetInitanimation(0);
	madeb = true;
	timer = new Timer();
	timer->Reset();
}


CBlood::~CBlood()
{
}

void CBlood::Init()
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(XMConvertToRadians(-90.0f), 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.012f, 0.012f, 0.012f);
}

void CBlood::Uninit()
{
	delete pModle;
	delete timer;
}

void CBlood::Update(float dt)
{

	timer->Tick();
	
	if (timer->TotalTime() < Tool::Random(0.3f,1.0f))
	{
		m_Position.y -= dt*20.0f;
	}
	else SetDestroy();
	
	pModle->Update(dt, 4.0f);

}

void CBlood::Draw()
{
	//if (madeb) return;
	XMMATRIX rotationX =
		XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);//转矩阵全部
	XMFLOAT4X4 world1[INSTANCEMAX];

	XMMATRIX w0;
	w0 = XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(180.0f), 0.0f);
	w0 *= XMMatrixScaling(0.0025f, 0.0025f, 0.0025f);
	w0 *= XMMatrixTranslation(23.0f, 1.0f, 8.0f);
	w0 *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMStoreFloat4x4(&world1[0], w0);

	XMMATRIX w1;
	w1 = XMMatrixRotationRollPitchYaw(XMConvertToRadians(-90.0f),0.0f, 0.0f);
	w1 *= XMMatrixScaling(0.012f, 0.012f, 0.012f);
	w1 *= XMMatrixTranslation(-110.0f, 41.0f, 13.0f);
	w1 *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMStoreFloat4x4(&world1[1], w1);

	XMMATRIX w2;
	w2 = XMMatrixRotationRollPitchYaw(XMConvertToRadians(90.0f), 0.0f, 0.0f);
	w2 *= XMMatrixScaling(0.012f, 0.012f, 0.012f);
	w2 *= XMMatrixTranslation(-111.0f, -41.0f, 21.0f);
	w2 *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMStoreFloat4x4(&world1[2], w2);

	XMMATRIX w3;
	w3 = XMMatrixRotationRollPitchYaw(XMConvertToRadians(-45.0f), 0.0f, 0.0f);
	w3 *= XMMatrixScaling(0.012f, 0.012f, 0.012f);
	w3 *= XMMatrixTranslation(-111.0f, 32.4, 45.0f);
	w3 *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMStoreFloat4x4(&world1[3], w3);

	XMMATRIX w4;
	w4 = XMMatrixRotationRollPitchYaw(XMConvertToRadians(45.0f), 0.0f, 0.0f);
	w4 *= XMMatrixScaling(0.012f, 0.012f, 0.012f);
	w4 *= XMMatrixTranslation(-111.0f, -27.0f, 49.0f);
	w4 *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMStoreFloat4x4(&world1[4], w4);
	pModle->RenderInstance(world1, 0);
}


