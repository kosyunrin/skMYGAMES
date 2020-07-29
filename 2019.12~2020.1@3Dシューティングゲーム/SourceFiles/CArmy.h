#pragma once
class CBlueArmy :public CGameObject
{
public:
	CBlueArmy();
	~CBlueArmy();
	void Init();
	void Uninit();
	void Update(float dt);
	void Draw();
private:
	CSkinnedfbxanim* pModle;
	BARMYDATE sBdate;
	Line* pLine;
	int TargetID;
	XMMATRIX worldsssss;//test
public:
	BARMYDATE* GetsBdate();
	BoundingOrientedBox GetOBB(XMFLOAT3 m_rot);
};

