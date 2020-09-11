#pragma once
#include<memory>
#include<SpriteBatch.h>
#include<SpriteFont.h>
class CAudioClip;
class Timer;
class game:public CScene
{
public:
	game();
	~game();
public:
	void Init();
	void Uninit();
	void Update(float dt);
private:
	CAudioClip* M_BGM;
	Timer* pTimer;
};

