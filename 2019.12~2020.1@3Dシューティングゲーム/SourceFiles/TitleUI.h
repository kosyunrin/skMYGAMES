#pragma once
#include<SpriteBatch.h>
class CPolygon;
enum UICONTROL
{
	gamestart,
	gameend,
};
class TitleUI:public CGameObject
{
public:
	TitleUI();
	~TitleUI();
private:
	std::unique_ptr<CPolygon> pbackground;
	STRINGDRAW GameStart;
	STRINGDRAW GameOut;
	float gamestartBlend;
	int ControlUINum2;
public:
	void Init();
	void Uninit();
	void Update(float dt);
	void Draw();
public:
	int GetUINum()
	{
		return ControlUINum2;
	}
};

