#pragma once
#include"main.h"
#include"CObjManager.h"
class ArmyKnife : public PlayerWeaPonBase
{
public:
	virtual void Update(WEAPON::Type type, WEAPON::Pattern Pattern, XMMATRIX WorldMatrix, CSkinnedfbxanim* pMode)override
	{
		XMFLOAT3 rot = {11.0f,11.0f,0.0f};
		XMFLOAT3 Scal = {3.5f,3.5f,3.5f };

		XMMATRIX boneMatrix = pMode->GetFramLocalWorldMatrix(38);
		//XMMATRIX boneMatrix = pModle->GetBonesTransform(54);
		XMFLOAT4X4 weaponBone;
		XMMATRIX LocalBoneWorldMatrix;
		XMFLOAT3 WorldPos;

		/*switch (Pattern)
		{
		case WeaPonPattern::NoneState:
		{
			boneMatrix = pMode->GetFramLocalWorldMatrix(12);
			rot = { 1.5f,10.6f,6.0f };
			WorldPos = { 25.4f,4.8f,13.3f };
			LocalBoneWorldMatrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			LocalBoneWorldMatrix *= XMMatrixScaling(Scal.x, Scal.y, Scal.z);
		}
			break;
		case WeaPonPattern::UsingSate:
		{
			WorldPos = { 0.0f,-6.4f,0.0f };
			LocalBoneWorldMatrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			LocalBoneWorldMatrix *= XMMatrixScaling(Scal.x, Scal.y, Scal.z);
		}
			break;
		case WeaPonPattern::AttackState:
		{
			WorldPos = { -11.0f,0.0f,0.0f };
			LocalBoneWorldMatrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			LocalBoneWorldMatrix *= XMMatrixScaling(Scal.x, Scal.y, Scal.z);
		}
			break;
		case WeaPonPattern::Attack:
		{
			WorldPos = { -11.0f,-0.5f,0.6f };
			LocalBoneWorldMatrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			LocalBoneWorldMatrix *= XMMatrixScaling(Scal.x, Scal.y, Scal.z);
		}
			break;
		}*/

		switch (type)
		{
		case WEAPON::Type::knfie:
		/*	WorldPos = { 0.0f,-6.4f,0.0f };
			LocalBoneWorldMatrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			LocalBoneWorldMatrix *= XMMatrixScaling(Scal.x, Scal.y, Scal.z);*/
			switch (Pattern)
			{
			case WEAPON::Pattern::UsingSate:
			{
				WorldPos = { 0.0f,-6.4f,0.0f };
				LocalBoneWorldMatrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
				LocalBoneWorldMatrix *= XMMatrixScaling(Scal.x, Scal.y, Scal.z);
			}
				break;
			case WEAPON::Pattern::AttackState:
			{
				WorldPos = { -11.0f,0.0f,0.0f };
				LocalBoneWorldMatrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
				LocalBoneWorldMatrix *= XMMatrixScaling(Scal.x, Scal.y, Scal.z);
			}
				break;
			case WEAPON::Pattern::Attack:
			{
				WorldPos = { -11.0f,-0.5f,0.6f };
				LocalBoneWorldMatrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
				LocalBoneWorldMatrix *= XMMatrixScaling(Scal.x, Scal.y, Scal.z);
			}
				break;
			}
			break;
		case WEAPON::Type::Gun:
		/*	boneMatrix = pMode->GetFramLocalWorldMatrix(12);
			rot = { 1.5f,10.6f,6.0f };
			WorldPos = { 25.4f,4.8f,13.3f };
			LocalBoneWorldMatrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
			LocalBoneWorldMatrix *= XMMatrixScaling(Scal.x, Scal.y, Scal.z);*/
			switch (Pattern)
			{
			case WEAPON::Pattern::UsingSate:
			{
				boneMatrix = pMode->GetFramLocalWorldMatrix(12);
				rot = { 1.5f,10.6f,6.0f };
				WorldPos = { 25.4f,4.8f,13.3f };
				LocalBoneWorldMatrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
				LocalBoneWorldMatrix *= XMMatrixScaling(Scal.x, Scal.y, Scal.z);
			}
				break;
			case WEAPON::Pattern::AttackState:
				break;
			case WEAPON::Pattern::Attack:
				break;
			}
			break;
		}
		XMStoreFloat4x4(&weaponBone, boneMatrix);
		pMode->SetWeaponLocalMatrix(LocalBoneWorldMatrix);
		pWeapon->RenderWeaPon(XMMatrixTranslation(WorldPos.x, WorldPos.y, WorldPos.z)*WorldMatrix, weaponBone);
	}
	virtual void InitWeapon()override
	{
		pWeapon = std::make_unique<CStaticmodle>("asset/Onepiece/WaponDao3.fbx",0);
	}
};
