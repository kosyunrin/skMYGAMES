#pragma once
#pragma once
#include"main.h"
#include"CObjManager.h"
class Weakness : public BossWeaPonBase
{
public:
	virtual void Update(XMMATRIX WorldMatrix, CSkinnedfbxanim* pMode)override
	{
		XMFLOAT3 rot = { 6.0,6.7,1.4 };
		XMFLOAT3 Scal = { 0.25,0.25,0.25 };

		XMMATRIX boneMatrix = pMode->GetFramLocalWorldMatrix(12);
		XMFLOAT3 posss = pMode->GetFramLocalWorldMatrixPOS(12);
		//XMMATRIX boneMatrix = pModle->GetBonesTransform(54);
		XMFLOAT4X4 weaponBone;
		XMMATRIX LocalBoneWorldMatrix;
		XMFLOAT3 WorldPos;


		//Scal = { CRenderer::Debug_move_Rotation2[0],CRenderer::Debug_move_Rotation2[0] ,CRenderer::Debug_move_Rotation2[0] };
		WorldPos = { -5,1,1 };
		LocalBoneWorldMatrix = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
		LocalBoneWorldMatrix *= XMMatrixScaling(Scal.x, Scal.y, Scal.z);
		
		XMStoreFloat4x4(&weaponBone, boneMatrix);
		pMode->SetWeaponLocalMatrix(LocalBoneWorldMatrix);
		pWeakness->RenderWeaPon(XMMatrixTranslation(WorldPos.x, WorldPos.y, WorldPos.z) * WorldMatrix, weaponBone);

		m_Position = posss;
		XMMATRIX linew;

		//linew = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		linew = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		linew *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
		linew *= XMMatrixTranslation(-6, 1, 1);
		linew *= WorldMatrix;

		XMStoreFloat4x4(&Matrix_Box, linew);

		XMMATRIX Bodyw;
		Bodyw = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		Bodyw *= XMMatrixScaling(1.0f, 1.0f, 1.0f);
		Bodyw *= XMMatrixTranslation(posss.x, posss.y, posss.z);
		Bodyw *= XMMatrixTranslation(1, 0, -1);
		Bodyw *= WorldMatrix;
		XMStoreFloat4x4(&Body_MatrixBox, Bodyw);

		pLine->DrawLineByPlayerWorld(linew);
	}
	virtual void InitWeapon()override
	{
		pWeakness = std::make_unique<CStaticmodle>("asset/Onepiece/Eye.fbx", 0);
		pLine = std::make_unique<Line>();



		XMFLOAT3 vmax={6.0f,6.0f,6.0f };
		XMFLOAT3 vmin = {-6.0f,-6.0f,-6.0f };
		XMFLOAT3 v3[8];
		CCreate::CreateBox(m_box, vmax, vmin);
		CCreate::CreateV8(m_box, v3);
		m_Rotation = { 0,0,0 };
		m_Scale = { 0.8f,0.8f,0.8f };
		m_Position = { -5, 12, 137 };

		 vmax = { 10.0f,6.0f,20.0f };
		 vmin = { -10.0f,-6.0f,-20.0f };
		XMFLOAT3 v4[8];
		CCreate::CreateBox(m_bodyBox, vmax, vmin);
		CCreate::CreateV8(m_bodyBox, v4);

		pLine->InitDrawBox(v3);
	}
};
