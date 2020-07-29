#pragma once
class CBlood :public CGameObject
{
public:
	CBlood();
	~CBlood();
public:
	void Init();
	void Uninit();
	void Update(float dt);
	void Draw();
private:
	bool madeb;
	Timer* timer;
	CSkinnedfbxanim* pModle;
};

