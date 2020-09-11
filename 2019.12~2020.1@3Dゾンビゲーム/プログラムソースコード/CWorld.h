#pragma once
class CWorld :public CGameObject
{
public:
	CWorld();
	~CWorld();
public:
	void Init();
	void Uninit();
	void Update(float dt);
	void Draw();
	void DrawShadow();
private:
	CStaticmodle* e_Modle;
};

