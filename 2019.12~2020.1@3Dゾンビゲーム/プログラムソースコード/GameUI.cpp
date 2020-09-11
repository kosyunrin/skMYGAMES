#include"B_header.h"
#include"CPolygon.h"
#include"texture.h"
#include"input.h"



GameUI::GameUI()
{	
	BlueDrawUI.BuleDraw = true;
}


GameUI::~GameUI()
{
}

void GameUI::Init()
{
	Go_texture = new CTexture();
	Go_textures = new CTexture();
	Go_texture->LoadALLTga();
	Go_textures->LoadAnyJpgPng();
	Go_polygon = new CPolygon();
	Go_polygon->Init();
}

void GameUI::Uninit()
{
	Go_texture->UnloadAllTga();
	Go_textures->UnloadAllJpgPng();
	delete Go_texture;
	delete Go_textures;
	Go_polygon->Uninit();
	delete Go_polygon;
}

void GameUI::Update(float dt)
{
	
}

void GameUI::Draw()
{
	SoldierHouseBlue* g_s = CManager::GetScene()->GetGmeobjs<SoldierHouseBlue>(_solderHouseblue);
	cnt += 0.3f;
	int pattern = (int)cnt % 2;
	Go_polygon->DrawJpgPng(30.0f, 910.0f, 50.0f, 50.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2);
	Go_polygon->Draw(100.0f, 0.0f, 200.0f, 200.0f, pattern*Go_texture->Texture_GetWidth(6) / 1, pattern / 1* Go_texture->Texture_GetHeight(6) / 2,
		Go_texture->Texture_GetWidth(6) / 1, Go_texture->Texture_GetHeight(6) / 2, 6);
	Go_polygon->Draw_animation2D(500.0f, 0.0f, 200.0f, 200.0f,6, 1, 2, 0.3f);
	//Go_polygon->Draw(300.0f, 0.0f, 200.0f, 200.0f, pattern*Go_texture->Texture_GetWidth(5) / 5, pattern / 5 * Go_texture->Texture_GetHeight(5) / 3,
		//Go_texture->Texture_GetWidth(5) / 5, Go_texture->Texture_GetHeight(5) / 3, 5);

	Go_polygon->DrawJpgPng(0.0f, 900.0f, 500.0f, 100.0f, 1.0f,1.0f,1.0f,1.0f,1);
	
}

DrawUI * GameUI::getUiDraw()
{
	return &BlueDrawUI;
}
