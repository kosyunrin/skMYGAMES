#include"B_header.h"
#include"BossStateBase.h"
#include"BossnoMono.h"






CEnemy::CEnemy()
{
	pModle = new CSkinnedfbxanim(ZombieDate, ZOMBIE_SIZE);
	pModle->SetInitanimation(0);
	pBossState = new BossState();
	pAstar = std::make_unique<AStarPathFinding>();
	pWeakness = std::make_unique<Weakness>();
	pWeakness->InitWeapon();
	//pBossState->ChangeState(new FirstShow(),this);
}

CEnemy::~CEnemy()
{
	delete pBossState;
}

void CEnemy::Init()
{
	m_Position = XMFLOAT3(0, -200, 120);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.5f, 0.5f, 0.5f);
	sDate.Currentanim = 0;
	sDate.HP = 100;
	sDate.xHp = 0;
	sDate.StopChangeState = false;

	XMVECTOR Vmax = XMLoadFloat3(&pModle->m_GetBoxPinots()[0].m_BoxPoint.Vmax);
	XMVECTOR Vmin = XMLoadFloat3(&pModle->m_GetBoxPinots()[0].m_BoxPoint.Vmin);
	XMFLOAT3 vmax;
	XMFLOAT3 vmin;
	XMFLOAT3 v3[8];
	XMStoreFloat3(&vmax, Vmax);
	XMStoreFloat3(&vmin, Vmin);
	vmax.x -= 15.0f;
	vmax.z -= 20.0f;
	CCreate::CreateBox(m_box, vmax, vmin);
	CCreate::CreateV8(m_box, v3);


	m_line = new Line();
	m_line->InitDrawBox(v3);

	//blood演出
	sDate.pBlood = new CPolygon();
	sDate.pBlood->Init2D_tga(7);
	sDate.IsHpShow = false;
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
	CP0* p0 = CManager::GetScene()->GetGmeobjs<CP0>(4);

	float dis = Tool::Distance_float(p0->GetPosition(), m_Position);
	CRenderer::Debug_move_v2[1] = dis;
	XMVECTOR faceDir = { 0.0f,0.0f,1.0f,0.0f };
	NowfaceDir = XMVector3TransformNormal(faceDir, this->GetMatrixForWorld());
	if (CInput::GetKeyPress('U'))
	{
		//pBossState->ChangeState(new FirstShow(), this);
		
		for (int i = 0; i < ENEMY_SIZE; i++)
		{
			CZombie_man* pman = CManager::GetScene()->GetGmeobj<CZombie_man>(ENEMY_ID, i);
			if (pman != nullptr)
			{
				pman->GetStrutForData()->HP = 0;
			}
		}
	}
	
	

	pBossState->UpdateState(this,dt);

	/*switch (sDate.Currentanim)
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
	}*/

	//pModle->Update(dt, 1.0f);
	if (sDate.IsHpShow)
	{
		sDate.HpShowTimer += dt * 1.0f;
		if (sDate.HpShowTimer > 4.0f)
		{
			sDate.IsHpShow = false;
		}
	}
}

void CEnemy::Draw()
{
	XMMATRIX rotationX =
		XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);//转矩阵全部
	XMMATRIX world;
	world = rotationX;
	world *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMStoreFloat4x4(&m_WorldMatirx, world);
	XMStoreFloat4x4(&Matrix_World, XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z));
	//pModle->Render(world, sDate.Currentanim);
	pModle->WeaponRender(world, sDate.Currentanim);



	XMMATRIX linew;
	linew = world;
	linew *= XMMatrixScaling(1, 0.25f, 1.0f);
	linew *= XMMatrixTranslation(1.0f, 4.0f , 8.0f );
	XMStoreFloat4x4(&Matrix_Box, linew);

	XMMATRIX headBox;
	headBox = world;
	headBox *= XMMatrixScaling(0.099f, 0.099f, 0.099f);
	headBox *= XMMatrixTranslation(0.25f, 3.5f, 14.0f);
	XMStoreFloat4x4(&Matrix_HeadBox, headBox);

	//m_line->DrawLineByPlayerWorld(linew);

	pWeakness->Update(world, pModle);

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

BoundingSphere CEnemy::Get_Sphere()
{
	return pWeakness->GetEyESphereBox();
}

BoundingSphere CEnemy::GetEyeSphereBox()
{
	return pWeakness->GetEyESphereBox();
}

BoundingBox CEnemy::GetBodySphereBox()
{
	return pWeakness->GetBodySphereBox();
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

void CEnemy::MoveRot()
{
	pBossState->ChangeState(new MoveRotx(), this);
}


void CEnemy::Move()
{
	pBossState->ChangeState(new Movex(), this);
}

void CEnemy::MoveAstar()
{
	pBossState->ChangeState(new MoveAstarx(), this);
}

void CEnemy::MoveAstarRot()
{
	pBossState->ChangeState(new MoveAstarRotx(), this);
}

void CEnemy::MoveAstarPatrol()
{
	pBossState->ChangeState(new MovePatrol(), this);
}

void CEnemy::MoveBackx()
{
	pBossState->ChangeState(new MoveBackx2(), this);
}
void CEnemy::MoveAttackx()
{
	pBossState->ChangeState(new MoveTargetAttack(), this);
}
void CEnemy::MoveHurtx()
{
	pBossState->ChangeState(new MoveHurt(), this);
}
void CEnemy::MoveWeaknessx()
{
	pBossState->ChangeState(new MoveWeakness(), this);
}
void CEnemy::MoveStandupx()
{
	pBossState->ChangeState(new MoveStandup(), this);
}
void CEnemy::MoveFirstx()
{
	pBossState->ChangeState(new FirstShow(), this);
}
XMFLOAT3 CEnemy::GetpWeakPos()
{
	return pWeakness->GetEyEPos();
}
template<int T>
void CEnemy::MoveRotFreeActionx()
{
	pBossState->ChangeState(new MoveRotFreeAction<T>(), this);
}

