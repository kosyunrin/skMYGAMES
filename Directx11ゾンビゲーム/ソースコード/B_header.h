#pragma once
#include"main.h"
#include "renderer.h"
#include"audio_clip.h"
#include"CLight.h"
#include"StaticModel.h"
#include"FuTuAnimation.h"
#include"skinnedModel.h"
#include"CObjPhySics.h"
#include"CStaticmodle.h"
#include"CAx.h";
#include"AStarPathFinding.h"
#include"CSkinnedfbxanim.h"
#include"CPolygon.h"
#include"Timer.h"
//#include"FSM_AI.h"
#include"BET.h"
#include"game_object.h"
#include"Cbullet.h"
#include"CShadow.h"
#include"camera.h"
#include"CP0.h"
#include"CMap.h"
#include "CBlock.h"
#include"CZombie_man.h"
#include"CCameraOne.h"
#include "CPlayer.h"
#include"skyBox.h"
#include"field.h"
#include"CmeshField.h"
#include "SoldierHouseRed.h"
#include"SoldierHouseBlue.h"
#include"GameUI.h"
#include"BulletBule.h"
#include"CEnemy.h"
#include"CArmy.h"
#include "CRedArmy.h"
#include "UImanager3D.h"
#include"Friend.h"
#include"CWorld.h"
#include "CBlood.h"
#include "CFont.h"
#include"Scene.h"
#include"manager.h"
#include"input.h"
#include"GamePad.h"

using namespace Input;
#define CamPosH 20.0f
#define CamRotX  70.0f
#define CamMoveSpeed 20.0f
//#define redBulletSpeed 10.0f
#define EnemyAttackRange 10.0f
#define p0TAMA_SPEED          15.0f
#define XBTAMA_SPEED          10.0f


struct Ray
{
	Ray() : origin(0.0f,0.0f,0.0f), direction(0.0f, 0.0f, 1.0f) {}
	Ray(const XMFLOAT3& origin, const XMFLOAT3& direction) : origin(origin)
	{
		// …‰œﬂµƒdirection≥§∂»±ÿ–ÅE™1.0f£¨ŒÛ≤˚⁄1e-5fƒ⁄
	
		XMVECTOR dirLength = XMVector3Length(XMLoadFloat3(&direction));
		XMVECTOR error = XMVectorAbs(dirLength - XMVectorSplatOne());
		assert(XMVector3Less(error, XMVectorReplicate(1e-5f)));

		XMStoreFloat3(&this->direction, XMVector3Normalize(XMLoadFloat3(&direction)));
	}

	static Ray ScreenToRay(const CCamera* camera, float screenX, float screenY)
	{
		// ******************
	// Ω⁄—°◊‘DirectX::XMVector3Unproject∫Ø ˝£¨≤¢ °¬‘¡À¥” ¿ΩÁ◊¯±ÅEµµΩæ÷≤ø◊¯±ÅEµµƒ±‰ªª
	//

	// Ω´∆¡ƒª◊¯±ÅE„¥” ”ø⁄±‰ªªªÿNDC◊¯±ÅEµ
		static const XMVECTORF32 D = { { { -1.0f, 1.0f, 0.0f, 0.0f } } };
		XMVECTOR V = XMVectorSet(screenX, screenY, 0.0f, 1.0f);
		D3D11_VIEWPORT viewPort = camera->GetViewPort();

		XMVECTOR Scale = XMVectorSet(viewPort.Width * 0.5f, -viewPort.Height * 0.5f, viewPort.MaxDepth - viewPort.MinDepth, 1.0f);
		Scale = XMVectorReciprocal(Scale);

		XMVECTOR Offset = XMVectorSet(-viewPort.TopLeftX, -viewPort.TopLeftY, -viewPort.MinDepth, 0.0f);
		Offset = XMVectorMultiplyAdd(Scale, Offset, D.v);

		// ¥”NDC◊¯±ÅEµ±‰ªªªÿ ¿ΩÁ◊¯±ÅEµ
		XMMATRIX Transform = XMMatrixMultiply(camera->GetViewXM(), camera->GetProjXM());
		Transform = XMMatrixInverse(nullptr, Transform);

		XMVECTOR Target = XMVectorMultiplyAdd(V, Scale, Offset);
		Target = XMVector3TransformCoord(Target, Transform);

		// «Û≥ˆ…‰œﬂ
		XMFLOAT3 direction;
		XMStoreFloat3(&direction, XMVector3Normalize(Target - camera->GetPositionXM()));
		return Ray(camera->GetPosition(), direction);
	}
	static Ray ScreenToRay( CCameraOne* camera, float screenX, float screenY)
	{
		// ******************
	// Ω⁄—°◊‘DirectX::XMVector3Unproject∫Ø ˝£¨≤¢ °¬‘¡À¥” ¿ΩÁ◊¯±ÅEµµΩæ÷≤ø◊¯±ÅEµµƒ±‰ªª
	//

	// Ω´∆¡ƒª◊¯±ÅE„¥” ”ø⁄±‰ªªªÿNDC◊¯±ÅEµ
		static const XMVECTORF32 D = { { { -1.0f, 1.0f, 0.0f, 0.0f } } };
		XMVECTOR V = XMVectorSet(screenX, screenY, 0.0f, 1.0f);
		D3D11_VIEWPORT viewPort = camera->Get_Viewport();

		XMVECTOR Scale = XMVectorSet(viewPort.Width * 0.5f, -viewPort.Height * 0.5f, viewPort.MaxDepth - viewPort.MinDepth, 1.0f);
		Scale = XMVectorReciprocal(Scale);

		XMVECTOR Offset = XMVectorSet(-viewPort.TopLeftX, -viewPort.TopLeftY, -viewPort.MinDepth, 0.0f);
		Offset = XMVectorMultiplyAdd(Scale, Offset, D.v);

		// ¥”NDC◊¯±ÅEµ±‰ªªªÿ ¿ΩÁ◊¯±ÅEµ
		XMMATRIX Transform = XMMatrixMultiply(camera->get_VIEWMatrix(), camera->Get_ProMatrix());
		Transform = XMMatrixInverse(nullptr, Transform);

		XMVECTOR Target = XMVectorMultiplyAdd(V, Scale, Offset);
		Target = XMVector3TransformCoord(Target, Transform);

		// «Û≥ˆ…‰œﬂ
		XMFLOAT3 direction;
		XMStoreFloat3(&direction, XMVector3Normalize(Target - camera->Get_PosXM()));
		return Ray(camera->GetPosition(), direction);
	}

	bool Hit(const BoundingBox& box, float* pOutDist = nullptr, float maxDist = FLT_MAX)
	{
		float dist;
		bool res = box.Intersects(XMLoadFloat3(&origin), XMLoadFloat3(&direction), dist);
		if (pOutDist)
			*pOutDist = dist;
		return dist > maxDist ? false : res;
	}
	bool Hit(const BoundingOrientedBox& box, float* pOutDist = nullptr, float maxDist = FLT_MAX)
	{
		float dist;
		bool res = box.Intersects(XMLoadFloat3(&origin), XMLoadFloat3(&direction), dist);
		if (pOutDist)
			*pOutDist = dist;
		return dist > maxDist ? false : res;
	}
	bool Hit(const BoundingSphere& sphere, float* pOutDist = nullptr, float maxDist = FLT_MAX)
	{
		float dist;
		bool res = sphere.Intersects(XMLoadFloat3(&origin), XMLoadFloat3(&direction), dist);
		if (pOutDist)
			*pOutDist = dist;
		return dist > maxDist ? false : res;
	}
	bool XM_CALLCONV Hit(FXMVECTOR V0, FXMVECTOR V1, FXMVECTOR V2, float* pOutDist = nullptr, float maxDist = FLT_MAX)
	{
		float dist;
		bool res = TriangleTests::Intersects(XMLoadFloat3(&origin), XMLoadFloat3(&direction), V0, V1, V2, dist);
		if (pOutDist)
			*pOutDist = dist;
		return dist > maxDist ? false : res;
	}

	XMFLOAT3 origin;		// …‰œﬂ‘≠µÅE
	XMFLOAT3 direction;	// µ•Œª∑ΩœÚœÚ¡ø
};

class MoveCharactersManager
{
public:
	static void Lookat(XMFLOAT3& rot,XMVECTOR direct,XMFLOAT4X4 Rmarix)
	{
		XMVECTOR down = { 0.0f,0.0f,-1.0f };
		XMVECTOR nowface = XMVector3TransformNormal(down, XMLoadFloat4x4(&Rmarix));
		float Radian = XMVectorGetY(XMVector3AngleBetweenVectors(nowface, direct));
		if (XMVectorGetY(XMVector3Cross(direct, nowface)) > 0.0f)
		{
			rot.y -= Radian;
		}
		else
		{
			rot.y += Radian;
		}
	}
	static void PlayerLookat(XMVECTOR nextFaceDirection,float& 
	radians,XMFLOAT4X4 Rmmarix)
	{
		XMVECTOR down = { 0.0f,0.0f,-1.0f };
		XMVECTOR nowface = XMVector3TransformNormal(down, XMLoadFloat4x4(&Rmmarix));
		float Radian = XMVectorGetY(XMVector3AngleBetweenVectors(nowface, nextFaceDirection));
		if (XMVectorGetY(XMVector3Cross(nextFaceDirection, nowface)) > 0.0f)
		{
			//m_rotation.y -= Radian;
			radians = -Radian;
		}
		else
		{
			//m_rotation.y += Radian;
			radians = Radian;
		}

	}
	static void PlayerMove(XMFLOAT3 &m_pos,XMFLOAT3 &m_rotation,XMFLOAT3 moveDir,
							XMFLOAT4X4 Rxmmraix
							,int Distance,
							float rotSpeed,float moveSpeed,float& rotationcount, 
							float& newraidans,
							float dt,
							bool &isMove,
							bool isenemy,
							float attackRange
							)
	{
		XMVECTOR down = { 0.0f,0.0f,-1.0f };
		//strat
		XMVECTOR m_posx = XMLoadFloat3(&m_pos);
		//rotation move//
		/*if (m_newrotation.y >= 0.0f)
		{
			if(FBSnew> FBSold)
			if ((m_rotation.y / m_newrotation.y) < 1.0f)
				{
					rotationcount += rotSpeed;
					m_rotation.y += rotationcount;
				}
			else
			{
				m_rotation.y = m_newrotation.y;
				rotationcount = 0.0f;
				FBSold = fabs(m_rotation.y);
			}
		}
		else
			{
				if ((m_rotation.y / m_newrotation.y) < 1.0f)
				{
					rotationcount += rotSpeed;
					m_rotation.y -= rotationcount;
				}
				else
				{
					m_rotation.y = m_newrotation.y;
					rotationcount = 0.0f;
				}
			}*/
		float FBSradians = fabs(newraidans);
		if (FBSradians > 0.0f)
		{
			rotationcount += rotSpeed *dt;
			if (FBSradians > rotationcount)
			{
				if (newraidans >= 0.0f)
					m_rotation.y += rotSpeed *dt;
				else { m_rotation.y -= rotSpeed *dt; }
			}
			else
			{
				rotationcount = 0.0f;
				newraidans = 0.0f;
			}
		}
		///

		//posmove//
		if (!isenemy)
		{
			XMVECTOR fangxiangV;
			fangxiangV = XMVector3Normalize(XMLoadFloat3(&moveDir));
			m_posx += fangxiangV * moveSpeed*dt;
			XMStoreFloat3(&m_pos, m_posx);
			//
			//end
			if (Distance <= 0)
			{
				isMove = false;
			}
		}
		else
		{
			if (Distance > attackRange)
			{
				XMVECTOR fangxiangV;
				fangxiangV = XMVector3Normalize(XMLoadFloat3(&moveDir));
				m_posx += fangxiangV * moveSpeed*dt;
				XMStoreFloat3(&m_pos, m_posx);
				//
			}
			else
			{
				isMove = false;
			}
		}
	}
	static bool ismove(XMFLOAT3 &moveDirection, XMFLOAT3& PointOI,XMFLOAT3 m_Pos,
					  XMFLOAT4X4 Rmaix,float &radians,bool& isenemy, int& ID,int& outTarget)
	{
		if (CInput::GetKeyTrigger(VK_RBUTTON))
		{
			XMFLOAT2 mousPos;
			mousPos = XMFLOAT2(CInput::GetmouseX(), CInput::GetmouseY());
			CCamera* p_camera = CManager::GetScene()->GetGmeobjs<CCamera>(_Camera);
			Ray ray = Ray::ScreenToRay(p_camera, mousPos.x, mousPos.y);// ¿ΩÁ•ﬁ•»•ÅEØ•π…‰æÄ§Ú”ãÀÅE

			outTarget = -1;
			//sienemy
			if (outTarget < 0)
			{
				for (int i = 0; i < 2; i++)
				{
					CBlueArmy* pBarmy = CManager::GetScene()->GetGmeobj<CBlueArmy>(5, i);
					if (pBarmy != nullptr)
					{
						BARMYDATE *sBadte = pBarmy->GetsBdate();
						float d = 0.0f;
						BoundingOrientedBox asd;
						//BoundingOrientedBox::CreateFromBoundingBox(asd, sBadte->ABox);
						asd = pBarmy->GetOBB(pBarmy->GetRotation());
						//asdddd.Intersects(asd, sddd);
						if (pBarmy->GetsBdate()->life > 0)
						{
							/*CPlayer* pPlayer = CManager::GetScene()->GetGmeobjs<CPlayer>(_Cplayer);
							XMVECTOR asdcenter = XMLoadFloat3(&asd.Center);
							XMVECTOR dir = XMVector3Normalize(XMLoadFloat3(&pPlayer->GetPosition()) - asdcenter);
							asdcenter += dir * 1.0f;
							XMStoreFloat3(&asd.Center, asdcenter);*/
							//asd.Center.z += 1.0f;
							if (ray.Hit(asd))
								//if (asd.Intersects(XMLoadFloat3(&ray.origin), XMLoadFloat3(&ray.direction), d))
							{
								isenemy = true;
								ID = i;
								outTarget = Tama_BlueXB;
							}
							else
							{
								isenemy = false;
							}
						}
						else isenemy = false;
					}
				}
			}
		   if (outTarget < 0)
			{
					SoldierHouseBlue* pHouse = CManager::GetScene()->GetGmeobjs<SoldierHouseBlue>(7);
					if (pHouse != nullptr)
					{
						House* shouse = pHouse->GetDate_house();
						float d = 0.0f;
						BoundingOrientedBox asd;
						BoundingOrientedBox::CreateFromBoundingBox(asd, shouse->ABOX);
						if (shouse->HP > 0)
						{
							//asd.Center.z += 1.0f;
							if (ray.Hit(asd, &d))
							{
								isenemy = true;
								outTarget = Tama_BlueHouse;
							}
							else
							{
								isenemy = false;
							}
						}
						else isenemy = false;
					}
			}




			//jiao dian and dir
			XMVECTOR moveDirXM = { 0.0f,0.0f,0.0f };
			//XMFLOAT3 PointOI = { 0.0f,0.0f,0.0f };
			PointOI = Tool::Intersection_PlaneTo_ray(ray.origin, ray.direction);
			//get move jiaodian
			moveDirXM = XMLoadFloat3(&PointOI) - XMLoadFloat3(&m_Pos);
			XMStoreFloat3(&moveDirection, moveDirXM);
			//get moveDir
			//setchange angle
			MoveCharactersManager::PlayerLookat(moveDirXM,radians,Rmaix);
			return true;
		}
		return false;
	}
};
class CCollider
{
public:
	static bool ClientPos(XMFLOAT2 mousePos)
	{
		if (mousePos.y <= 0 || mousePos.y >= 1080-32 ||
			mousePos.x <= 0 || mousePos.x >= 1920-9)
			return true;
		else
			return false;
	}
	static bool BoxCirece(XMFLOAT2 cPoint, XMFLOAT2 p1, XMFLOAT2 p3)
	{
		bool blResult = (cPoint.x >= p1.x && cPoint.x <= p3.x) && (cPoint.y >= p1.y && cPoint.y <= p3.y);
		return blResult;
	}
	static bool ISBOXHIT(BoundingBox p1, BoundingBox p2)
	{
		if (p1.Contains(p2))
			return true;
			return false;
	}
	static bool ISBOXHIT(BoundingSphere p1, BoundingBox p2)
	{
		if (p1.Contains(p2))
			return true;
		return false;
	}
	static bool ISBOXHIT(BoundingSphere p1, BoundingOrientedBox p2)
	{
		if (p1.Contains(p2))
			return true;
		return false;
	}
	static bool ISBOXHIT(BoundingSphere p1, BoundingSphere p2)
	{
		if (p1.Contains(p2))
			return true;
		return false;
	}
	static bool ISTriangle(Ray _ray, CStaticmodle* pmode,XMMATRIX world)
	{
		XMVECTOR V[3];
		
		std::vector<SStaticMode*> m_mesh;
		m_mesh = pmode->GetSkinnedMesh();
		for (int index = 0; index < m_mesh.size(); index++)
		{
			SStaticMode* mesh = m_mesh[index];

			for (UINT g = 0; g < mesh->indices.size()/3; g++)
			{
				DWORD number = mesh->indices[g];
				DWORD number1 = mesh->indices[g+1];
				DWORD number2 = mesh->indices[g+2];
				V[0] = XMVector3TransformCoord
				(XMLoadFloat3(&mesh->vs[number].Position), world);
				V[1] = XMVector3TransformCoord
				(XMLoadFloat3(&mesh->vs[number1].Position), world);
				V[2] = XMVector3TransformCoord
				(XMLoadFloat3(&mesh->vs[number2].Position), world);
				
			}
		}
		if (_ray.Hit(V[0], V[1], V[2]))
			return true;
		
		return false;
	}
	static BoundingSphere  GetShere(XMFLOAT3 pos, float size)
	{
		BoundingSphere _s;
		_s.Center = pos;
		_s.Radius = size;
		return _s;
	}
	static bool MapCollider(Ray ray,BoundingSphere sphereBox)
	{
		CMap* pmap = CManager::GetScene()->GetGmeobjs<CMap>(MAP_ID);
		if (pmap != nullptr)
		{
			SBOX sbox = pmap->GetBlock();
			for (int i = 0; i < sbox.ABOX.size(); i++)
			{
				BoundingBox abox = sbox.ABOX[i];
				if (ray.Hit(abox) && CCollider::ISBOXHIT(sphereBox, abox)) return true;
			}
			for (int x = 0; x < sbox.OBOX.size(); x++)
			{
				BoundingOrientedBox obox = sbox.OBOX[x];
				if (ray.Hit(obox) && CCollider::ISBOXHIT(sphereBox, obox)) return true;
			}
		}
		return false;
	}
	//static void 
};
class CCreate
{
public:
	static void CreateBox(BoundingBox &out, XMFLOAT3 Vmax, XMFLOAT3 Vmin)
	{
		XMVECTOR VMIN = XMLoadFloat3(&Vmin);
		XMVECTOR VMAX = XMLoadFloat3(&Vmax);
		BoundingBox::CreateFromPoints(out, VMAX,VMIN);
	}
	static void  CreateV8(BoundingBox box, XMFLOAT3* v3)
	{
		//XMFLOAT3 v3[8];
		//XMFLOAT3* v3 = new XMFLOAT3[8];
		box.GetCorners(v3);
	}
	static void CreatVmaxmin(XMFLOAT3 outmax, XMFLOAT3 outmin,XMFLOAT3 m_Scale,XMFLOAT3 m_Rotation,XMFLOAT3& Vmaxout, XMFLOAT3& Vminout)
	{
		XMMATRIX scale= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		/*XMMATRIX rot*/ scale *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		XMVECTOR Vmax = XMVector3TransformCoord(XMLoadFloat3(&outmax), scale);
		XMVECTOR Vmin= XMVector3TransformCoord(XMLoadFloat3(&outmin), scale);
		/*Vmax = XMVector3TransformCoord(XMLoadFloat3(&outmax), scale);
		Vmin = XMVector3TransformCoord(XMLoadFloat3(&outmin), scale);*/
		XMStoreFloat3(&Vmaxout, Vmax);
		XMStoreFloat3(&Vminout, Vmin);
	}
};
class CAttack
{
public:
	static bool isEnemy()
	{
		if (CInput::GetKeyTrigger(VK_RBUTTON))
		{
			XMFLOAT2 mousPos;
			mousPos = XMFLOAT2(CInput::GetmouseX(), CInput::GetmouseY());
			CCamera* p_camera = CManager::GetScene()->GetGmeobjs<CCamera>(_Camera);
			Ray ray = Ray::ScreenToRay(p_camera, mousPos.x, mousPos.y);

			for (int i = 0; i < 2; i++)
			{
				CBlueArmy* pBarmy = CManager::GetScene()->GetGmeobj<CBlueArmy>(5, i);
				if (pBarmy != nullptr)
				{
					BARMYDATE *sBadte = pBarmy->GetsBdate();
					float d;
					BoundingOrientedBox asd;
					BoundingOrientedBox::CreateFromBoundingBox(asd, sBadte->ABox);
					//asdddd.Intersects(asd, sddd);
					if (asd.Intersects(XMLoadFloat3(&ray.origin), XMLoadFloat3(&ray.direction), d))
					{
						return true;
					}
				}
			}
		}
		return false;
	}
};
//  struct GameScene 
//{
//	  std::vector<CRedArmy*> 
//};
template <typename T>
class Canimation
{
public:
	static void Using(){}
};
class Text
{
private:
//	static std::vector<STRINGDRAW> Vstring;
 // static	std::vector<STRINGDRAW> Vstring;

public:
	static void Addtext(STRINGDRAW Sstring)
	{
		CRenderer::Vstring.push_back(Sstring);
	}
	static void SetString(int ID, STRINGDRAW Sstring)
	{
		for (int i = 0; i < CRenderer::Vstring.size(); i++)
		{
			int _id = CRenderer::Vstring[i].ID;
			if (ID == _id)
			{
				Sstring.ID = ID;
				CRenderer::Vstring[i] = Sstring;
			}
		}
	}
	static void TextDraw()
	{
		//XMFLOAT2(CRenderer::Debug_move_v3[0], CRenderer::Debug_move_v3[1])
		if (CRenderer::Vstring.size() > 0)
		{
			for (int i = 0; i < CRenderer::Vstring.size(); i++)
			{
				bool sw = CRenderer::Vstring[i].StringSwitch;
				if (sw)
					CRenderer::spritefont->DrawString(CRenderer::spritebich.get(), Tool::StrToWtr(CRenderer::Vstring[i].Text).c_str(), CRenderer::Vstring[i].Pos, CRenderer::Vstring[i].Color, CRenderer::Vstring[i].RotSpeed, CRenderer::Vstring[i].RotPoint, CRenderer::Vstring[i].Scale);
			}
		}
	}
};
class ObjRun
{

public:
	static bool ZombieDontMove()
	{
		if (!CRenderer::RunSwtichForZombie) return false;
		else return true;
	}
};
struct  TamaSort
{
	float RaySize;
	CZombie_man* PMAN = NULL;
};
class PlayerManager
{
public:
	static void AttackManger(Ray ray)
	{

		std::list<TamaSort> VDirSize2;
 		for (int i = 0; i < ENEMY_SIZE; i++)
		{
			CZombie_man* pman = CManager::GetScene()->GetGmeobj<CZombie_man>(ENEMY_ID, i);
			if (pman != nullptr)
			{
				ZOMBIEDATE* sdate = pman->GetStrutForData();
				if (sdate->Currentanim != Man_dead&&sdate->Currentanim!=Man_isDie)
				{
					TamaSort sort;
					if (ray.Hit(pman->Get_box(), &sort.RaySize)|| ray.Hit(pman->Get_HeadBox(), &sort.RaySize))
					{
						sort.PMAN = pman;
						VDirSize2.push_back(sort);
					}
				}
			}
		}


			VDirSize2.sort([&](TamaSort a, TamaSort b)
			{
				return a.RaySize < b.RaySize;
			});
	
		if (!VDirSize2.empty())
		{
			CZombie_man* pman = VDirSize2.front().PMAN;
			if (ray.Hit(pman->Get_box()))
			{
				XMVECTOR xmpos = XMLoadFloat3(&ray.direction);
				XMVECTOR pexPos = XMLoadFloat3(&pman->GetPosition());
				XMFLOAT3 Pos;
				if (pman->GetPosition().y <= 5.0f)
				{
					pexPos += xmpos * 1.0f;
					XMStoreFloat3(&Pos, pexPos);
					Pos.y = 0.0f;
					pman->SetPosition(Pos);
				}
				pman->GetStrutForData()->Currentanim = Manhurt_duzhi;
				pman->GetStrutForData()->HP -= 5.0f;

				CFont* pFont = CManager::GetScene()->GetGmeobjs<CFont>(FONT_ID);
				pFont->AddTextForGold(pFont->GetGold(XMFLOAT2(SCREEN_WIDTH / 2 + 100.0f, SCREEN_HEIGHT / 2 - 50.0f), 30.0f));
				pFont->GetNumDatePtr()->MoneySize += 30.0f;

				XMFLOAT3 BloodPos = pman->GetPosition();
				BloodPos.z -= 18.0f;
				BloodPos.y += 5.0f;
				CBlood* pBlood = CManager::GetScene()->AddGameObject<CBlood>(10);
				pBlood->SetPosition(BloodPos);
			}
			else if (ray.Hit(pman->Get_HeadBox()))
			{
				XMVECTOR xmpos = XMLoadFloat3(&ray.direction);
				XMVECTOR pexPos = XMLoadFloat3(&pman->GetPosition());
				XMFLOAT3 Pos;
				if (pman->GetPosition().y <= 5.0f)
				{
					pexPos += xmpos * 1.0f;
					XMStoreFloat3(&Pos, pexPos);
					Pos.y = 0.0f;
					pman->SetPosition(Pos);
				}
				pman->GetStrutForData()->Currentanim = Manhurt_head;
				pman->GetStrutForData()->HP -= 10.0f;

				CFont* pFont = CManager::GetScene()->GetGmeobjs<CFont>(FONT_ID);
				pFont->AddTextForGold(pFont->GetGold(XMFLOAT2(SCREEN_WIDTH / 2 + 100.0f, SCREEN_HEIGHT / 2 - 50.0f), 60.0f));
				pFont->GetNumDatePtr()->MoneySize += 60.0f;

				XMFLOAT3 BloodPos = pman->GetPosition();
				BloodPos.z -= 18.0f;
				BloodPos.y += 10.0f;
				CBlood* pBlood = CManager::GetScene()->AddGameObject<CBlood>(10);
				pBlood->SetPosition(BloodPos);
			}
		}
	}
	static int knifeAttackManger(Ray ray,float Range)
	{

		std::list<TamaSort> VDirSize2;
		for (int i = 0; i < ENEMY_SIZE; i++)
		{
			CZombie_man* pman = CManager::GetScene()->GetGmeobj<CZombie_man>(ENEMY_ID, i);
			if (pman != nullptr)
			{
				ZOMBIEDATE* sdate = pman->GetStrutForData();
				if (sdate->Currentanim != Man_dead && sdate->Currentanim != Man_isDie)
				{
					TamaSort sort;
					if (ray.Hit(pman->Get_box(), &sort.RaySize) || ray.Hit(pman->Get_HeadBox(), &sort.RaySize))
					{
						sort.PMAN = pman;
						VDirSize2.push_back(sort);
					}
				}
			}
		}


		VDirSize2.sort([&](TamaSort a, TamaSort b)
		{
			return a.RaySize < b.RaySize;
		});
		if (VDirSize2.front().RaySize <= Range)
		{
			if (!VDirSize2.empty())
			{
				CZombie_man* pman = VDirSize2.front().PMAN;
				if (ray.Hit(pman->Get_box()))
				{
					XMVECTOR xmpos = XMLoadFloat3(&ray.direction);
					XMVECTOR pexPos = XMLoadFloat3(&pman->GetPosition());
					XMFLOAT3 Pos;
					/*if (pman->GetPosition().y <= 5.0f)
					{
						pexPos += xmpos * 1.0f;
						XMStoreFloat3(&Pos, pexPos);
						Pos.y = 0.0f;
						pman->SetPosition(Pos);
					}*/
					//pman->GetStrutForData()->Currentanim = Manhurt_duzhi;
					pman->GetStrutForData()->HP -= 0.5f;

					CFont* pFont = CManager::GetScene()->GetGmeobjs<CFont>(FONT_ID);
					pFont->AddTextForGold(pFont->GetGold(XMFLOAT2(SCREEN_WIDTH / 2 + 100.0f, SCREEN_HEIGHT / 2 - 50.0f), 30.0f));
					pFont->GetNumDatePtr()->MoneySize += 5.0f;

					XMFLOAT3 BloodPos = pman->GetPosition();
					BloodPos.z -= 18.0f;
					BloodPos.y += 5.0f;
					CBlood* pBlood = CManager::GetScene()->AddGameObject<CBlood>(10);
					pBlood->SetPosition(BloodPos);
					return 1;
				}
				else if (ray.Hit(pman->Get_HeadBox()))
				{
					XMVECTOR xmpos = XMLoadFloat3(&ray.direction);
					XMVECTOR pexPos = XMLoadFloat3(&pman->GetPosition());
					XMFLOAT3 Pos;
					/*if (pman->GetPosition().y <= 5.0f)
					{
						pexPos += xmpos * 1.0f;
						XMStoreFloat3(&Pos, pexPos);
						Pos.y = 0.0f;
						pman->SetPosition(Pos);
					}*/
					//pman->GetStrutForData()->Currentanim = Manhurt_head;
					pman->GetStrutForData()->HP -= 1.0f;

					CFont* pFont = CManager::GetScene()->GetGmeobjs<CFont>(FONT_ID);
					pFont->AddTextForGold(pFont->GetGold(XMFLOAT2(SCREEN_WIDTH / 2 + 100.0f, SCREEN_HEIGHT / 2 - 50.0f), 60.0f));
					pFont->GetNumDatePtr()->MoneySize += 12.0f;

					XMFLOAT3 BloodPos = pman->GetPosition();
					BloodPos.z -= 18.0f;
					BloodPos.y += 10.0f;
					CBlood* pBlood = CManager::GetScene()->AddGameObject<CBlood>(10);
					pBlood->SetPosition(BloodPos);
					return 1;
				}
			}
		}
		return 0;
	}
	static void CotrolMove(ControlXiput  xiputNum,XMMATRIX& outmatrix,float blend)
	{
		switch (xiputNum)
		{
		case Ww:
			outmatrix *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(180)*(1+blend)/2, 0.0f);
			break;
		case Ss:
			outmatrix *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(180)*(1 + blend) / 2, 0.0f);
			break;
		case Aa:
			outmatrix *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(90.0f)+XMConvertToRadians(90.0f)*(1 + blend) / 2, 0.0f);
		case Dd:
			outmatrix *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(-90.0f)*(1 + blend) / 2, 0.0f);
			//world *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(90)*rotBlend2, 0.0f);
			break;
	/*	case X:
			outmatrix *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(90)*rotBlend, 0.0f);
			break;
		case Y:
			outmatrix *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(-90)*rotBlend, 0.0f);
			break;*/
		/*case miaozhun:
			rotmatrix *= XMMatrixRotationRollPitchYaw(0.0f, XMConvertToRadians(180), 0.0f);
			break;*/
		}
	}

};
class ZombieManager
{
public:
	static void Zombieiscomming()
	{
		for (int i = 0; i < ENEMY_SIZE; i++)
		{
			CZombie_man*  pman = CManager::GetScene()->GetGmeobj<CZombie_man>(ENEMY_ID, i);
			if (pman != nullptr)
			{
				ZOMBIEDATE* data = pman->GetStrutForData();
				if (data->ZombieState==zombie_InitalState)
				{
					pman->SetAtRestPos(0,4);
					return;
				}
			}
		}
	}
};



