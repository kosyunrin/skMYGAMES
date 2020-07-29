#pragma once
class CRedArmy :public CGameObject
{
public:
	CRedArmy();
	~CRedArmy();
	void Init();
	void Uninit();
	void Update(float dt);
	void Draw();
private:
	CSkinnedfbxanim* pModle;
	BARMYDATE sRdate;
	Line* pLine;
public:
	BARMYDATE* GetsRdate();
	BoundingSphere GetColliderSphere();
};

