#include "main.h"
#include "renderer.h"
#include"CPolygon.h"
#include"game_object.h"
#include"Scene.h"
#include"manager.h"
#include "end.h"
#include"game.h"
#include"Title.h"
#include"input.h"
#include"GamePad.h"
using namespace Input;



end::end()
{
}


end::~end()
{
}

void end::Init()
{
	pbackground = std::make_unique<CPolygon>();
	pbackground->Init2D(13);
	GameStart.Color = Colors::Red;
	GameStart.Pos = { 670,180 };
	GameStart.Scale = { 5,5 };
	GameStart.Text = "Game Again";
	GameStart.RotPoint = { 0.0f,0.0f };

	GameOut.Color = Colors::Red;
	GameOut.Pos = { 730,320 };
	GameOut.Scale = { 5,5 };
	GameOut.Text = "Game end";

	gamestartBlend = 0.0f;
	ControlUINum2 = gamestart2;
}

void end::Uninit()
{
	pbackground->Uninit3D(13);
}

void end::Update(float dt)
{
	//CInput::Update();
	if (CInput::GetKeyTrigger('I'))
	{
		CManager::SetScene<Title>();
	}

	if (GamePad::IsTrigger(GamePad::Button::THUMB_L_UP)|| CInput::GetKeyTrigger(VK_UP)||CInput::GetKeyTrigger('W'))
	{
		ControlUINum2++;
		if (ControlUINum2 > 1.0f) ControlUINum2 = 0.0f;
	}
	else if (GamePad::IsTrigger(GamePad::Button::THUMB_L_DOWN) || CInput::GetKeyTrigger(VK_DOWN) || CInput::GetKeyTrigger('S'))
	{
		ControlUINum2--;
		if (ControlUINum2 < 0.0f) ControlUINum2 = 1.0f;
	}
	switch (ControlUINum2)
	{
	case gamestart2:
		GameOut.Scale = { 5.0f,5.0f };
		if (gamestartBlend < 1.0f)
		{
			Tool::BlendRunUp(gamestartBlend, dt, 1.5f);
			GameStart.Scale = { 5.0f,5.0f + 2.0f*gamestartBlend };
		}
		else
		{
			gamestartBlend = 0.0f;
		}
		break;
	case gameend2:
		GameStart.Scale = { 5,5 };
		if (gamestartBlend < 1.0f)
		{
			Tool::BlendRunUp(gamestartBlend, dt, 1.5f);
			GameOut.Scale = { 5.0f,5.0f + 2.0f*gamestartBlend };
		}
		else
		{
			gamestartBlend = 0.0f;
		}
		break;
	}
	switch (ControlUINum2)
	{
	case gamestart2:
		if (Input::GamePad::IsTrigger(Input::GamePad::Button::A)|| CInput::GetKeyTrigger(VK_RETURN)|| CInput::GetKeyTrigger(VK_LBUTTON)) CManager::SetScene<Title>();
		break;
	case gameend2:
		if (Input::GamePad::IsTrigger(Input::GamePad::Button::A) || CInput::GetKeyTrigger(VK_RETURN)||CInput::GetKeyTrigger(VK_LBUTTON)) DestroyWindow(GetWindow());
		break;
	}
}

void end::Draw()
{
	pbackground->PNGDraw2D(-16, -31, 2000, 1200, 13, 1.0f);

	Tool::TextBegain();

	Tool::TextDraw(GameStart);
	Tool::TextDraw(GameOut);
	Tool::TextEnd();
}
