#pragma once
#include"CStaticmodle.h"
#include"CSkinnedfbxanim.h"
enum  class MusicPattern :int
{
	Sound_Stop = -1,
	Sound_Barrking,
	Sound_Attack,
	Sound_die,
	Sound_StopAttack
};
namespace WEAPON
{
	enum  class Pattern :int
	{
		UsingSate,
		AttackState,
		Attack,
	};
	enum  class Type :int
	{
		knfie,
		Gun,
	};
}
class MusicBasic
{
public:
	virtual void Init() = 0;
	virtual void Start(MusicPattern num) = 0;
	virtual void Stop(MusicPattern num) = 0;
};
class PlayerWeaPonBase
{
protected:
	std::unique_ptr<CStaticmodle> pWeapon;
public:
	virtual void InitWeapon( ) = 0;
	virtual void Update(WEAPON::Type type, WEAPON::Pattern Pattern, XMMATRIX WorldMatrix, CSkinnedfbxanim* pMode) = 0;
};
class BossWeaPonBase
{
protected:
	std::unique_ptr<CStaticmodle> pWeakness;
	std::unique_ptr<Line>	pLine;
	BoundingBox m_box;
	BoundingBox m_bodyBox;
	XMFLOAT3 m_Position;
	XMFLOAT3 m_bodyPos;
	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_Scale;
	XMFLOAT4X4 Matrix_Box;
	XMFLOAT4X4 Body_MatrixBox;
public:
	virtual void InitWeapon() = 0;
	virtual void Update(XMMATRIX WorldMatrix, CSkinnedfbxanim* pMode) = 0;
	XMMATRIX GetEyeBoxMatrix() { return XMLoadFloat4x4(&Matrix_Box); }
	BoundingSphere GetEyESphereBox()
	{
		BoundingBox box;
		m_box.Transform(box, GetEyeBoxMatrix());
		BoundingSphere Sp;
		BoundingSphere::CreateFromBoundingBox(Sp, box);
		return Sp;
	}
	BoundingBox GetBodySphereBox()
	{
		BoundingBox box;
		m_bodyBox.Transform(box, XMLoadFloat4x4(&Body_MatrixBox));
	
		return box;
	}
	XMFLOAT3 GetEyEPos()
	{
		return m_Position;
	}
};