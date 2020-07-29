#include"B_header.h"



CBlock::CBlock()
{
	pModle = new CSkinnedfbxanim(BLockDate, BLOCK_SIZE);
	pModle->SetInitanimation(1);
	pSmode = new CStaticmodle("asset/Onepiece/yizhi2.fbx", 0);
}


CBlock::~CBlock()
{
}

void CBlock::Init()
{
	m_Position = XMFLOAT3(2.0f, 0.0f, 500.0f);
	m_Rotation = XMFLOAT3(0.0f, XMConvertToRadians(90.0f), 0.0f);
	m_Scale = XMFLOAT3(0.20f, 0.20f, 0.20f);
}

void CBlock::Uninit()
{
	delete pModle;
	delete pSmode;
}

void CBlock::Update(float dt)
{
	pModle->Update(dt, 1.0f);
}

void CBlock::Draw()
{
	XMMATRIX rotationX =
		XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);//转矩阵全部
	XMFLOAT4X4 world1[INSTANCEMAX];
	
	/*for (int i = 0; i < INSTANCEMAX; i++)
	{
		XMMATRIX world;
		world = rotationX;
		world *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z-i*50.0f);
		XMStoreFloat4x4(&world1[i], world);
	}*/
	XMMATRIX world;
	world = XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(90.0f), 0.0f);
	world *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixTranslation(6.0f, 0.0f, -30.0f);
	XMStoreFloat4x4(&world1[0], world);

	XMMATRIX worlds;
	worlds = XMMatrixRotationRollPitchYaw(XMConvertToRadians(0.0), XMConvertToRadians(-90.0f), 0.0f);
	worlds *= XMMatrixScaling(0.15f, 0.01f, 0.015f);
	//worlds *= XMMatrixScaling(10.0f, 10.0f, 10.0f);
	worlds *= XMMatrixTranslation(-36.0f, 2.5f, 15.0f);
	pSmode->Render(worlds);

	XMMATRIX world11;
	world11 = XMMatrixRotationRollPitchYaw(m_Rotation.x, XMConvertToRadians(45.0f), m_Rotation.z);
	world11 *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world11 *= XMMatrixTranslation(6.0f, 15.0f, -30.0f);
	XMStoreFloat4x4(&world1[1], world11);

	//XMMATRIX world11;
	//world11 = XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(90.0f), 0.0f);
	//world11 *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	//world11 *= XMMatrixTranslation(0.0f, 15.0f, 0.0f);
	//XMStoreFloat4x4(&world1[1], world11);

	XMMATRIX world12;
	world12 = XMMatrixRotationRollPitchYaw(m_Rotation.x, XMConvertToRadians(45.0f), m_Rotation.z);
	world12 *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world12 *= XMMatrixTranslation(-140, 0.0f, 61.0f);
	XMStoreFloat4x4(&world1[2], world12);

	XMMATRIX world13;
	world13 = XMMatrixRotationRollPitchYaw(m_Rotation.x, XMConvertToRadians(45.0f), m_Rotation.z);
	world13 *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world13 *= XMMatrixTranslation(-100.0f, 0.0f, 200.0f);
	XMStoreFloat4x4(&world1[3], world13);

	XMMATRIX world14;
	world14 = XMMatrixRotationRollPitchYaw(m_Rotation.x, XMConvertToRadians(45.0f), m_Rotation.z);
	world14 *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world14 *= XMMatrixTranslation(-100.0f, 0.0f, 180.0f);
	XMStoreFloat4x4(&world1[4], world14);

	XMMATRIX world15;
	world15 = XMMatrixRotationRollPitchYaw(m_Rotation.x, XMConvertToRadians(90.0f), m_Rotation.z);
	world15 *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world15 *= XMMatrixTranslation(-19, 0.0f, 344);
	XMStoreFloat4x4(&world1[5], world15);

	XMMATRIX world16;
	world16 = XMMatrixRotationRollPitchYaw(m_Rotation.x, XMConvertToRadians(45.0f), m_Rotation.z);
	world16 *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world16 *= XMMatrixTranslation(43.0f, 500.0f, 150.0f);
	XMStoreFloat4x4(&world1[6], world16);

	XMMATRIX world17;
	//world17 = XMMatrixRotationRollPitchYaw(m_Rotation.x, XMConvertToRadians(180.0f), m_Rotation.z);
	world17 = XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(90.0f), 0.0f);
	world17 *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(90.0f), 0.0f);
	world17 *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world17 *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	world17 *= XMMatrixTranslation(-140, 0.0f, 81.0f);
	//world17 *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(45.0f), 0.0f);
	XMStoreFloat4x4(&world1[7], world17);

	XMMATRIX world18;
	world18 = XMMatrixRotationRollPitchYaw(m_Rotation.x, XMConvertToRadians(180.0f), m_Rotation.z);
	world18 *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world18 *= XMMatrixTranslation(63.0f, 500.0f, 120.0f);
	XMStoreFloat4x4(&world1[8], world18);

	XMMATRIX world19;
	world19 = XMMatrixRotationRollPitchYaw(m_Rotation.x, XMConvertToRadians(180.0f), m_Rotation.z);
	world19 *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world19 *= XMMatrixTranslation(63.0f, 500.0f, 80.0f);
	XMStoreFloat4x4(&world1[9], world19);
	
	pModle->RenderInstance(world1,1);
}
