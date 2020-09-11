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
	std::unique_ptr<CPolygon> pbackground2;
	STRINGDRAW GameStart;
	STRINGDRAW GameOut;
	STRINGDRAW Loadding;
	float gamestartBlend;
	int ControlUINum2;
	float loaddingblend;
	int loaadingcount;
	float GoGame;
	bool isGoGame;
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
	STRINGDRAW* getstring()
	{
		return &Loadding;
	}
	bool GetGoGame()
	{
		return isGoGame;
	}
	void SetGoGame(bool is)
	{
		isGoGame = is;
	}
	float GetGoGeme()
	{
		return GoGame;
	}
};

