#pragma once
#include "main.h"
class BossStateBase
{
public:
	BossStateBase();
	~BossStateBase();
	virtual void Enter(CEnemy* pE) {}
	virtual void Out(CEnemy* pE) { }
	virtual void UpdateSate(CEnemy* pE, float dt) 
	{
		CP0* p0 = CManager::GetScene()->GetGmeobjs<CP0>(4);
		float dis = Tool::Distance_float(p0->GetPosition(), pE->GetPosition());
		CRenderer::Debug_move_Rotation2[0] = dis;
		if(dis<100)
		{
			pE->MoveRotFreeActionx<MoveAttack>();
		}
	}
	void UpdaSatePatrolOnly(CEnemy* pE, float dt)
	{
		CP0* p0 = CManager::GetScene()->GetGmeobjs<CP0>(4);
		float dis = Tool::Distance_float(p0->GetPosition(), pE->GetPosition());
		CRenderer::Debug_move_Rotation2[0] = dis;
		if (dis < 80)
		{
			pE->MoveRotFreeActionx<MoveAttack>();
		}
	}
private:

};

class BossState
{
public:
	BossState();
	~BossState();
	void UpdateState(CEnemy* pE, float dt) { if(pCurrentState)	pCurrentState->UpdateSate(pE,dt); }
	void ChangeState(BossStateBase* pState, CEnemy* pE)
	{
		if (pCurrentState)
		{
			pCurrentState->Out(pE);
			delete pCurrentState;
		}
		pCurrentState = pState;
		pCurrentState->Enter(pE);
	}
	bool IsHpShow() { return &mIsHpShow; }

private:
	BossStateBase* pCurrentState = nullptr;
	bool mIsHpShow=false;

};

BossState::BossState()
{
	//BossStateBase* pF = new FirstShow();
	//pCurrentState = pF;
	//pCurrentState->Enter(CEnemy* pE);
}

BossState::~BossState()
{
	delete pCurrentState;
}

BossStateBase::BossStateBase()
{
}

BossStateBase::~BossStateBase()
{
}

class  FirstShow:public BossStateBase
{
public:
	void Enter(CEnemy* pE)override 
	{	
		pE->SetPosition(XMFLOAT3(0, -20, 120));
		blend = 0;
		pE->Get_Date()->Currentanim = Zombie_attack;
	}
	 void Out(CEnemy* pE)override 
	 {

	 }
	 void UpdateSate(CEnemy* pE,float dt)override 
	 {
		 //if (CInput::GetKeyPress('U'))
		 {
			 Tool::BlendRunUp(blend, dt, 0.2f);
			 pE->SetPosition(XMFLOAT3(0, blend * 20 - 20, 120));
		 }
		 if (blend == 1)
		 {
			 pE->MoveAstarPatrol();
			 UImanager3D* pui = CManager::GetScene()->GetGmeobjs<UImanager3D>(UI_ID);
			 pui->RestScene();
		 }
		 pE->GetpAnim()->Update(dt, 0.1f);
	 }

private:
	float blend;

};
class  FindTarget:public BossStateBase
{
public:
	 void Enter(CEnemy* pE)override {}
	 void Out(CEnemy* pE)override {}
	 void UpdateSate(CEnemy* pE,float dt)override {}

private:

};

class  JumpAttackTarget :public BossStateBase
{
public:
	void Enter(CEnemy* pE)override {}
	void Out(CEnemy* pE)override {}
	void UpdateSate(CEnemy* pE,float dt)override {}

private:

};
class  MoveStandup : public BossStateBase
{
public:
	void Enter(CEnemy* pE)override { pE->Get_Date()->Currentanim = Zombie_run; }
	void Out(CEnemy* pE)override {}
	void UpdateSate(CEnemy* pE, float dt)override 
	{
		if (pE->GetpAnim()->AiamFramManager(15.0f, Zombie_run))
		{
			pE->MoveAstarPatrol();
		}

		pE->GetpAnim()->Update(dt, 0.3f);
	}

private:

};
class  MoveWeakness :public BossStateBase
{
public:
	void Enter(CEnemy* pE)override { pE->Get_Date()->Currentanim = Zombie_dead; 
	timer = 0;
	speed = 1.0f;
	pE->Get_Date()->StopChangeState = true;
	}
	void Out(CEnemy* pE)override 
	{
		pE->Get_Date()->StopChangeState = false;
	}
	void UpdateSate(CEnemy* pE, float dt)override 
	{
		timer += dt;
		if (timer > 1.0f) speed = 0;

		if (timer > 10.0f)
		{
			//pE->MoveStandupx();
			speed = 0.5f;
			pE->Get_Date()->Currentanim = Zombie_run;
			if (timer > 13.0f) pE->MoveAstarPatrol();
		}
		pE->GetpAnim()->Update(dt, speed);
	}

private:
	float timer;
	float speed;


};
class  MoveHurt :public BossStateBase
{
public:
	void Enter(CEnemy* pE)override { 
		pE->Get_Date()->Currentanim = Zombie_hurt;
		
		if (pE->Get_Date()->xHp >= 20)
		{
			pE->Get_Date()->xHp = 0;
			pE->MoveWeaknessx();
		}
	
	

		

	}
	void Out(CEnemy* pE)override {}
	void UpdateSate(CEnemy* pE, float dt)override 
	{
		if (pE->GetpAnim()->AiamFramManager(10.0f, Zombie_hurt))
		{
			pE->MoveRotFreeActionx<MoveAttack>();
		}

		pE->GetpAnim()->Update(dt, 0.5f);
	}

private:

};
class  MoveBackx2 :public BossStateBase
{
public:
	void Enter(CEnemy* pE)override {
		pE->Get_Date()->Currentanim = Zombie_run;
		StartPos = pE->GetPosition();
		Speed = 0;
	}
	void Out(CEnemy* pE)override {}
	void UpdateSate(CEnemy* pE, float dt)override 
	{
		XMFLOAT3 TargetPos = { 0,0,160 };
		XMFLOAT3 pos = pE->GetPosition();
		Speed += dt * 25;
		int t = 0;
		pos = Tool::Vec3LerpSmooth(StartPos, TargetPos, Speed, t);
		if (t == 1)
		{
			pE->MoveAstarPatrol();
		}




		pE->SetPosition(pos);
		pE->GetpAnim()->Update(dt, 1.0f);
	}

private:
	XMFLOAT3 StartPos;
	float Speed;

};
class  MoveTargetAttack : public BossStateBase
{
public:
	void Enter(CEnemy* pE)override { pE->Get_Date()->Currentanim = Zombie_attack; }
	void Out(CEnemy* pE)override {}
	void UpdateSate(CEnemy* pE,float dt)override 
	{
		CP0* p0 = CManager::GetScene()->GetGmeobjs<CP0>(4);
		float dis = Tool::Distance_float(pE->GetPosition(), p0->GetPosition());
		if (pE->GetpAnim()->AiamFramManager(50.0f, Zombie_attack))
		{
			pE->MoveAstarPatrol();
		}
		if (pE->GetpAnim()->AiamFramManager(20, Zombie_attack))
		{
			if (dis < 50.0f)
			{
				//p0->GetP0Dataptr()->HP > 0 ? p0->GetP0Dataptr()->HP -= 0.003f : p0->GetP0Dataptr()->HP = 0;
			}
		}
		if (pE->GetpAnim()->AiamFramManager(40, Zombie_attack))
		{
			//if (dis < 50.0f)p0->GetP0Dataptr()->HP > 0 ? p0->GetP0Dataptr()->HP -= 0.003f : p0->GetP0Dataptr()->HP = 0;
		}
		

		pE->GetpAnim()->Update(dt, 0.8f);
	}

private:

};
class  MoveAstarx : public BossStateBase
{
public:
	void Enter(CEnemy* pE)override { moveblend = 0; }
	void Out(CEnemy* pE)override {}
	void UpdateSate(CEnemy* pE, float dt)override 
	{
		BossStateBase::UpdateSate(pE, dt);
		bool StopMove = false;
		bool Again = false;
		AStarPathFinding* pS = pE->GetPointForAstar();
		//float speed = 0.1f;
		//Tool::BlendRunUp(moveblend, dt, speed);
		moveblend += dt * 25.0f;
		XMFLOAT3 epos = pE->GetPosition();
		pS->UPdateObject(epos, StopMove, Again, moveblend);
		pE->SetPosition(epos);
		if (StopMove)
		{
			pE->MoveAstarRot();
		}
		if (Again)
		{
			pE->MoveAstarPatrol();
		}
		
		pE->GetpAnim()->Update(dt, 1.0f);

	}

private:
	float moveblend;

};
 class  MovePatrol : public BossStateBase
{
public:
	void Enter(CEnemy* pE)override 
	{
		time = 0;
		pE->Get_Date()->Currentanim = Zombie_hurt;
		XMFLOAT2 xP[5] = { XMFLOAT2(-90,15),XMFLOAT2(-100,150),XMFLOAT2(110,170),XMFLOAT2(100,0),XMFLOAT2(0,300) };
		for (int i = 0; i < 5; i++)
		{
			PatrolPos[i] = xP[i];
		}
		AStarPathFinding* pS = pE->GetPointForAstar();
		pS->PathReset();
		pS->SetbeginPos({ pE->GetPosition().x,	pE->GetPosition().z });
		int num;
		num = Tool::RandomInt(0, 5);
		pS->SetTargetPos(PatrolPos[num]);
		pS->SetStartNode();
		
	}
	void Out(CEnemy* pE)override {}
	void UpdateSate(CEnemy* pE,float dt)override 
	{
		//Tool::BlendRunUp(moveblend, dt, 1.0);
		//Tool::BlendRunUp(Rotblend, dt, 1.0);
		BossStateBase::UpdaSatePatrolOnly(pE,dt);
		AStarPathFinding* pS = pE->GetPointForAstar();
		XMFLOAT3 asd = pE->GetPosition();
		pS->UpdateX();
		if (pS->GetFindPathDir())
		{
			pE->MoveAstarRot();
		}

		pE->GetpAnim()->Update(dt, 0.5f);
		//pE->SetPosition(asd);

		time += dt * 3.0f;
		CRenderer::Debug_move_Rotation2[1] = time;

		if (time > 3.0f)
		{
			pE->MoveRotFreeActionx<MoveBack>();
		}
	}

private:
	XMFLOAT2 PatrolPos[5];
	float time;
};

class  Movex : public BossStateBase
{
public:
	void Enter(CEnemy* pE)override { pE->Get_Date()->Currentanim = Zombie_run; }
	void Out(CEnemy* pE)override {}
	void UpdateSate(CEnemy* pE, float dt)override
	{
		 CMap* pMap = CManager::GetScene()->GetGmeobjs<CMap>(MAP_ID);
		 CP0* p0 = CManager::GetScene()->GetGmeobjs<CP0>(4);
		XMVECTOR xpos = pE->XMGet_pos();


		XMFLOAT3 RayDir;
		XMStoreFloat3(&RayDir, (pE->GetNowFaceDir()));
		Ray ray(pE->GetPosition(), RayDir);


		xpos += pE->GetNowFaceDir() * 2.0f;
		XMFLOAT3 pos;
		XMStoreFloat3(&pos, xpos);
		pE->SetPosition(pos);

		float dis = Tool::Distance_float(p0->GetPosition(), pE->GetPosition());
		if (dis < 40)
		{
			pE->MoveAttackx();
		}
		for (int i = 0; i < 27; i++)
		{
			if (ray.Hit(pMap->GetWallBox(i)) && (pE->GetSphereBox(1.0f).Contains(pMap->GetWallBox(i)))&&i!=25)
			{
				pE->MoveBackx();
			}
		}



		pE->GetpAnim()->Update(dt, 4.0f);
	}

private:

};
class MoveAstarRotx : public BossStateBase
{
public:
	void Enter(CEnemy* pE)override
	{
		//XMConvertToDegrees
		AStarPathFinding* pS = pE->GetPointForAstar();
		deg = (XMVectorGetY(XMVector3AngleBetweenVectors(pE->GetNowFaceDir(), pS->NowMoveDir())));
		float dot = XMVectorGetY(XMVector3Cross(pE->GetNowFaceDir(), pS->NowMoveDir()));
		if (dot > 0) DotC = 1;
		else if (dot == 0) DotC = 1;
		else DotC = -1;
		nowRot = pE->GetRotation();
		pE->Get_Date()->Currentanim = Zombie_run;

		Blend = 0;
	}
	void Out(CEnemy* pE)override {}
	void UpdateSate(CEnemy* pE, float dt)override
	{
		
		Tool::BlendRunUp(Blend, dt, 1.0f);
		XMFLOAT3 rot = { nowRot.x,nowRot.y + (Blend * deg) * DotC ,nowRot.z };
		pE->SetRotation(rot);
		if (Blend == 1)
		{
			pE->MoveAstar();
		}
		pE->GetpAnim()->Update(dt, 3.0f);

	}


private:
	float Blend;
	float deg;
	int DotC;
	XMFLOAT3 nowRot;
};
class MoveRotx : public BossStateBase
{
public:
	void Enter(CEnemy* pE)override
	{
		//XMConvertToDegrees
			deg = (XMVectorGetY(XMVector3AngleBetweenVectors(pE->GetNowFaceDir(), pE->GetTargetDir())));
			float dot = XMVectorGetY(XMVector3Cross(pE->GetNowFaceDir(), pE->GetTargetDir()));
			if (dot > 0) DotC = 1;
			else if (dot == 0) DotC = 1;
			else DotC = -1;
			nowRot = pE->GetRotation();
			pE->Get_Date()->Currentanim = Zombie_run;

		Blend = 0;
	}
	void Out(CEnemy* pE)override {}
	void UpdateSate(CEnemy* pE, float dt)override
	{
		Tool::BlendRunUp(Blend, dt, 1.0f);
		XMFLOAT3 rot = { nowRot.x,nowRot.y + (Blend * deg) * DotC ,nowRot.z };
		pE->SetRotation(rot);
		if (Blend == 1)
		{
			pE->Move();
		}
		pE->GetpAnim()->Update(dt, 3.0f);

	}


private:
	float Blend;
	float deg;
	int DotC;
	XMFLOAT3 nowRot;
};

template<int T>
class MoveRotFreeAction : public BossStateBase
{
public:
	void Enter(CEnemy* pE)override
	{
		CP0* p0 = CManager::GetScene()->GetGmeobjs<CP0>(4);
		XMVECTOR TargetDir;
		if (T == MoveBack)
		{
			TargetDir = XMVector3Normalize(XMVectorSet(0,0,160,0) - pE->XMGet_pos());
		}
		else if(T==MoveAttack)
		{
			TargetDir = XMVector3Normalize(p0->XMGet_pos() - pE->XMGet_pos());
		}
		//XMConvertToDegrees
		deg = (XMVectorGetY(XMVector3AngleBetweenVectors(pE->GetNowFaceDir(), TargetDir)));
		float dot = XMVectorGetY(XMVector3Cross(pE->GetNowFaceDir(), TargetDir));
		if (dot > 0) DotC = 1;
		else if (dot == 0) DotC = 1;
		else DotC = -1;
		nowRot = pE->GetRotation();
		pE->Get_Date()->Currentanim = Zombie_run;

		Blend = 0;
	}
	void Out(CEnemy* pE)override {}
	void UpdateSate(CEnemy* pE, float dt)override
	{
		Tool::BlendRunUp(Blend, dt, 1.0f);
		XMFLOAT3 rot = { nowRot.x,nowRot.y + (Blend * deg) * DotC ,nowRot.z };
		pE->SetRotation(rot);
		if (Blend == 1)
		{
			if (T == MoveBack)
			{
				pE->MoveBackx();
			}
			else if (T == MoveAttack)
			{
				pE->Move();
			}
		}
		pE->GetpAnim()->Update(dt, 3.0f);

	}


private:
	float Blend;
	float deg;
	int DotC;
	XMFLOAT3 nowRot;
};







