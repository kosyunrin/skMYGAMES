#pragma once
#define Bullet_MAX	(10)

class Cbullet:public CGameObject
{
public:
	Cbullet( );
	~Cbullet();
private:
	CPolygon *pBullet;
	Timer* ptimer;
	XMFLOAT3 Qidian;
	int EnemyID;
	int Power;
	int target;
	float dist;
	XMFLOAT3 userPos;
	UserDate pUserDate;
public:
	void Init();
	void Uninit();
	void Update(float dt);
	void Draw();
public:
	void SetenemyID(int ID) { EnemyID = ID; }
	void SetPower(float size) { Power = size; }
	void LoadTex(const  wchar_t* path);
	void SetTarget(int targetx) { target = targetx; }
	void SetUserDate(CBlueArmy* PB, CRedArmy* PR) { pUserDate.pB = PB;  pUserDate.pR=PR; }
};

