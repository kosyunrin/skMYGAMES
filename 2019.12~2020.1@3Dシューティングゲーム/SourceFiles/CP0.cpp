#include"B_header.h"
#include"CPlayerManger.h"
//#include"end.h"

CP0::CP0()
{
	SDate.CurrentAnim = 0;
	sheji = false;
	moveStop = true;
	ZhunXSwitch = false;
	ZhunxColor = 0.5f;
	pModle = new CSkinnedfbxanim(NQDate, NQsize);
	pModle->SetInitanimation(SDate.CurrentAnim);
	//
	pZhunxin = new CPolygon();
	pZhunxin->Init2D(6);
	ZhunxPos.x = SCREEN_WIDTH / 2 + 50.0f;
	ZhunxPos.y = SCREEN_HEIGHT / 2 + 10.0f;
	ZHunxWH = 25.0f;


	
	//UI
	pUI = new CPolygon();
	pUI->Init2D(7);

}

CP0::~CP0()
{
}

void CP0::Init()
{
	Sound.Run = false;
	chuanxi = std::make_unique<CAudioClip>();
	chuanxi->Load("asset/Music/Chuanqi.wav");
	jiaobu = std::make_unique<CAudioClip>();
	jiaobu->Load("asset/Music/jiaobu.wav");
	
	m_Weapon_Knife = std::make_unique<ArmyKnife>();
	m_Weapon_Knife->InitWeapon();
	CRenderer::RunSwtichForZombie = false;
	m_Position = XMFLOAT3(-50.0f, 0.0f, 50.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.05f, 0.05f, 0.05f);
	rotBlend = 1.0f;
	Left_Right = 1.0f;
	rotBlend2 = 0.0f;
	rotBlend1 = 2.0f;
	CameraRotBlend = 0.0f;
	CameraRotBlendZ = 0.0f;
	CameraViewShootControl = 0.0f;
	SDate.JumpDownControl = false;
	SDate.JumpRunControl = false;
	SDate.PhysicalBar = 294.8f;

	//box
	XMVECTOR Vmax = XMLoadFloat3(&pModle->m_GetBoxPinots()[2].m_BoxPoint.Vmax);
	XMVECTOR Vmin = XMLoadFloat3(&pModle->m_GetBoxPinots()[2].m_BoxPoint.Vmin);
	XMFLOAT3 vmax;
	XMFLOAT3 vmin;
	XMFLOAT3 v3[8];
	XMStoreFloat3(&vmax, Vmax);
	XMStoreFloat3(&vmin, Vmin);
	CCreate::CreateBox(SDate.box, vmax, vmin);
	CCreate::CreateV8(SDate.box, v3);


	line = new Line();
	line->InitDrawBox(v3);

	SDate.HP = 5.0f;
	SDate.SpeedControl = 1.0f;
	Huanzidancontrol = false;
	SDate.BeHurtAnimControl = false;

	pTimer = std::make_unique<Timer>();
	pTimer->Reset();
	//chuanxi->Play(true);
	jiaobu->Play(true);
	jiaobu->Stop();
	//pModle->AddPartMeshes(pSmode->GetSkinnedMesh());
	m_WeaponType = WEAPON::Type::Gun;
	m_WeaponPattern = WEAPON::Pattern::UsingSate;
	
}

void CP0::Uninit()
{
	delete pModle;
	pZhunxin->Uninit3D(6);
	delete pZhunxin;
	line->Uninit();
	delete line;


	pUI->Uninit3D(7);
	delete pUI;

	chuanxi->Unload();
	jiaobu->Unload();
	
}

void CP0::Update(float dt)
{
	
	//CRenderer::Debug_move_v2[0] = Sound.Jump;
	//jiaobu->Play(true);
//	if (GamePad::ThumbRX() > 0.9f) SetCursorPos(GamePad::ThumbRX()*0.00000001f*dt, 0.0f);
//	else if (GamePad::ThumbRX() < -0.9f) SetCursorPos(GamePad::ThumbRX()*0.00000001f*dt, 0.0f);
//	else if (GamePad::ThumbRY() < -0.9f) SetCursorPos(GamePad::ThumbRY()*0.00000001f*dt, 0.0f);
//	else if (GamePad::ThumbRY() > 0.9f) SetCursorPos(GamePad::ThumbRY()*0.00000001f*dt, 0.0f);
//	else if(GamePad::ThumbRX()>0.5f&&GamePad::ThumbRY()>0.5f) SetCursorPos(GamePad::ThumbRX()*0.00000001f*dt, GamePad::ThumbRY()*0.00000001f*dt);
//	else if (GamePad::ThumbRX() < -0.5f&&GamePad::ThumbRY() > 0.5f) SetCursorPos(GamePad::ThumbRX()*0.00000001f*dt, GamePad::ThumbRY()*0.00000001f*dt);
//	else if (GamePad::ThumbRX() < -0.5f&&GamePad::ThumbRY() < -0.5f) SetCursorPos(GamePad::ThumbRX()*0.00000001f*dt, GamePad::ThumbRY()*0.00000001f*dt);
//	else if (GamePad::ThumbRX() > 0.5f&&GamePad::ThumbRY() < -0.5f) SetCursorPos(GamePad::ThumbRX()*0.00000001f*dt, GamePad::ThumbRY()*0.00000001f*dt);
//	SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	AnimationSpeed = 1.0f;
	SDate.CurrentAnim = _idie;
	CCameraOne* g_Camera = CManager::GetScene()->GetGmeobjs<CCameraOne>(_Camera);
	CEnemy* pE = CManager::GetScene()->GetGmeobjs<CEnemy>(6);
	CZombie_man* pMan = CManager::GetScene()->GetGmeobjs<CZombie_man>(7);
	CMap* pMap = CManager::GetScene()->GetGmeobjs<CMap>(MAP_ID);
	UImanager3D* pui = CManager::GetScene()->GetGmeobjs<UImanager3D>(UI_ID);

	CBlock* pBlock = CManager::GetScene()->GetGmeobjs<CBlock>(9);

	XMVECTOR PlayerPos = XMLoadFloat3(&m_Position);
	XMVECTOR Rot = XMLoadFloat3(&m_Rotation);

	XMVECTOR ForwardMovemengt = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	//desiredCharDir = XMVector3Normalize(desiredCharDir);
	XMVECTOR faceDir = { 0.0f,0.0f,-1.0f,0.0f };
	XMVECTOR LeftDir = { -1.0f,0.0f,0.0f,0.0f };
	XMVECTOR nowface = XMVector3TransformNormal(faceDir, this->XMGet_WorldMatrix());
	if(moveStop)
	if (g_Camera != nullptr)
	{
		AnimInit();
		BoundingBox box = pMan->Get_box();
		BoundingBox colliderbox = pMan->Get_ColliderBox();
		XMFLOAT3 pos = box.Center;
		//XMVECTOR faceDir = { 0.0f,0.0f,-1.0f,0.0f };
		XMVECTOR ZFXfaceDir= { 0.0f,0.0f,1.0f,0.0f };
		/*XMVECTOR LeftDir = { -1.0f,0.0f,0.0f,0.0f };
		XMVECTOR nowface = XMVector3TransformNormal(faceDir, this->XMGet_WorldMatrix());*/
		XMVECTOR CamtoP0 = PlayerPos - g_Camera->Get_PosXM();
		float Degreesxx = XMConvertToDegrees(XMVectorGetY(XMVector3AngleBetweenVectors(nowface, CamtoP0)));
		if (rotBlend == 0.0f|| rotBlend==1.0f)
		{
			if (CInput::GetKeyTrigger('W'))
			{
				float Degrees = XMConvertToDegrees (XMVectorGetY(XMVector3AngleBetweenVectors(faceDir, CamtoP0)));
				if(Degrees>90.0f)
				if (XMVectorGetY(XMVector3Cross(ZFXfaceDir, nowface)) > 0.0f)Left_Right = 1.0f;
				else Left_Right = -1.0f;
				else 
				if (XMVectorGetY(XMVector3Cross(ZFXfaceDir, nowface)) > 0.0f)Left_Right = -1.0f;
				else Left_Right = 1.0f;

				rotBlend == 0.0f;
			}
			else if (CInput::GetKeyTrigger('S'))
			{
				float Degrees = XMConvertToDegrees(XMVectorGetY(XMVector3AngleBetweenVectors(faceDir, CamtoP0)));
				if (Degrees > 90.0f)
					if (XMVectorGetY(XMVector3Cross(ZFXfaceDir, nowface)) > 0.0f)Left_Right = -1.0f;
					else Left_Right = 1.0f;
				else
					if (XMVectorGetY(XMVector3Cross(ZFXfaceDir, nowface)) > 0.0f)Left_Right = 1.0f;
					else Left_Right = -1.0f;

				rotBlend == 1.0f;
			}
			else if (CInput::GetKeyTrigger('A')||GamePad::IsTrigger(GamePad::Button::THUMB_L_LEFT))
			{
			
				if(Degreesxx <60.0f)FaceNumber = A;
				else
				{
					FaceNumber = X;
					rotBlend = 0.0f;
				}
				rotBlend1 = 2.0f;
			}
			else if (CInput::GetKeyTrigger('D')||GamePad::IsTrigger(GamePad::Button::THUMB_L_RIGHT))
			{
				
				if (Degreesxx < 60.0f)FaceNumber = D;
				else
				{
					FaceNumber = Y;
					rotBlend = 0.0f;
				}
				rotBlend2 = 0.0f;

			}
		}
		float Degrees = XMConvertToDegrees(XMVectorGetY(XMVector3AngleBetweenVectors(nowface, CamtoP0)));
		State_Collider = NONE;
		State_Floor = NONE2;
		BoundingSphere sphere;
		sphere.Radius = 1.0f;
		sphere.Center = this->GetPosition();
	
		
		//diban jiaoche

		XMVECTOR DownDir = { 0.0f,-1.0f,0.0f,0.0f };
		
		XMFLOAT3 down;
		XMStoreFloat3(&down, DownDir);
		XMVECTOR RayPosXM = PlayerPos + nowface * 50.0f;
		XMFLOAT3 RayPos;
		XMStoreFloat3(&RayPos, RayPosXM);
		Ray ray_down(m_Position, down);

		XMFLOAT3 Dir;
		XMStoreFloat3(&Dir, XMVector3Normalize(nowface));
		Ray ray(RayPos, Dir);

		CRenderer::Debug_show_v2[1] = 900;
		if (CInput::GetKeyPress('W')||GamePad::ThumbLY()> 0.75f)
		{
			SDate.CurrentAnim = _Run;
			if (rotBlend < 1.0f)rotBlend += 2.5f * dt;
			else rotBlend = 1.0f;

			FaceNumber = W;

		
			if (ray_down.Hit(pMap->GetFloorBox(0))) { State_Floor = FLOOR0; }
			else if (ray_down.Hit(pMap->GetFloorBox(1))) { State_Floor = FLOOR1; }
			else if (ray_down.Hit(pMap->Get_OBBOX(7))) { State_Floor = FLOOR2;}
			else if (ray_down.Hit(pMap->GetFloorBox(3))) { State_Floor = FLOOR3;   }
		
			

			ForwardMovemengt = g_Camera->getForward();
			MoveRevise(PlayerPos, ForwardMovemengt, dt);
		}
		
		else if (CInput::GetKeyPress('S')|| GamePad::ThumbLY() < -0.75f)
		{
			
			 FaceNumber = S;
			SDate.CurrentAnim = _Run;
			if (rotBlend > 0.0f)rotBlend -= 2.5f * dt;
			else rotBlend = 0.0f;

			
			if (ray_down.Hit(pMap->GetFloorBox(0))) { State_Floor = FLOOR0; }
			else if (ray_down.Hit(pMap->GetFloorBox(1))) { State_Floor = FLOOR1; }
			else if (ray_down.Hit(pMap->Get_OBBOX(7))) {	State_Floor = FLOOR2;	}
			else if (ray_down.Hit(pMap->GetFloorBox(3))) { State_Floor = FLOOR3; }

				ForwardMovemengt = g_Camera->getForward()*-1;
				MoveRevise(PlayerPos, ForwardMovemengt, dt);
		}
		 else if (CInput::GetKeyPress('A')|| GamePad::ThumbLX() < -0.75f)
		{
			
			SDate.CurrentAnim = _Run;
			if (rotBlend1 > 1.0f)rotBlend1 -= 2.5f * dt;
			else rotBlend1 = 1.0f;

			if (FaceNumber == X)
			{
				if (rotBlend < 1.0f)rotBlend += 5.0f*dt;
				else rotBlend = 1.0f;
			}
		
			if (ray_down.Hit(pMap->GetFloorBox(0))) { State_Floor = FLOOR0; }
			else if (ray_down.Hit(pMap->GetFloorBox(1))) { State_Floor = FLOOR1; }
			else if (ray_down.Hit(pMap->Get_OBBOX(7))) { State_Floor = FLOOR2; CRenderer::Debug_show_v2[1] = 1900; }
			else if (ray_down.Hit(pMap->GetFloorBox(3))) { State_Floor = FLOOR3; }
	
			{
				ForwardMovemengt = g_Camera->getcamRight();
				MoveRevise(PlayerPos, ForwardMovemengt, dt);
			}
		}
		 else if (CInput::GetKeyPress('D')|| GamePad::ThumbLX() > 0.75f)
		{
			
			SDate.CurrentAnim = _Run;


			if (rotBlend2 < 1.0f)rotBlend2 += 2.5f * dt;
			else rotBlend2 = 1.0f;

			if (FaceNumber == Y)
			{
				if (rotBlend < 1.0f)rotBlend += 5.0f*dt;
				else rotBlend = 1.0f;
			}

			if (ray_down.Hit(pMap->GetFloorBox(0))) { State_Floor = FLOOR0; }
			else if (ray_down.Hit(pMap->GetFloorBox(1))) { State_Floor = FLOOR1; }
			else if (ray_down.Hit(pMap->Get_OBBOX(7))) { State_Floor = FLOOR2; CRenderer::Debug_show_v2[1] = 1900; }
			else if (ray_down.Hit(pMap->GetFloorBox(3))) { State_Floor = FLOOR3; }

		
			{
				ForwardMovemengt = g_Camera->getcamRight()*-1;
				MoveRevise(PlayerPos, ForwardMovemengt, dt);
			}
		}


		

		 // wall 判定
		 switch (State_Collider)
		 {
		 case WALLBOX0:
			 {
				CRenderer::Debug_show_v2[1] = 15555;
				 XMVECTOR right = {0.0f,0.0f, -1.0f,0.0f };
				 XMVECTOR Dir = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
				
				 {
					 if(Tool::GET_ANGLE(nowface,Dir)>0.0f)
					 {
						 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(6)))
							 PlayerPos += (right)  * 20.0f * dt;
					 }
					 else
						 if(!CCollider::ISBOXHIT(this->Get_Box(),pMap->GetWallBox(1)))
						 PlayerPos += (-right) * 20.0f * dt;
				 }
			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX1:
			 if (CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(1)))
			 {

			
				 XMVECTOR X = { 1.0f,0.0f,0.0f,0.0f };
				 XMVECTOR Z = { 0.0f,0.0f,1.0f,0.0f };
				 XMFLOAT3 center = pMap->GetWallBox(1).Center;
				 XMVECTOR Dir = XMLoadFloat3(&center) - PlayerPos;
				 float Dis = Tool::Distance_float(center, this->GetPosition());
				 float Deg = XMVectorGetY(XMVector3AngleBetweenVectors(faceDir, Dir));
				 float H = Tool::Get_Ht(Dis, Deg);

				 if (H < 60)
				 {
					 if (Tool::GET_ANGLE(nowface, Z) < 0.0f)
					 {
						 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(0))&&
							 !CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(2)))
						 PlayerPos += X * 20.0f * dt;
					 }
					 else
						 PlayerPos += -X * 20.0f * dt;
				 }
				 else
				 {
					 if (Tool::GET_ANGLE(nowface, X) < 0.0f)
						 PlayerPos += -Z * 20.0f * dt;
					 else
						 PlayerPos += Z * 20.0f * dt;
				 }
			 }
			 else
			 {
				 ForwardMovemengt = g_Camera->getForward();
				 MoveRevise(PlayerPos, ForwardMovemengt, dt);
			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
			
		 case WALLBOX2:
			 if (CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(2)))
			 {
				 XMVECTOR X = { 1.0f,0.0f,0.0f,0.0f };
				 XMVECTOR Z = { 0.0f,0.0f,1.0f,0.0f };
				 XMFLOAT3 center = { pMap->GetWallBox(2).Center.x,0.0f,pMap->GetWallBox(2).Center.z };

				 XMVECTOR Dir = XMLoadFloat3(&center) - PlayerPos;
				 float Dis = Tool::Distance_float(center, this->GetPosition());
				 float Deg = XMVectorGetY(XMVector3AngleBetweenVectors(Dir, -X));
				 float H = Tool::Get_Ht(Dis, Deg);

				 if (H > 115.0f)
				 {
					 if (Tool::GET_ANGLE(nowface, Z) < 0.0f)
					 {
						 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(1)))
						 PlayerPos += X * 20.0f * dt;
					 }
					 else
						 PlayerPos += -X * 20.0f * dt;
				 }
				 else
				 {
					 if (Tool::GET_ANGLE(nowface, X) < 0.0f)
					 {
						 PlayerPos += -Z * 20.0f * dt;
					 }
					 else
						 PlayerPos += Z * 20.0f * dt;
				 }
			 }
			 else
			 {
				 ForwardMovemengt = g_Camera->getForward();
				 MoveRevise(PlayerPos, ForwardMovemengt, dt);
			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX3:
			 if (CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(3)))
			 {
				 XMVECTOR X = { 1.0f,0.0f,0.0f,0.0f };
				 XMVECTOR Z = { 0.0f,0.0f,1.0f,0.0f };
				 XMFLOAT3 center = { pMap->GetWallBox(3).Center.x,0.0f,pMap->GetWallBox(3).Center.z };

				 XMVECTOR Dir = XMLoadFloat3(&center) - PlayerPos;
				 float Dis = Tool::Distance_float(center, this->GetPosition());
				 float Deg = XMVectorGetY(XMVector3AngleBetweenVectors(Dir, -X));
				 float H = Tool::Get_Ht(Dis, Deg);

				 if (H > 115.0f)
				 {
					 if (Tool::GET_ANGLE(nowface, Z) < 0.0f)
					 {
						 PlayerPos += X * 20.0f * dt;
					 }
					 else
						 PlayerPos += -X * 20.0f * dt;
				 }
				 else
				 {
					 if (Tool::GET_ANGLE(nowface, X) < 0.0f)
					 {
						 if (!CCollider::ISBOXHIT(this->Get_Sphere(), pMap->Get_OBBOX(11)))
						 PlayerPos += -Z * 20.0f * dt;
					 }
					 else
						 if (!CCollider::ISBOXHIT(this->Get_Sphere(), pMap->Get_OBBOX(10)))
						 PlayerPos += Z * 20.0f * dt;
				 }
			 }
			 else
			 {
				 ForwardMovemengt = g_Camera->getForward();
				 MoveRevise(PlayerPos, ForwardMovemengt, dt);
			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX4:
			 if (CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(4)))
			 {


				 XMVECTOR X = { 1.0f,0.0f,0.0f,0.0f };
				 XMVECTOR Z = { 0.0f,0.0f,1.0f,0.0f };
				 XMFLOAT3 center = pMap->GetWallBox(4).Center;
				 XMVECTOR Dir = XMLoadFloat3(&center) - PlayerPos;
				 float Dis = Tool::Distance_float(center, this->GetPosition());
				 float Deg = XMVectorGetY(XMVector3AngleBetweenVectors(faceDir, Dir));
				 float H = Tool::Get_Ht(Dis, Deg);

				 if (H < 60)
				 {
					 if (Tool::GET_ANGLE(nowface, Z) < 0.0f)
					 {
						 if(!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(17)))
						 PlayerPos += X * 20.0f * dt;
					 }
					 else
					 {
						 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(5))&& !CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(17)))
							 PlayerPos += -X * 20.0f * dt;
					 }
				 }
				 else
				 {
					 if (Tool::GET_ANGLE(nowface, X) < 0.0f)
						 PlayerPos += -Z * 20.0f * dt;
					 else
						 PlayerPos += Z * 20.0f * dt;
				 }
			 }
			 else
			 {
				 ForwardMovemengt = g_Camera->getForward();
				 MoveRevise(PlayerPos, ForwardMovemengt, dt);
			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX5:
			 if (CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(5)))
			 {

				 XMVECTOR right = { 0.0f,0.0f, -1.0f,0.0f };
				 XMVECTOR Dir = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);

				 {
					 if (Tool::GET_ANGLE(nowface, Dir) > 0.0f)
					 {
						 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(7))&& !CCollider::ISBOXHIT(this->Get_Sphere(), pMap->Get_OBBOX(1)))
							 PlayerPos += (right)  * 20.0f * dt;
					 }
					 else
						 if(!CCollider::ISBOXHIT(this->Get_Sphere(), pMap->Get_OBBOX(5)))
							 PlayerPos += (-right) * 20.0f * dt;
				 }
			 }
			 else
			 {
				 ForwardMovemengt = g_Camera->getForward();
				 MoveRevise(PlayerPos, ForwardMovemengt, dt);
			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX6:
			 if (CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(6)))
			 {


				 XMVECTOR X = { 1.0f,0.0f,0.0f,0.0f };
				 XMVECTOR Z = { 0.0f,0.0f,1.0f,0.0f };
				 XMFLOAT3 center = { pMap->GetWallBox(6).Center.x,0.0f,pMap->GetWallBox(6).Center.z };
				 XMFLOAT3 P0os = { this->GetPosition().x,0.0f,this->GetPosition().z};
				 XMVECTOR Dir = XMLoadFloat3(&center) -XMLoadFloat3(&P0os);
				 float Dis = Tool::Distance_float(center, P0os);
				 float Deg = XMVectorGetY(XMVector3AngleBetweenVectors(faceDir, -X));
				 float H = Tool::Get_Ht(Dis, Deg);

				 if (H > 32.5f)
				 {
					 if (Tool::GET_ANGLE(nowface, Z) < 0.0f)
						 PlayerPos += X * 20.0f * dt;
					 else
						 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(8)))
						 PlayerPos += -X * 20.0f * dt;
				 }
				 else
				 {
					 if (Tool::GET_ANGLE(nowface, X) < 0.0f)
						 PlayerPos += -Z * 20.0f * dt;
					 else
						 PlayerPos += Z * 20.0f * dt;
				 }
			 }
			 else
			 {
				 ForwardMovemengt = g_Camera->getForward();
				 MoveRevise(PlayerPos, ForwardMovemengt, dt);
			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX7:
			 if (CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(7)))
			 {


				 XMVECTOR X = { 1.0f,0.0f,0.0f,0.0f };
				 XMVECTOR Z = { 0.0f,0.0f,1.0f,0.0f };
				 XMFLOAT3 center = { pMap->GetWallBox(7).Center.x,0.0f,pMap->GetWallBox(7).Center.z };
				 XMFLOAT3 P0os = { this->GetPosition().x,0.0f,this->GetPosition().z };
				 XMVECTOR Dir = XMLoadFloat3(&center) - XMLoadFloat3(&P0os);
				 float Dis = Tool::Distance_float(center, P0os);
				 float Deg = XMVectorGetY(XMVector3AngleBetweenVectors(faceDir, -X));
				 float H = Tool::Get_Ht(Dis, Deg);

				 if (H > 32.5f)
				 {
					 if (Tool::GET_ANGLE(nowface, Z) < 0.0f)
					 {
						 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(9)))
						 PlayerPos += X * 20.0f * dt;
					 }
					 else
						 PlayerPos += -X * 20.0f * dt;
				 }
				 else
				 {
					 if (Tool::GET_ANGLE(nowface, X) < 0.0f)
						 PlayerPos += -Z * 20.0f * dt;
					 else
						 PlayerPos += Z * 20.0f * dt;
				 }
			 }
			 else
			 {
				 ForwardMovemengt = g_Camera->getForward();
				 MoveRevise(PlayerPos, ForwardMovemengt, dt);
			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX8:
			 if (CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(8)))
			 {

				 XMVECTOR right = { 0.0f,0.0f, -1.0f,0.0f };
				 XMVECTOR Dir = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);

				 {
					 if (Tool::GET_ANGLE(nowface, Dir) > 0.0f)
					 {
						// if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(11)))
							 PlayerPos += (right)  * 20.0f * dt;
					 }
					 else
						 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(11)))
							 PlayerPos += (-right) * 20.0f * dt;
				 }
			 }
			 else
			 {
				 ForwardMovemengt = g_Camera->getForward();
				 MoveRevise(PlayerPos, ForwardMovemengt, dt);
			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX9:
			 if (CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(9)))
			 {

				 XMVECTOR right = { 0.0f,0.0f, -1.0f,0.0f };
				 XMVECTOR Dir = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);

				 {
					 if (Tool::GET_ANGLE(nowface, Dir) > 0.0f)
					 {
						 //if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(6)))
						 PlayerPos += (right)  * 20.0f * dt;
					 }
					 else
						 //if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(1)))
						 PlayerPos += (-right) * 20.0f * dt;
				 }
			 }
			 else
			 {
				 ForwardMovemengt = g_Camera->getForward();
				 MoveRevise(PlayerPos, ForwardMovemengt, dt);
			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX10:
			 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetFloorBox(1)))
			 {
				 if (CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(10)))
				 {


					 XMVECTOR X = { 1.0f,0.0f,0.0f,0.0f };
					 XMVECTOR Z = { 0.0f,0.0f,1.0f,0.0f };
					 XMFLOAT3 center = { pMap->GetWallBox(10).Center.x,0.0f,pMap->GetWallBox(11).Center.z };
					 XMVECTOR Dir2;
					 Dir2 = PlayerPos;
					 XMVectorSetY(Dir2, 0.0f);
					 XMVECTOR Dir = XMLoadFloat3(&center) - Dir2;
					 float Dis = Tool::Distance_float(center, this->GetPosition());
					 float Deg = XMVectorGetY(XMVector3AngleBetweenVectors(faceDir, Dir));
					 float H = Tool::Get_Ht(Dis, Deg);

					 if (H < 5.5f)
					 {
						 if (Tool::GET_ANGLE(nowface, Z) < 0.0f)
							 PlayerPos += X * 20.0f * dt;
						 else
							 // if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(5)))
							 PlayerPos += -X * 20.0f * dt;
					 }
					 else
					 {
						 if (Tool::GET_ANGLE(nowface, X) < 0.0f)
						 {
							 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(12)))
								 PlayerPos += -Z * 20.0f * dt;
						 }
						 else
							 PlayerPos += Z * 20.0f * dt;
					 }
				 }
				 else
				 {
					 ForwardMovemengt = g_Camera->getForward();
					 MoveRevise(PlayerPos, ForwardMovemengt, dt);
				 }
			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX11:
			 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetFloorBox(1)))
			 {
				 if (CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(11)))
				 {


					 XMVECTOR X = { 1.0f,0.0f,0.0f,0.0f };
					 XMVECTOR Z = { 0.0f,0.0f,1.0f,0.0f };
					 XMFLOAT3 center = { pMap->GetWallBox(11).Center.x,0.0f,pMap->GetWallBox(11).Center.z };
					 XMVECTOR Dir2;
					 Dir2 = PlayerPos;
					 XMVectorSetY(Dir2, 0.0f);
					 XMVECTOR Dir = XMLoadFloat3(&center) - Dir2;
					 float Dis = Tool::Distance_float(center, this->GetPosition());
					 float Deg = XMVectorGetY(XMVector3AngleBetweenVectors(faceDir, Dir));
					 float H = Tool::Get_Ht(Dis, Deg);


					 if (H < 5.5f)
					 {
						 if (Tool::GET_ANGLE(nowface, Z) < 0.0f)
							 PlayerPos += X * 20.0f * dt;
						 else
							 // if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(5)))
							 PlayerPos += -X * 20.0f * dt;
					 }
					 else
					 {
						 if (Tool::GET_ANGLE(nowface, X) < 0.0f)
						 {
							 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(12)))
								 PlayerPos += -Z * 20.0f * dt;
						 }
						 else
							 PlayerPos += Z * 20.0f * dt;
					 }
				 }
				 else
				 {
					 ForwardMovemengt = g_Camera->getForward();
					 MoveRevise(PlayerPos, ForwardMovemengt, dt);
				 }
			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX12:
			 //if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetFloorBox(1)))
			 {
				 if (CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(12)))
				 {


					 XMVECTOR X = { 1.0f,0.0f,0.0f,0.0f };
					 XMVECTOR Z = { 0.0f,0.0f,1.0f,0.0f };
					 XMFLOAT3 center = { pMap->GetWallBox(12).Center.x,0.0f,pMap->GetWallBox(12).Center.z };

					 XMVECTOR Dir = XMLoadFloat3(&center) - PlayerPos;
					 float Dis = Tool::Distance_float(center, this->GetPosition());
					 float Deg = XMVectorGetY(XMVector3AngleBetweenVectors(Dir, -X));
					 float H = Tool::Get_Ht(Dis, Deg);

					 if (H > 5.0f)
					 {
						 if (Tool::GET_ANGLE(nowface, Z) < 0.0f)
						 {
							 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(14)))
								 PlayerPos += X * 20.0f * dt;
						 }
						 else
							 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(13)))
								 PlayerPos += -X * 20.0f * dt;
					 }
					 else
					 {
						 if (Tool::GET_ANGLE(nowface, X) < 0.0f)
						 {
							 // if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(11)))
							 PlayerPos += -Z * 20.0f * dt;
						 }
						 else
							 PlayerPos += Z * 20.0f * dt;
					 }
				 }
				 else
				 {
					 ForwardMovemengt = g_Camera->getForward();
					 MoveRevise(PlayerPos, ForwardMovemengt, dt);
				 }
			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX13:
			
			
			 {
				 BoundingSphere shere;
				 shere.Center = { m_Position.x,m_Position.y + 4.0f,m_Position.z };
				 shere.Radius = 1.0f;
				 if (!CCollider::ISBOXHIT(shere, pMap->GetFloorBox(2)))
				 {


					 XMVECTOR X = { 1.0f,0.0f,0.0f,0.0f };
					 XMVECTOR Z = { 0.0f,0.0f,1.0f,0.0f };
					 XMFLOAT3 center = { pMap->GetWallBox(13).Center.x,0.0f,pMap->GetWallBox(13).Center.z };

					 XMVECTOR Dir = XMLoadFloat3(&center) - PlayerPos;
					 float Dis = Tool::Distance_float(center, this->GetPosition());
					 float Deg = XMVectorGetY(XMVector3AngleBetweenVectors(Dir, -X));
					 float H = Tool::Get_Ht(Dis, Deg);

					 if (H > 18.0f)
					 {
						 if (Tool::GET_ANGLE(nowface, Z) < 0.0f)
						 {
							 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetFloorBox(0)))
								 PlayerPos += X * 20.0f * dt;
						 }
						 else
							 // if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(5)))
							 PlayerPos += -X * 20.0f * dt;
					 }
					 else
					 {
						 if (Tool::GET_ANGLE(nowface, X) < 0.0f)
						 {
							 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetFloorBox(0)))
							 {
								 PlayerPos += -Z * 20.0f * dt;
							 }
						 }
						 else
							 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetFloorBox(0)))
								 PlayerPos += Z * 20.0f * dt;
					 }
				 }
			 }

				 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX14:
			 if (State_Floor != FLOOR3)
			 {
				 CRenderer::Debug_show_v2[1] = 199;
				 if (CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(14)))
				 {
					 XMVECTOR X = { 1.0f,0.0f,0.0f,0.0f };
					 XMVECTOR Z = { 0.0f,0.0f,1.0f,0.0f };
					 XMFLOAT3 center = { pMap->GetWallBox(14).Center.x,0.0f,pMap->GetWallBox(14).Center.z };

					 XMVECTOR Dir = XMLoadFloat3(&center) - PlayerPos;
					 float Dis = Tool::Distance_float(center, this->GetPosition());
					 float Deg = XMVectorGetY(XMVector3AngleBetweenVectors(Dir, -X));
					 float H = Tool::Get_Ht(Dis, Deg);

					 if (H > 18.0f)
					 {
						 if (Tool::GET_ANGLE(nowface, Z) < 0.0f)
						 {
							 PlayerPos += X * 20.0f * dt;
						 }
						 else
							 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetFloorBox(0)))
								 PlayerPos += -X * 20.0f * dt;
							 else
							 {
								 XMFLOAT3 p1 = { 0.0f,0.0f,-32.0f };
								 XMFLOAT3 p2 = { 0.0f,0.0f,this->GetPosition().z };
								 float distans = Tool::Distance_float(p1, p2);
								 float H = tanf(XMConvertToRadians(35.0f))*distans;
								 //Z = XMVectorSetY(Z, H);
								 PlayerPos += -Z * 10.0f * dt;
								 PlayerPos = XMVectorSetY(PlayerPos, H);
							 }
					 }
					 else
					 {
						 if (Tool::GET_ANGLE(nowface, X) < 0.0f)
						 {
							 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetFloorBox(0)))
							 {
								 PlayerPos += -Z * 20.0f * dt;
							 }
							 else
							 {
								 XMFLOAT3 p1 = { 0.0f,0.0f,-32.0f };
								 XMFLOAT3 p2 = { 0.0f,0.0f,this->GetPosition().z };
								 float distans = Tool::Distance_float(p1, p2);
								 float H = tanf(XMConvertToRadians(35.0f))*distans;
								 //Z = XMVectorSetY(Z, H);
								 PlayerPos += -Z * 10.0f * dt;
								 PlayerPos = XMVectorSetY(PlayerPos, H);
							 }
						 }
						 else
							 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetFloorBox(0)))
								 PlayerPos += Z * 20.0f * dt;
							 else
							 {
								 XMFLOAT3 p1 = { 0.0f,0.0f,-32.0f };
								 XMFLOAT3 p2 = { 0.0f,0.0f,this->GetPosition().z };
								 float distans = Tool::Distance_float(p1, p2);
								 float H = tanf(XMConvertToRadians(35.0f))*distans;
								 //Z = XMVectorSetY(Z, H);
								 PlayerPos += Z * 10.0f * dt;
								 PlayerPos = XMVectorSetY(PlayerPos, H);
							 }
					 }
				 }
				 else
				 {
					 ForwardMovemengt = g_Camera->getForward();
					 MoveRevise(PlayerPos, ForwardMovemengt, dt);
				 }
			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX15:
			 {
				 if (CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(15)))
				 {


					 XMVECTOR X = { 1.0f,0.0f,0.0f,0.0f };
					 XMVECTOR Z = { 0.0f,0.0f,1.0f,0.0f };
					 XMFLOAT3 center = { pMap->GetWallBox(15).Center.x,0.0f,pMap->GetWallBox(15).Center.z };

					 XMVECTOR Dir = XMLoadFloat3(&center) - PlayerPos;
					 float Dis = Tool::Distance_float(center, this->GetPosition());
					 float Deg = XMVectorGetY(XMVector3AngleBetweenVectors(Dir, -X));
					 float H = Tool::Get_Ht(Dis, Deg);

					 if (H > 5.0f)
					 {
						 if (Tool::GET_ANGLE(nowface, Z) < 0.0f)
						 {
							 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(14)))
								 PlayerPos += X * 20.0f * dt;
						 }
						 else
							 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetFloorBox(0)))
							 {
								 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(14)))
									 PlayerPos += -X * 20.0f * dt;
							 }
							 else
							 {
								 XMFLOAT3 p1 = { 0.0f,0.0f,-32.0f };
								 XMFLOAT3 p2 = { 0.0f,0.0f,this->GetPosition().z };
								 float distans = Tool::Distance_float(p1, p2);
								 float H = tanf(XMConvertToRadians(35.0f))*distans;
								 //Z = XMVectorSetY(Z, H);
								 PlayerPos += -Z * 10.0f * dt;
								 PlayerPos = XMVectorSetY(PlayerPos, H);
							 }
					 }
					 else
					 {
						 if (Tool::GET_ANGLE(nowface, X) < 0.0f)
						 {
							 // if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(11)))
							 PlayerPos += -Z * 20.0f * dt;
						 }
						 else
							 PlayerPos += Z * 20.0f * dt;
					 }
				 }
				 else
				 {
					 ForwardMovemengt = g_Camera->getForward();
					 MoveRevise(PlayerPos, ForwardMovemengt, dt);
				 }

			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX16:
			 {
				 if (CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(16)))
				 {


					 XMVECTOR X = { 1.0f,0.0f,0.0f,0.0f };
					 XMVECTOR Z = { 0.0f,0.0f,1.0f,0.0f };
					 XMFLOAT3 center = { pMap->GetWallBox(16).Center.x,0.0f,pMap->GetWallBox(16).Center.z };

					 XMVECTOR Dir = XMLoadFloat3(&center) - PlayerPos;
					 float Dis = Tool::Distance_float(center, this->GetPosition());
					 float Deg = XMVectorGetY(XMVector3AngleBetweenVectors(Dir, -X));
					 float H = Tool::Get_Ht(Dis, Deg);

					 if (H > 5.0f)
					 {
						 if (Tool::GET_ANGLE(nowface, Z) < 0.0f)
						 {
							 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetFloorBox(0)))
							 {
								 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(13)))
									 PlayerPos += X * 20.0f * dt;
							 }
							 else
							 {
								 XMFLOAT3 p1 = { 0.0f,0.0f,-32.0f };
								 XMFLOAT3 p2 = { 0.0f,0.0f,this->GetPosition().z };
								 float distans = Tool::Distance_float(p1, p2);
								 float H = tanf(XMConvertToRadians(35.0f))*distans;
								 //Z = XMVectorSetY(Z, H);
								 PlayerPos += -Z * 10.0f * dt;
								 PlayerPos = XMVectorSetY(PlayerPos, H);
							 }
						 }
						 else
							 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(13)) && !CCollider::ISBOXHIT(this->Get_Sphere(), pMap->Get_OBBOX(2)))
								 PlayerPos += -X * 20.0f * dt;
					 }
					 else
					 {
						 if (Tool::GET_ANGLE(nowface, X) < 0.0f)
						 {
							 // if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(11)))
							 PlayerPos += -Z * 20.0f * dt;
						 }
						 else
							 PlayerPos += Z * 20.0f * dt;
					 }
				 }
				 else
				 {
					 ForwardMovemengt = g_Camera->getForward();
					 MoveRevise(PlayerPos, ForwardMovemengt, dt);
				 }

			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX17:
				 if (CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(17)))
				 {
					 XMVECTOR X = { 1.0f,0.0f,0.0f,0.0f };
					 XMVECTOR Z = { 0.0f,0.0f,1.0f,0.0f };
					 XMFLOAT3 center = { pMap->GetWallBox(17).Center.x,0.0f,pMap->GetWallBox(17).Center.z };

					 XMVECTOR Dir = XMLoadFloat3(&center) - PlayerPos;
					 float Dis = Tool::Distance_float(center, this->GetPosition());
					 float Deg = XMVectorGetY(XMVector3AngleBetweenVectors(Dir, -X));
					 float H = Tool::Get_Ht(Dis, Deg);

					 if (H > 25.0f)
					 {
						 if (Tool::GET_ANGLE(nowface, Z) < 0.0f)
						 {
							 PlayerPos += X * 20.0f * dt;
						 }
						 else
							 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(18)))
								 PlayerPos += -X * 20.0f * dt;
					 }
					 else
					 {
						 if (Tool::GET_ANGLE(nowface, X) < 0.0f)
						 {
							 if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(18)))
								 PlayerPos += -Z * 20.0f * dt;
						 }
						 else
								 PlayerPos += Z * 20.0f * dt;
					 }
				 }
				 else
				 {
					 ForwardMovemengt = g_Camera->getForward();
					 MoveRevise(PlayerPos, ForwardMovemengt, dt);
				 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX18:
			 if (CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(18)))
			 {
				 XMVECTOR X = { 1.0f,0.0f,0.0f,0.0f };
				 XMVECTOR Z = { 0.0f,0.0f,1.0f,0.0f };
				 XMFLOAT3 center = { pMap->GetWallBox(18).Center.x,0.0f,pMap->GetWallBox(18).Center.z };

				 XMVECTOR Dir = XMLoadFloat3(&center) - PlayerPos;
				 float Dis = Tool::Distance_float(center, this->GetPosition());
				 float Deg = XMVectorGetY(XMVector3AngleBetweenVectors(Dir, -X));
				 float H = Tool::Get_Ht(Dis, Deg);

				 if (H > 15.0f)
				 {
					 if (Tool::GET_ANGLE(nowface, Z) < 0.0f)
					 {
						 PlayerPos += X * 20.0f * dt;
					 }
					 else
						 PlayerPos += -X * 20.0f * dt;
				 }
				 else
				 {
					 if (Tool::GET_ANGLE(nowface, X) < 0.0f)
					 {
						 PlayerPos += -Z * 20.0f * dt;
					 }
					 else
						 PlayerPos += Z * 20.0f * dt;
				 }
			 }
			 else
			 {
				 ForwardMovemengt = g_Camera->getForward();
				 MoveRevise(PlayerPos, ForwardMovemengt, dt);
			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX19:
			 if (CCollider::ISBOXHIT(this->Get_Sphere(), pMap->Get_OBBOX(0)))
			 {
			 }
			 else
			 {
				 ForwardMovemengt = g_Camera->getForward();
				 MoveRevise(PlayerPos, ForwardMovemengt, dt);
			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX20:
			 if (CCollider::ISBOXHIT(this->Get_Sphere(), pMap->Get_OBBOX(1)))
			 {
			 }
			 else
			 {
				 ForwardMovemengt = g_Camera->getForward();
				 MoveRevise(PlayerPos, ForwardMovemengt, dt);
			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX21:
			 if (CCollider::ISBOXHIT(this->Get_Sphere(), pMap->Get_OBBOX(2)))
			 {
			 }
			 else
			 {
				 ForwardMovemengt = g_Camera->getForward();
				 MoveRevise(PlayerPos, ForwardMovemengt, dt);
			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX22:
			 if (CCollider::ISBOXHIT(this->Get_Sphere(), pMap->Get_OBBOX(3)))
			 {
			 }
			 else
			 {
				 ForwardMovemengt = g_Camera->getForward();
				 MoveRevise(PlayerPos, ForwardMovemengt, dt);
			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX23:
			 if (CCollider::ISBOXHIT(this->Get_Sphere(), pMap->Get_OBBOX(4)))
			 {
			 }
			 else
			 {
				 ForwardMovemengt = g_Camera->getForward();
				 MoveRevise(PlayerPos, ForwardMovemengt, dt);
			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX24:
			 if (CCollider::ISBOXHIT(this->Get_Sphere(), pMap->Get_OBBOX(5)))
			 {
			 }
			 else
			 {
				 ForwardMovemengt = g_Camera->getForward();
				 MoveRevise(PlayerPos, ForwardMovemengt, dt);
			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX25:
			 if (CCollider::ISBOXHIT(this->Get_Sphere(), pMap->Get_OBBOX(6)))
			 {
			 }
			 else
			 {
				 ForwardMovemengt = g_Camera->getForward();
				 MoveRevise(PlayerPos, ForwardMovemengt, dt);
			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX26:
		
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX27:

			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX28:

			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX29:

			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case WALLBOX30:

			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 case MANSBOX:
			 if (CCollider::ISBOXHIT(this->Get_Sphere(), pMan->Get_box()))
			 {
			 }
			 else
			 {
				 ForwardMovemengt = g_Camera->getForward();
				 MoveRevise(PlayerPos, ForwardMovemengt, dt);
			 }
			 break;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
			 //_________\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
		 }
		

		 {
			 //floor panding
			 //switch (State_Floor)
			 //{
			 //case NONE2:
			 //{
				// BoundingBox box = pMap->GetFloorBox(0);
				// if (!CCollider::ISBOXHIT(this->Get_Box(), box) &&
				//	 !CCollider::ISBOXHIT(this->Get_Box(), pMap->GetFloorBox(1)) &&
				//	 !CCollider::ISBOXHIT(this->Get_Box(), pMap->GetFloorBox(2)) &&
				//	 !CCollider::ISBOXHIT(this->Get_Box(), pMap->GetFloorBox(3)))
				// {
				//	 float y = m_Position.y;

				//	 if (y > 20.0f)
				//	 {
				//		 XMVECTOR dir = { 0.0f,0.0f,1.0f };
				//		 XMVECTOR nowfacedir;
				//		 nowfacedir = Tool::GetNowDir(this->GetMatrixForWorld(), dir);
				//		 PlayerPos += nowfacedir * dt*5.0f;
				//		 y -= 5.0f*dt;
				//		 SDate.CurrentAnim = _NQJUMP;
				//	 }
				//	 else y = 0.0f;

				//	 PlayerPos = XMVectorSetY(PlayerPos, y);
				// }
				// break;
			 //}
			 //case FLOOR0:
				// if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(14)) &&
				//	 !CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(17)) && !CCollider::ISBOXHIT(this->Get_Box(), pMap->GetFloorBox(1)) &&
				//	 !CCollider::ISBOXHIT(this->Get_Sphere(), pMap->Get_OBBOX(2)) && !CCollider::ISBOXHIT(this->Get_Sphere(), pMap->Get_OBBOX(3)))
				// {
				//	 XMFLOAT3 p1 = { 0.0f,0.0f,-32.0f };
				//	 XMFLOAT3 p2 = { 0.0f,0.0f,this->GetPosition().z };
				//	 float distans = Tool::Distance_float(p1, p2);
				//	 float H = tanf(XMConvertToRadians(35.0f))*distans;

				//	 /*ForwardMovemengt = g_Camera->getForward();
				//	 MoveRevise(PlayerPos, ForwardMovemengt, dt/3);*/
				//	 PlayerPos = XMVectorSetY(PlayerPos, H);
				//	 //XMStoreFloat3(&m_Position, PlayerPos);
				// }
				// break;
			 //case FLOOR1:
				// PlayerPos = XMVectorSetY(PlayerPos, 25.8f);
				// break;
			 //case FLOOR2:

				// if (State_Collider != WALLBOX16)
				// {
				//	 CRenderer::Debug_show_v2[1] = 38;

				//	 XMFLOAT3 p1 = { 0.0f,0.0f,42.0f };
				//	 XMFLOAT3 p2 = { 0.0f,0.0f,this->GetPosition().z };
				//	 float distans = Tool::Distance_float(p1, p2);
				//	 float H = tanf(XMConvertToRadians(13.0f))*distans;
				//	 PlayerPos = XMVectorSetY(PlayerPos, H);
				// }
				// break;

			 //case FLOOR3:

				// if (State_Collider != WALLBOX15)
				// {
				//	 if (CCollider::ISBOXHIT(this->Get_Box(), pMap->GetFloorBox(3)))
				//	 {
				//		 XMFLOAT3 p1 = { 0.0f,0.0f,42.0f };
				//		 XMFLOAT3 p2 = { 0.0f,0.0f,this->GetPosition().z };
				//		 float distans = Tool::Distance_float(p1, p2);
				//		 float H = tanf(XMConvertToRadians(13.0f))*distans;

				//		 /*ForwardMovemengt = g_Camera->getForward();
				//		 MoveRevise(PlayerPos, ForwardMovemengt, dt);*/
				//		 PlayerPos = XMVectorSetY(PlayerPos, H);
				//	 }
				// }
				// break;
			 //}
		 }
	
	}
	//XMVECTOR Pl = PlayerPos;
	//Pl = XMVectorSetY(Pl, XMVectorGetY(Pl) + 8.0f+CRenderer::Debug_move_v3[0]);	//调整视角
	//Pl = XMVectorSetZ(Pl, XMVectorGetZ(Pl) + CRenderer::Debug_move_v3[1]);// 2.8
	////Pl = XMVectorSetX(Pl, XMVectorGetX(Pl) );	//调整视角
	//g_Camera->set(Pl);
	//g_Camera->Update(dt);
	//bool angleCtr = false;
	//if(!ZhunXSwitch)
	//if (CInput::GetKeyPress('K'))
	//	angleCtr = true;
	//if (!angleCtr&&SDate.CurrentAnim!= _SsangDH)
	//{
	//	Rot = XMVectorSetY(Rot, g_Camera->getangle());//按照角色向量Y轴旋转rot并赋值；
	//
	//	
	//	if(ZhunXSwitch)
	//	Rot= XMVectorSetX(Rot, (g_Camera->Get_AngleX())*-1.0f);
	//	else
	//	{
	//		Rot = XMVectorSetX(Rot, 0.0f);
	//	}
	//}
	//XMStoreFloat3(&m_Rotation, Rot);
	//XMStoreFloat3(&m_Position, PlayerPos);
	switch (State_Floor)
	{
	case NONE2:
	{
		BoundingBox box = pMap->GetFloorBox(0);
		if (!CCollider::ISBOXHIT(this->Get_Box(), box) &&
			!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetFloorBox(1)) &&
			!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetFloorBox(2)) &&
			!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetFloorBox(3)))
		{

			float y = m_Position.y;

			if (y > 20.0f)
			{
				SDate.JumpDownControl = true;

			
			}
			else
			{
				if (!SDate.JumpDownControl) PlayerPos = XMVectorSetY(PlayerPos, 0.0f);
				
			}
				

		}
		break;
	}
	case FLOOR0:
		if (!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(14)) &&
			!CCollider::ISBOXHIT(this->Get_Box(), pMap->GetWallBox(17)) && !CCollider::ISBOXHIT(this->Get_Box(), pMap->GetFloorBox(1)) &&
			!CCollider::ISBOXHIT(this->Get_Sphere(), pMap->Get_OBBOX(2)) && !CCollider::ISBOXHIT(this->Get_Sphere(), pMap->Get_OBBOX(3)))
		{
			XMFLOAT3 p1 = { 0.0f,0.0f,-32.0f };
			XMFLOAT3 p2 = { 0.0f,0.0f,this->GetPosition().z };
			float distans = Tool::Distance_float(p1, p2);
			float H = tanf(XMConvertToRadians(35.0f))*distans;

			/*ForwardMovemengt = g_Camera->getForward();
			MoveRevise(PlayerPos, ForwardMovemengt, dt/3);*/
			PlayerPos = XMVectorSetY(PlayerPos, H);
			//XMStoreFloat3(&m_Position, PlayerPos);
		}
		break;
	case FLOOR1:
		
		PlayerPos = XMVectorSetY(PlayerPos, 25.8f);
		break;
	case FLOOR2:

		if (State_Collider != WALLBOX16)
		{
			CRenderer::Debug_show_v2[1] = 38;

			XMFLOAT3 p1 = { 0.0f,0.0f,42.0f };
			XMFLOAT3 p2 = { 0.0f,0.0f,this->GetPosition().z };
			float distans = Tool::Distance_float(p1, p2);
			float H = tanf(XMConvertToRadians(13.0f))*distans;
			PlayerPos = XMVectorSetY(PlayerPos, H);
		}
		break;

	case FLOOR3:

		if (State_Collider != WALLBOX15)
		{
			if (CCollider::ISBOXHIT(this->Get_Box(), pMap->GetFloorBox(3)))
			{
				XMFLOAT3 p1 = { 0.0f,0.0f,42.0f };
				XMFLOAT3 p2 = { 0.0f,0.0f,this->GetPosition().z };
				float distans = Tool::Distance_float(p1, p2);
				float H = tanf(XMConvertToRadians(13.0f))*distans;

				/*ForwardMovemengt = g_Camera->getForward();
				MoveRevise(PlayerPos, ForwardMovemengt, dt);*/
				PlayerPos = XMVectorSetY(PlayerPos, H);
			}
		}
		break;
	}


	//anim 
	bool EquipmentMenuSwitch = !pui->GetEquipmentSwitch();
	if (!Huanzidancontrol&&!SDate.BeHurtAnimControl)
	{
		CFont* pF = CManager::GetScene()->GetGmeobjs<CFont>(FONT_ID);

		//shootting&&EquipmentMenuSwitch
		if (CInput::GetKeyPress(VK_RBUTTON) && EquipmentMenuSwitch || GamePad::IsPress(GamePad::Button::LEFT_TRIGGER) && EquipmentMenuSwitch)
			SDate.CurrentAnim = _miaozhun;
		else if (CInput::GetKeyTrigger('F') && EquipmentMenuSwitch&&m_WeaponType==WEAPON::Type::Gun || GamePad::IsTrigger(GamePad::Button::X) && EquipmentMenuSwitch&&m_WeaponType == WEAPON::Type::Gun)
		{
			std::unique_ptr<CAudioClip> huanzidan;
			huanzidan = std::make_unique<CAudioClip>();
			huanzidan->Load("asset/Music/shangtang.wav");
			huanzidan->Play(false);
			Huanzidancontrol = true;
		}
		else if (CInput::GetKeyTrigger('G') && EquipmentMenuSwitch || GamePad::IsTrigger(GamePad::Button::A) && EquipmentMenuSwitch)
		{
			UImanager3D* pUI = CManager::GetScene()->GetGmeobjs<UImanager3D>(UI_ID);
			
			XMVECTOR dir = { -1.0f,0.0f,0.0f };
			XMFLOAT3 rightdir;
			XMStoreFloat3(&rightdir, XMVector3Normalize(dir));

			XMVECTOR dir2 = { 0.0f,0.0f,1.0f };
			XMFLOAT3 fontdir;
			XMStoreFloat3(&fontdir, XMVector3Normalize(dir2));

			XMFLOAT3 raypos = { pUI->GetPosition().x,5.0f,pUI->GetPosition().z };
			Ray _ray(raypos, rightdir);
			XMFLOAT3 raypos2 = { pUI->GetGun2Pos().x,5.0f,pUI->GetGun2Pos().z };
			Ray _ray2(raypos2, rightdir);
			XMFLOAT3 raypos3 = { pUI->GetRedPos().x,5.0f,pUI->GetRedPos().z };
			Ray _ray3(raypos3, fontdir);
			XMFLOAT3 raypos4 = { pUI->GetHerbPos().x,5.0f,pUI->GetHerbPos().z };
			Ray _ray4(raypos4, fontdir);
			if (_ray.Hit(this->GetSphereBox()))
			{
				if (pF->GetNumDatePtr()->MoneySize >= 1000.0f)
				{
					pF->GetNumDatePtr()->MoneySize -= 1000.0f;
					pF->GetNumDatePtr()->BulleSize += 30.0f;
				}
			}
			else if(_ray2.Hit(this->GetSphereBox()))
			{
				float distance = Tool::Distance_float(raypos2, this->GetPosition());
				if (distance <= 10.0f)
				{
					if (pF->GetNumDatePtr()->MoneySize >= 1000.0f)
					{
						pF->GetNumDatePtr()->MoneySize -= 1000.0f;
						pF->GetNumDatePtr()->BulleSize += 30.0f;
					}
				}
			}
			else if (_ray3.Hit(this->GetSphereBox()))
			{
				float distance = Tool::Distance_float(raypos3, this->GetPosition());
				if (distance <= 10.0f)
				{
					if (pF->GetNumDatePtr()->MoneySize >= 500.0f)
					{
						if (pF->GetNumDatePtr()->YaocaoSize <=0.0f )
						{
							pui->AddEquipment(Equipment::YaoShui);
						}
						pF->GetNumDatePtr()->YaocaoSize += 1.0f;
						pF->GetNumDatePtr()->MoneySize -= 500.0f;
					}
				}
			}
			else if (_ray4.Hit(this->GetSphereBox()))
			{
				float distance = Tool::Distance_float(raypos4, this->GetPosition());
				if (distance <= 10.0f)
				{
					if (pF->GetNumDatePtr()->MoneySize >= 500.0f)
					{
						SDate.PhysicalBar = 294.8f;
						pF->GetNumDatePtr()->MoneySize -= 500.0f;
					}
				}
			}
		}
		else if (CInput::GetKeyTrigger(VK_SPACE)&&SDate.PhysicalBar>=100.0f&&EquipmentMenuSwitch || GamePad::IsTrigger(GamePad::Button::Y)&& SDate.PhysicalBar >= 100.0f&&EquipmentMenuSwitch)
		{
			SDate.JumpRunControl = true;
			std::unique_ptr<CAudioClip> pmusic;
			pmusic = std::make_unique<CAudioClip>();
			pmusic->Load("asset/Music/luoxia.wav");
			pmusic->Play(false);
		}
		else if (CInput::GetKeyTrigger(VK_MBUTTON)) { pui->SetEquipmentSwitch(); g_Camera->SetSunAmbient(COLOR(0.4f,0.4f,0.4f,0.4f)); }
		SNumber* pSNum = pF->GetNumDatePtr();
	
		switch (m_WeaponType)
		{
		case WEAPON::Type::knfie:
		{
			if (CInput::GetKeyTrigger(VK_LBUTTON)&&SDate.CurrentAnim == _miaozhun && EquipmentMenuSwitch || GamePad::IsTrigger(GamePad::Button::RIGHT_SHOULDER)&&SDate.CurrentAnim == _miaozhun && EquipmentMenuSwitch)
			{
				Ray ray = Ray::ScreenToRay(g_Camera, ZhunxPos.x + ZHunxWH / 2, ZhunxPos.y + ZHunxWH / 2);
				ZHunxWH += 20.0f;
				ZhunxPos.x -= 10.0f;
				ZhunxPos.y -= 10.0f;
				pModle->ResetTimer();
				sheji = true;
				std::unique_ptr<CAudioClip> msheji;
				msheji = std::make_unique<CAudioClip>();
				int pattern = PlayerManager::knifeAttackManger(ray, 15.0f);
				switch (pattern)
				{
				case 0:
					msheji->Load("asset/Music/airDao.wav");
					break;
				case 1:
					msheji->Load("asset/Music/nikuDao.wav");
					break;
				default:
					break;
				}
				msheji->Play(false);
			}
		}
			break;
		case WEAPON::Type::Gun:
		{
			if (CInput::GetKeyTrigger(VK_LBUTTON) && pSNum->Bulletcount >= 1.0f&&SDate.CurrentAnim == _miaozhun && EquipmentMenuSwitch || GamePad::IsTrigger(GamePad::Button::RIGHT_SHOULDER) && pSNum->Bulletcount >= 1.0f&&SDate.CurrentAnim == _miaozhun && EquipmentMenuSwitch)
			{
				pSNum->Bulletcount -= 1.0f;
				Ray ray = Ray::ScreenToRay(g_Camera, ZhunxPos.x + ZHunxWH / 2, ZhunxPos.y + ZHunxWH / 2);
				PlayerManager::AttackManger(ray);
				ZHunxWH += 20.0f;
				ZhunxPos.x -= 10.0f;
				ZhunxPos.y -= 10.0f;
				pModle->ResetTimer();
				sheji = true;
				std::unique_ptr<CAudioClip> msheji;
				msheji = std::make_unique<CAudioClip>();
				msheji->Load("asset/Music/sheji.wav");
				msheji->Play(false);

			}
		}
			break;
		default:
			break;
		}
	}
	
	if(sheji)
		SDate.CurrentAnim = _NAttack;
	else if (Huanzidancontrol) SDate.CurrentAnim == _Run ? SDate.CurrentAnim = _HZD1 : SDate.CurrentAnim = _HZD2;
	else if (SDate.BeHurtAnimControl)
	{
		switch (movieNum)
		{
		case LensOne:
			SDate.CurrentAnim = _SsangDH;
			break;
		case LensTwo:
			SDate.CurrentAnim = _NQdie;
			break;
		}
	}
	else if (SDate.JumpRunControl) SDate.CurrentAnim = _NQJunmpRun;
	if (SDate.JumpDownControl)
	{
		Huanzidancontrol = false;
		SDate.BeHurtAnimControl = false;
		SDate.JumpRunControl = false;
		SDate.CurrentAnim = _NQJUMP;
	}
	else
	{
		Sound.Jump = false;
	}
	
	/*if(m_Position.y>20.0f) 
	if (m_Position.x < -67.0f) SDate.CurrentAnim = _NQJumpStop;*/
	SetMyWeaponStatePattern(WEAPON::Pattern::UsingSate);
	if(!EquipmentMenuSwitch){ Tool::BlendRunUp(CameraViewShootControl, dt, 4.0f); }
	XMVECTOR camDirtarget;
	switch (SDate.CurrentAnim)
	{
	case _idie:
		jiaobu->Stop();
		moveStop = true;
		moveStop = EquipmentMenuSwitch;
		ZhunXSwitch = false;
		if (SDate.PhysicalBar <= 294.8f)  SDate.PhysicalBar += dt * 0.01f;
		break;
	case _Run:
		Tool::BlendRunDown(CameraViewShootControl,dt, 2.0f);
		jiaobu->Start();
		moveStop = true;
		moveStop = EquipmentMenuSwitch;
		ZhunXSwitch = false;
		if (SDate.HP <= 3.0f)
		{
			SDate.CurrentAnim = _SsangSate;
			AnimationSpeed = 0.75f;
		}
		break;
	case _miaozhun:
		Tool::BlendRunUp(CameraViewShootControl, dt, 4.0f);
		jiaobu->Stop();
		moveStop = false;
		ZhunXSwitch = true;
		FaceNumber = miaozhun;
		if (m_WeaponType == WEAPON::Type::knfie)
		{
			SDate.CurrentAnim = _NQDaomiaozhun;
			SetMyWeaponStatePattern(WEAPON::Pattern::AttackState);
		}
		break;
	case _NAttack:
		jiaobu->Stop();
		moveStop = false;
		ZhunXSwitch = true;
		if (m_WeaponType == WEAPON::Type::Gun)
		{
			if (!pModle->AiamFramManager(5.0f, _NAttack))
			{
				ZHunxWH = 45.0f;
				ZhunxPos.x = SCREEN_WIDTH / 2 + 50.0f;
				ZhunxPos.y = SCREEN_HEIGHT / 2;

			}
			else
			{
				ZhunxPos.x = SCREEN_WIDTH / 2 + 50.0f;
				ZhunxPos.y = SCREEN_HEIGHT / 2 + 10.0f;
				ZHunxWH = 25.0f;
			}
			if (pModle->AiamFramManager(31.0f, _NAttack))
			{
				sheji = false;
			}
		}
		else if (m_WeaponType == WEAPON::Type::knfie)
		{
			AnimationSpeed = 3.0f;
			SDate.CurrentAnim = _NQDaoattack;
			if (!pModle->AiamFramManager(5.0f, _NQDaoattack))
			{
				ZHunxWH = 45.0f;
				ZhunxPos.x = SCREEN_WIDTH / 2 - 200.0f;
				ZhunxPos.y = SCREEN_HEIGHT / 2+100.0f;

			}
			else
			{
				ZhunxPos.x = SCREEN_WIDTH / 2 -200.0f;
				ZhunxPos.y = SCREEN_HEIGHT / 2 + 110.0f;
				ZHunxWH = 25.0f;
			}
			if (pModle->AiamFramManager(24.0f, _NQDaoattack))
			{
				sheji = false;
			}
		}

		break;
	case _NQJUMP:
		jiaobu->Stop();
	{
		float y = m_Position.y;
		moveStop = false;
		ZhunXSwitch = false;
		AnimationSpeed = 1.5f;
		XMVECTOR dir = {-1.0f,0.0f,0.0f};
		if (m_Position.x > 0.0f) dir = { 1.0f,0.0f,0.0f };
		
		if(y>0.0f)
		PlayerPos += dir * dt*10.0f;
		y > 0.0f ? y -= 100.0f * dt : y = 0.0f;
		PlayerPos = XMVectorSetY(PlayerPos, y);
		if (!Sound.Jump)
		{
			std::unique_ptr<CAudioClip> pJump;
			pJump = std::make_unique<CAudioClip>();
			pJump->Load("asset/Music/luoxia.wav");
			pJump->Play(false);
			Sound.Jump = true;
		}
		if (pModle->AiamFramManager(90.0f, _NQJUMP))
		//if(pModle->PlayShot())
		{
			SDate.JumpDownControl = false;
			SDate.CurrentAnim = _idie;
			return;
		}
	}
		break;
	case _SsangDH:
		jiaobu->Stop();
		moveStop = false;
		ZhunXSwitch = false;
		{
			
			
			//dan du hui tingzhi buqian
			for (int i = 0; i < ENEMY_SIZE; i++)
			{
				CZombie_man* manptr = CManager::GetScene()->GetGmeobj<CZombie_man>(ENEMY_ID, i);
				if (manptr!=nullptr)
				{
					ZOMBIEDATE* zdata = manptr->GetStrutForData();
					if (zdata->AnimationShow)
					{
						XMFLOAT3 p1 = manptr->GetPosition();
						XMVECTOR oldface = { 0.0f,0.0f,1.0f};
						float deg = Tool::GetDegForP1ToP2(p1, m_Position, oldface);
						Tool::BlendRunUp(CameraRotBlend, dt, 2.0f);
						Rot = XMVectorSetY(Rot, deg*CameraRotBlend);
						g_Camera->SetcamYaw(deg*CameraRotBlend);
						XMVECTOR camtozombieDir = Tool::GetP1ToP2(p1, g_Camera->GetPosition());
						//Tool::BlendRunUp(CameraRotBlendZ, dt, 2.0f);
						camDirtarget = PlayerPos+camtozombieDir * 3.5f*CameraRotBlend;
						g_Camera->SetcamPitch(0.1f);
						XMFLOAT3 manpos;
						XMStoreFloat3(&manpos, XMLoadFloat3(&m_Position) +camtozombieDir * 3.0f);
						manptr->SetPosition(manpos);
						if (CameraRotBlend >= 1.0f)
						{
							XMFLOAT3 _manpos = { manpos.x,0.9f,manpos.z };
							manptr->SetPosition(_manpos);
							XMFLOAT3 _manrot = { -0.4f,manptr->GetRotation().y,manptr->GetRotation().z };
							manptr->SetRotation(_manrot);
							if (CameraRotBlendZ < 1.0f)
							{
								Tool::BlendRunUp(CameraRotBlendZ, dt, 1.0f+SDate.TouchNum/10.0f);
								CameraRotBlendZ2 = 1.0f;
								camDirtarget = XMVectorSetY(camDirtarget, -2.5f - 1.5f*CameraRotBlendZ);
								XMVECTOR left = { -1.0f,0.0f,0.0f };
								XMVECTOR Nowleft = Tool::GetNowDir(manptr->GetMatrixForWorld(), left);
								camDirtarget += Nowleft*(1.0f+3.0f*CameraRotBlendZ);
							}
							else if (CameraRotBlendZ2 > 0.0f)
							{
								Tool::BlendRunDown(CameraRotBlendZ2, dt, 1.0f+SDate.TouchNum/10.0f);
								camDirtarget = XMVectorSetY(camDirtarget, -2.5f - 1.5f*CameraRotBlendZ2);
								//if (CameraRotBlendZ2 == 0.0f) CameraRotBlendZ = 0.0f;
								XMVECTOR left = { -1.0f,0.0f,0.0f };
								XMVECTOR Nowleft = Tool::GetNowDir(manptr->GetMatrixForWorld(), left);
								camDirtarget += Nowleft * (1.0f + 3.0f*CameraRotBlendZ2);
							}
							else
							{
								CameraRotBlendZ = 0.0f;
							}
							
						}
					}
				}
			}
		
		}
		break;
	case _NQdie:
		jiaobu->Stop();
	{
		Tool::BlendRunUp(CameraRotaBlendZ3,dt,0.05f);
		moveStop = false;
		ZhunXSwitch = false;
		XMVECTOR Pl = PlayerPos;
		Pl = XMVectorSetY(Pl, XMVectorGetY(Pl) + 50.0f*CameraRotaBlendZ3);	//调整视角
		Pl = XMVectorSetZ(Pl, XMVectorGetZ(Pl));// 2.8
		XMVECTOR facedir = { 0.0f,0.0f,1.0f,0.0f };
		XMVECTOR dir = Tool::GetNowDir(GetMatrixForWorld(), facedir);

		XMVECTOR Cameramove = Pl + dir * 500.0f*CameraRotaBlendZ3;


		//g_Camera->SetcamPitch(-0.3f+1.3f*CameraRotaBlendZ3);
		float _blend = 10.0f*CameraRotaBlendZ3;
		if (_blend >= 1.0f) _blend = 1.0f;
		g_Camera->SetcamPitch(_blend);
		//Pl = XMVectorSetX(Pl, XMVectorGetX(Pl) );	//调整视角
		g_Camera->set(Cameramove);
	}
		break;
	case _HZD1:
		//jiaobu->Stop();
		jiaobu->Start();
		moveStop = true;
		moveStop = EquipmentMenuSwitch;
		ZhunXSwitch = false;
		if (pModle->AiamFramManager(24.0f, _HZD1))
		{
			CFont* pf = CManager::GetScene()->GetGmeobjs<CFont>(FONT_ID);
			SNumber* ps = pf->GetNumDatePtr();
			int count = ps->Bulletcount;
			if (count != 6.0f&&ps->BulleSize >=0.0f)
			{
				int cha = 6.0f - count;
				for (int i = 0; i < cha; i++)
				{
					if (ps->BulleSize >= 1.0f)
					{
						ps->BulleSize -= 1.0f;
						ps->Bulletcount += 1.0f;
					}
				}
			}
			Huanzidancontrol = false;
		}
		break;
	case _HZD2:
		jiaobu->Stop();
		moveStop = false;
		ZhunXSwitch = false;
		if (pModle->AiamFramManager(24.0f, _HZD2))
		{
			CFont* pf = CManager::GetScene()->GetGmeobjs<CFont>(FONT_ID);
			SNumber* ps = pf->GetNumDatePtr();
			int count = ps->Bulletcount;
			if (count != 6.0f&&ps->BulleSize >= 0.0f)
			{
				int cha = 6.0f - count;
				for (int i = 0; i < cha; i++)
				{
					if (ps->BulleSize >= 1.0f)
					{
						ps->BulleSize -= 1.0f;
						ps->Bulletcount += 1.0f;
					}
				}
			}
			Huanzidancontrol = false;
		}
		break;
	case _NQJunmpRun:
		jiaobu->Stop();
		moveStop = false;
		ZhunXSwitch = false;
		AnimationSpeed = 3.0f;
		{
			SDate.PhysicalBar > 0.0f ? SDate.PhysicalBar -= dt * 100.0f : SDate.PhysicalBar = 0.0f;
			XMFLOAT3 raydir = {0.0f,0.0f,0.0f};
			XMStoreFloat3(&raydir, -XMVector3Normalize( nowface));
			Ray ray(m_Position, raydir);
			if(!CCollider::MapCollider(ray,this->GetSphereBox(5.0f))) PlayerPos -= nowface * dt*700.0f;
			if (pModle->AiamFramManager(50.0f, _NQJunmpRun))
			{
				SDate.JumpRunControl = false;
			}
		}
		break;
	}

	//end move
	if (!SDate.BeHurtAnimControl&&!SDate.JumpDownControl)
	{
		XMVECTOR nowleftDir = Tool::GetNowDir(this->XMGet_WorldMatrix(),LeftDir);
		XMVECTOR Pl = PlayerPos+nowleftDir*60.0f*CameraViewShootControl;
		Pl = XMVectorSetY(Pl, XMVectorGetY(Pl) + 8.0f);	//调整视角
		//Pl = XMVectorSetX(Pl, XMVectorGetX(Pl));	//调整视角
		//Pl = XMVectorSetZ(Pl, XMVectorGetZ(Pl));// 2.8
		g_Camera->set(Pl);
	}
	else if (SDate.JumpDownControl)
	{
		XMVECTOR Pl = PlayerPos;
		Pl = XMVectorSetY(Pl, XMVectorGetY(Pl)+8.0f);	//调整视角
		Pl = XMVectorSetZ(Pl, XMVectorGetZ(Pl));// 2.8
		//g_Camera->SetcamPitch(CRenderer::Debug_move_v2[1]);
		XMVECTOR camtaeget = Pl + pModle->GetBonesTransformPos(12)*0.05f;
		g_Camera->set(camtaeget);
	}
	else
	{
		if (SDate.CurrentAnim != _NQdie)
		{
			XMVECTOR Pl = camDirtarget;
			Pl = XMVectorSetY(Pl, XMVectorGetY(Pl) + 12.0f);	//调整视角
			Pl = XMVectorSetZ(Pl, XMVectorGetZ(Pl));// 2.8
			g_Camera->set(Pl);
		}
	}
	g_Camera->Update(dt);
	bool angleCtr = false;
	if (!ZhunXSwitch)
		if (CInput::GetKeyPress('K'))
			angleCtr = true;
	if (!angleCtr&&SDate.CurrentAnim != _SsangDH&&SDate.CurrentAnim!=_NQJUMP)
	{
		Rot = XMVectorSetY(Rot, g_Camera->getangle());//按照角色向量Y轴旋转rot并赋值；


		if (ZhunXSwitch)
			Rot = XMVectorSetX(Rot, (g_Camera->Get_AngleX())*-1.0f);
		else
		{
			Rot = XMVectorSetX(Rot, 0.0f);
		}
	}
	XMStoreFloat3(&m_Rotation, Rot);
	XMStoreFloat3(&m_Position, PlayerPos);

	assert(pE);
	if (pE != nullptr)
	{
		if (ZhunXSwitch)
		{
			Ray ray = Ray::ScreenToRay(g_Camera, ZhunxPos.x + ZHunxWH / 2, ZhunxPos.y + ZHunxWH / 2);
			if (ray.Hit(pE->Get_box()))
			{
				ZhunxColor = 1.0f;
			}
			else if (ray.Hit(pMan->Get_box()))
			{
				ZhunxColor = 1.0f;
			}
			else if (ray.Hit(pMan->Get_HeadBox()))
			{
				ZhunxColor = 1.0f;
			}
			else
			{
				ZhunxColor = 0.5f;
			}
		}
		else
		{
			ZhunxColor = 0.5f;
		}
	}

	CRenderer::DeBug_show_v3[0] = m_Position.x;
	CRenderer::DeBug_show_v3[1] = m_Position.y;
	CRenderer::DeBug_show_v3[2] = m_Position.z;
	CRenderer::Debug_show_v2[0] = m_Position.y;
	pModle->Update(dt, AnimationSpeed);
}

void CP0::Draw() 
{
	XMMATRIX rotationX =
		XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);//转矩阵全部
	XMMATRIX world;
	XMMATRIX world2;

	world = rotationX;
	world2 = rotationX;
	switch (FaceNumber)
	{
	case W:
		rotBlend2 = 0.0;
		world *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(180)*rotBlend*Left_Right, 0.0f);
		break;
	case S:
		world *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(180)*rotBlend*Left_Right, 0.0f);
		break;
	case A:
		world *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(180) + XMConvertToRadians(90)*rotBlend1, 0.0f);
	case D:
		world *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(180)*1.0f*Left_Right + XMConvertToRadians(90)*rotBlend2, 0.0f);
		//world *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(90)*rotBlend2, 0.0f);
		break;
	case X:
		world *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(90)*rotBlend, 0.0f);
		break;
	case Y:
		world *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(-90)*rotBlend, 0.0f);
		break;
	case miaozhun:
		world *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(180), 0.0f);
		break;
	}
	//PlayerManager::CotrolMove(xiputnum, world, controlBlend);

	world *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMStoreFloat4x4(&WorldMartix,world);
	XMStoreFloat4x4(&m_WorldMatirx, world);

	//pModle->Render(world, SDate.CurrentAnim);
	pModle->WeaponRender(world, SDate.CurrentAnim);


	//test
	/*XMFLOAT3 pos;
	Tool::DeBugMoveV3(pos);
	XMVECTOR pos2;
	pos2 = XMLoadFloat3(&pos);
	XMFLOAT3 poss;
	XMStoreFloat3(&poss, pos2);
	XMFLOAT3 rot;
	Tool::DeBugMoveV3two(rot);
	world2 = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
	world2 *= XMMatrixScaling(CRenderer::Debug_move_v2[0], CRenderer::Debug_move_v2[0], CRenderer::Debug_move_v2[0]);*/


	m_Weapon_Knife->Update(m_WeaponType,m_WeaponPattern, world, pModle);



	

	//
	XMMATRIX linew;
	linew = XMMatrixRotationRollPitchYaw(XMConvertToRadians(90.0f), 0.0f, 0.0f);
	linew *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	linew *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z+1.0f);
	XMStoreFloat4x4(&boxMartix, linew);
}

  void CP0::DrawShadow() 
{
	  CShadow* pShadow = CManager::GetScene()->GetGmeobjs<CShadow>(ShadowLight_ID);

	  CRenderer::SetViewMatrix(&pShadow->GetViewMatrix());
	  CRenderer::SetProjectionMatrix(&pShadow->GetProjectionMatrix());

	  pModle->WeaponRender(GetMatrixForWorld(), SDate.CurrentAnim);

}

void CP0::MoveRevise(XMVECTOR & PlayerPos, XMVECTOR & ForwardMovement,float dt)
{
	ForwardMovement = XMVector3Normalize(ForwardMovement);

	XMFLOAT3 Dir;
	XMStoreFloat3(&Dir, ForwardMovement);
	Ray ray(this->GetPosition(), Dir);
	CMap* pMap = CManager::GetScene()->GetGmeobjs<CMap>(MAP_ID);
	//for (int i = 0; i < 19; i++)
	//{
	//	 if (ray.Hit(pMap->GetWallBox(i)) && (this->Get_Sphere().Contains(pMap->GetWallBox(i))))
	//	 {
	//		 State_Collider = COLLIDER(i+1); 
	//		 ismove = false;
	//	 }
	//	
	//}
	BoundingSphere saigo;
	saigo.Center = { 2.0f,0.0f,430.0f };
	saigo.Radius = 20.0f;
	
			 if (ray.Hit(pMap->GetWallBox(0)) && (this->Get_Sphere().Contains(pMap->GetWallBox(0)))) {
				State_Collider = WALLBOX0; 
			}
			else if (ray.Hit(pMap->GetWallBox(1))&& (this->Get_Sphere().Contains(pMap->GetWallBox(1))))		{ State_Collider = WALLBOX1; }
			else if (ray.Hit(pMap->GetWallBox(2)) && (this->Get_Sphere().Contains(pMap->GetWallBox(2))))		{ State_Collider = WALLBOX2; }
			else if (ray.Hit(pMap->GetWallBox(3)) && (this->Get_Sphere().Contains(pMap->GetWallBox(3))))		{ State_Collider = WALLBOX3; }
			else if (ray.Hit(pMap->GetWallBox(4)) && (this->Get_Sphere().Contains(pMap->GetWallBox(4))))		{ State_Collider = WALLBOX4; }
			else if (ray.Hit(pMap->GetWallBox(5)) && (this->Get_Sphere().Contains(pMap->GetWallBox(5))))		{ State_Collider = WALLBOX5; }
			else if (ray.Hit(pMap->GetWallBox(6)) && (this->Get_Sphere().Contains(pMap->GetWallBox(6))))		{ State_Collider = WALLBOX6; }
			else if (ray.Hit(pMap->GetWallBox(7)) && (this->Get_Sphere().Contains(pMap->GetWallBox(7))))		{ State_Collider = WALLBOX7; }
			else if (ray.Hit(pMap->GetWallBox(8)) && (this->Get_Sphere().Contains(pMap->GetWallBox(8))))		{ State_Collider = WALLBOX8; }
			else if (ray.Hit(pMap->GetWallBox(9)) && (this->Get_Sphere().Contains(pMap->GetWallBox(9))))		{ State_Collider = WALLBOX9; }
			else if (ray.Hit(pMap->GetWallBox(10)) && (this->Get_Sphere().Contains(pMap->GetWallBox(10))))	{ State_Collider = WALLBOX10; }
			else if (ray.Hit(pMap->GetWallBox(11)) && (this->Get_Sphere().Contains(pMap->GetWallBox(11)))) { State_Collider = WALLBOX11; }
			else if (ray.Hit(pMap->GetWallBox(12)) && (this->Get_Sphere().Contains(pMap->GetWallBox(12)))) { State_Collider = WALLBOX12; }
			else if (ray.Hit(pMap->GetWallBox(13)) && (this->Get_Sphere().Contains(pMap->GetWallBox(13)))&&State_Floor!=FLOOR2) { State_Collider = WALLBOX13;  }
			else if (ray.Hit(pMap->GetWallBox(14)) && (this->Get_Sphere().Contains(pMap->GetWallBox(14))) && State_Floor != FLOOR3) { State_Collider = WALLBOX14; }
			else if (ray.Hit(pMap->GetWallBox(15)) && (this->Get_Sphere().Contains(pMap->GetWallBox(15)))) { State_Collider = WALLBOX15;  }
			else if (ray.Hit(pMap->GetWallBox(16)) && (this->Get_Sphere().Contains(pMap->GetWallBox(16)))) { State_Collider = WALLBOX16;  }
			else if (ray.Hit(pMap->GetWallBox(17)) && (this->Get_Sphere().Contains(pMap->GetWallBox(17)))) { State_Collider = WALLBOX17; }
			else if (ray.Hit(pMap->GetWallBox(18)) && (this->Get_Sphere().Contains(pMap->GetWallBox(18)))) { State_Collider = WALLBOX18; }
			else if (ray.Hit(pMap->Get_OBBOX(0)) && (this->Get_Sphere().Contains(pMap->Get_OBBOX(0)))) { State_Collider = WALLBOX19; }
			else if (ray.Hit(pMap->Get_OBBOX(1)) && (this->Get_Sphere().Contains(pMap->Get_OBBOX(1)))) {State_Collider = WALLBOX20; }
			else if (ray.Hit(pMap->Get_OBBOX(2)) && (this->Get_Sphere().Contains(pMap->Get_OBBOX(2)))) { State_Collider = WALLBOX21; }
			else if (ray.Hit(pMap->Get_OBBOX(3)) && (this->Get_Sphere().Contains(pMap->Get_OBBOX(3)))) { State_Collider = WALLBOX22; }
			else if (ray.Hit(pMap->Get_OBBOX(4)) && (this->Get_Sphere().Contains(pMap->Get_OBBOX(4)))) { State_Collider = WALLBOX23; }
			else if (ray.Hit(pMap->Get_OBBOX(5)) && (this->Get_Sphere().Contains(pMap->Get_OBBOX(5)))) { State_Collider = WALLBOX24; }
			else if (ray.Hit(pMap->Get_OBBOX(6)) && (this->Get_Sphere().Contains(pMap->Get_OBBOX(6)))) { State_Collider = WALLBOX25; }
			else if (ray.Hit(pMap->Get_OBBOX(9)) && (this->Get_Sphere().Contains(pMap->Get_OBBOX(9)))) { State_Collider = WALLBOX26; }
			else if (ray.Hit(pMap->Get_OBBOX(10)) && (this->Get_Sphere().Contains(pMap->Get_OBBOX(10)))) { State_Collider = WALLBOX27; }
			else if (ray.Hit(pMap->Get_OBBOX(11)) && (this->Get_Sphere().Contains(pMap->Get_OBBOX(11)))) { State_Collider = WALLBOX28; }
			else if (ray.Hit(pMap->Get_OBBOX(12)) && (this->Get_Sphere().Contains(pMap->Get_OBBOX(12)))) { State_Collider = WALLBOX29; }
			else if (ray.Hit(pMap->Get_OBBOX(13)) && (this->Get_Sphere().Contains(pMap->Get_OBBOX(13)))) { State_Collider = WALLBOX30; }
			else if (ray.Hit(pMap->Get_OBBOX(13)) && (this->Get_Sphere().Contains(pMap->Get_OBBOX(13)))) { State_Collider = WALLBOX30; }
			else if (ray.Hit(saigo) && (this->Get_Sphere().Contains(saigo))) {  }
			else
			 {
			
				 if (SDate.HP > 3.0f)
				 {
					 PlayerPos += ForwardMovement * dt * P0SP;
				 }
				 else  PlayerPos += ForwardMovement * dt * P0SPSPEEDDOWN;
			 }
	//if(ismove)PlayerPos += ForwardMovement * dt * P0SP;
}

BoundingBox CP0::Get_Box()
{
	BoundingBox box;
	SDate.box.Transform(box, XMLoadFloat4x4(&boxMartix));
	return box;
}

BoundingSphere CP0::Get_Sphere()
{
	BoundingSphere Sp;
	Sp.Center = m_Position;
	Sp.Radius = 1.0f;
	return Sp;
}


