#pragma once
class CObjPhySics
{
public:
	CObjPhySics(float g,float speed,float constSpeed);
	~CObjPhySics();
	bool Gravity(XMFLOAT3& outpos, float dt);
private:
	float gSpeed;
	float Speed;
	float ConstSpeed;
};

