#pragma once
class SoldierHouseBlue;
class CPolygon;
class GameUI:public CGameObject
{
public:
	GameUI();
	~GameUI();
private:
	float w;
	float h;
	float cnt = 0;
	CTexture* Go_texture;
	CTexture* Go_textures;
	CPolygon* Go_polygon;
	DrawUI BlueDrawUI;
public:
	void Init();
	void Uninit();
	void Update(float dt);
	void Draw();
public:
public:
	DrawUI* getUiDraw();

};

