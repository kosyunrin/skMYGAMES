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
	void OpenOther(XMMATRIX Matrix);
private:
	bool madeb;
	Timer* timer;
	CSkinnedfbxanim* pModle;
	bool usemWorldMatrix;
	XMFLOAT4X4 OtherMatrix;
};

