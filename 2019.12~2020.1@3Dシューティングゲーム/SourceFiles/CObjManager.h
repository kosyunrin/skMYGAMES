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