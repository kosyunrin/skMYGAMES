#include"main.h"
#include "CObjPhySics.h"

CObjPhySics::CObjPhySics(float g, float speed, float constSpeed)
{
	gSpeed = g;
	Speed = speed;
	ConstSpeed = constSpeed;
}

CObjPhySics::~CObjPhySics()
{
}

bool CObjPhySics::Gravity(XMFLOAT3 & outpos, float dt)
{
	if (outpos.y <= 0.0f&&outpos.z>-100.0f)
	{
		outpos.y = 0.0f;
		Speed = ConstSpeed;
		return false;
	}
	else if (outpos.y <= 25.8f&&outpos.z < -100.0f)
	{
		outpos.y = 25.8f;
		Speed = ConstSpeed;
		return false;
	}
	else
	{
		float _speed = -dt * Speed;
		outpos.y += _speed;
		Speed += gSpeed;
		return true;
	}
}
