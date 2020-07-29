#include"B_header.h"





CEnemy::CEnemy()
{
	pModle = new CSkinnedfbxanim(ZombieDate, ZOMBIE_SIZE);
	pModle->SetInitanimation(0);
}

CEnemy::~CEnemy()
{
}

void CEnemy::Init()
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 15.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.1f, 0.1f, 0.1f);
	sDate.Currentanim = 0;
	sDate.HP = 50;

	XMVECTOR Vmax = XMLoadFloat3(&pModle->m_GetBoxPinots()[0].m_BoxPoint.Vmax);
	XMVECTOR Vmin = XMLoadFloat3(&pModle->m_GetBoxPinots()[0].m_BoxPoint.Vmin);
	XMFLOAT3 vmax;
	XMFLOAT3 vmin;
	XMFLOAT3 v3[8];
	XMStoreFloat3(&vmax, Vmax);
	XMStoreFloat3(&vmin, Vmin);
	CCreate::CreateBox(m_box, vmax, vmin);
	CCreate::CreateV8(m_box, v3);


	m_line = new Line();
	m_line->InitDrawBox(v3);

	//blood演出
	sDate.pBlood = new CPolygon();
	sDate.pBlood->Init2D_tga(7);
}

void CEnemy::Uninit()
{
	delete pModle;
	m_line->Uninit();
	delete m_line;
	sDate.pBlood->UnintTag(7);
	delete sDate.pBlood;
}

void CEnemy::Update(float dt)
{
	switch (sDate.Currentanim)
	{
	case Zombie_run:
		break;
	case Zombie_attack:
		break;
	case Zombie_dead:
		break;
	case Zombie_hurt:
		if (pModle->AiamFramManager(10.0f, Zombie_hurt))
		{
			sDate.Currentanim = Zombie_run;
		}
		break;
	}

	pModle->Update(dt, 1.0f);
}

void CEnemy::Draw()
{
	XMMATRIX rotationX =
		XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);//转矩阵全部
	XMMATRIX world;
	world = rotationX;
	world *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMStoreFloat4x4(&Matrix_World, world);
	pModle->Render(world, sDate.Currentanim);


	XMMATRIX linew;
	linew = world;
	linew *= XMMatrixScaling(1.0f, 0.05f, 1.0f);
	linew *= XMMatrixTranslation(1.0f, 4.0f, 8.0f);
	XMStoreFloat4x4(&Matrix_Box, linew);

	XMMATRIX headBox;
	headBox = world;
	headBox *= XMMatrixScaling(0.099f, 0.099f, 0.099f);
	headBox *= XMMatrixTranslation(0.25f, 3.5f, 14.0f);
	XMStoreFloat4x4(&Matrix_HeadBox, headBox);

	m_line->DrawLineByPlayerWorld(linew);
}

BoundingBox CEnemy::Get_box()
{
	BoundingBox box;
	m_box.Transform(box, XMLoadFloat4x4( &Matrix_Box));
	return box;
}

BoundingBox CEnemy::Get_HeadBox()
{
	BoundingBox box;
	m_box.Transform(box, XMLoadFloat4x4(&Matrix_HeadBox));
	return box;
}

void CEnemy::SetTriangle(XMFLOAT3 * Vpos)
{
	XMVECTOR V[3];
	std::vector<SkinnedMesh*> m_mesh;
	m_mesh = pModle->GetSkinnedMesh();
	for (int index = 0; index < m_mesh.size(); index++)
	{
		SkinnedMesh* mesh = m_mesh[index];
		int count = 0;
		for (UINT g = 0; g < mesh->indices.size()/3; g++)
		{
			DWORD number= mesh->indices[count];
			V[0]= XMVector3TransformCoord
			(XMLoadFloat3(&mesh->vertices[number].Position),XMLoadFloat4x4(& Matrix_World));
			XMStoreFloat3(&Vpos[0], V[0]);
			count++;
			V[1] = XMVector3TransformCoord
			(XMLoadFloat3(&mesh->vertices[number].Position), XMLoadFloat4x4(&Matrix_World));
			XMStoreFloat3(&Vpos[1], V[1]);
			count++;
			V[2] = XMVector3TransformCoord
			(XMLoadFloat3(&mesh->vertices[number].Position), XMLoadFloat4x4(&Matrix_World));
			XMStoreFloat3(&Vpos[2], V[2]);
		}
	}
}
