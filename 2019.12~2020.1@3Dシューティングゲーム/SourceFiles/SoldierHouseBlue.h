#pragma once
#define LIFE_MAX	(100)
class SoldierHouseBlue:public CGameObject
{
public:
	SoldierHouseBlue();
	~SoldierHouseBlue();
public:
	void Init();
	void Uninit();
	void Update(float dt);
	void Draw();
private:
	CStaticmodle* pMode;
	Line* m_line;
	House m_house;
	Timer* m_timer;
	Timer* m_t;
	AStarPathFinding* pA;
public:
	House*  GetDate_house();
};

