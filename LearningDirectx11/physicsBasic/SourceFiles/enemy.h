#pragma once

class Enemy :public GameObject
{
private:
	enum Event
	{
		Idle,
		Shout,
		Walk,
		Run,
		Attack,
		Hit,
		Dead
	};

	std::unique_ptr<MultiSkinnedModel> model;

	UINT event;

	XMFLOAT3 targetLocation;

	float speed;
	float counter;
	float deadCounter;

	bool onceTargeted;
	bool shouted;
	bool dead;
	bool shoutResetedTimer;
	bool deadResetedTimer;

	void Initialize() override;

	void Idle_Action();
	void Shout_Action();
	void Run_Action();
	void Attack_Action();
	void Hit_Action();
	void Dead_Action();

public:
	Enemy();

	void Update() override;
	void Render(bool boundingBox) override;
};