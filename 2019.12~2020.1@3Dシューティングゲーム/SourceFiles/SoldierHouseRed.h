#pragma once
class SoldierHouseRed:public CGameObject
{
public:
	SoldierHouseRed();
	~SoldierHouseRed();
public:
	BoundingOrientedBox GetArmyBox_obb() const;
public:
	void Init();
	void Uninit();
	void Update(float dt);
	void Draw();
private:
	int count;
	StaticModel* sss;
	XMVECTOR m_quation;
	LAimryDate AimryDate;
	XMFLOAT4X4 B_worldXMMRIX;
	Line* m_line;
};

