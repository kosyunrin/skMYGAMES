#pragma once
class CPlayer :public CGameObject
{

public:
	CPlayer();
	~CPlayer();
private:	
	//StaticModel* m_model;
	CSkinnedfbxanim* m_model;
	MoveManager move;
	Line* m_line;

public:
	void Init();
	void Uninit();
	void Update(float dt);
	void Draw();
	BoundingOrientedBox GetBoundingOrientedBox();
	BoundingSphere GetColliderSphere();
	
private:
	LPlayerOneDate Player_1_Date;
public:
	LPlayerOneDate* GetP0Date();

};

