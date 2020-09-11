#pragma once
class Timer;
class Title:public CScene
{
public:
	Title();
	~Title();
public:
	void Init();
	void Uninit();
	void Update(float dt);
private:
};

