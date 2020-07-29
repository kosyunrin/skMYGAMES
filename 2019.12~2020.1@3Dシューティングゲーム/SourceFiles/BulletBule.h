#pragma once
class BulletBule:public CGameObject
{
public:
	BulletBule();
	~BulletBule();
public:
	void Move();
	void State();
public:
	void Init();
	void Uninit();
	void Update(float dt);
	void Draw();
private:
	StaticModel* t_Modle;
	float count;
	EnemyBullet  Sbullet;
public:
	EnemyBullet* getSbule();
};

