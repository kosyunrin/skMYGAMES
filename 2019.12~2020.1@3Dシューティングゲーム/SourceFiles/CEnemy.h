#pragma once
class CEnemy:public CGameObject
{
public:
	CEnemy();
	~CEnemy();
public:
	void Init();
	void Uninit();
	void Update(float dt);
	void Draw();
private:
	CSkinnedfbxanim* pModle;
	Line* m_line;
	BoundingBox m_box;
	XMFLOAT4X4 Matrix_World;
	XMFLOAT4X4 Matrix_Box;
	XMFLOAT4X4 Matrix_HeadBox;
	ZOMBIEDATE sDate;
public:
	BoundingBox Get_box();
	BoundingBox Get_HeadBox();
	void SetTriangle(XMFLOAT3* Vpos);
	ZOMBIEDATE* Get_Date() { return &sDate; }
};

