#pragma once
class CFont : public CGameObject
{
public:
	CFont();
	~CFont();
public:
	void Init();
	void Uninit();
	void Update(float dt);
	void Draw();
private:
	SNumber NumberDate;
	std::unique_ptr<Timer> ptimer;
	std::unique_ptr<Timer> ptimerforzombie;
	std::vector<GOLDPOOR> Goldpurse;
	bool zombieisnotcomming;
public:
	SNumber* GetNumDatePtr() { return &NumberDate; }
	void AddTextForGold(GOLDPOOR gold) { Goldpurse.push_back(gold); }
	GOLDPOOR GetGold(XMFLOAT2 pos, int money);
};

