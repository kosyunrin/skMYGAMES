#include"TitleScene.h"



TitleUI::TitleUI()
{
}


TitleUI::~TitleUI()
{
}

void TitleUI::Init()
{
	pbackground = std::make_unique<CPolygon>();
	pbackground->Init2D(13);
	GameStart.Color = Colors::Red;
	GameStart.Pos = { 670,180 };
	GameStart.Scale = { 5,5 };
	GameStart.Text = "Game Start";
	GameStart.RotPoint = { 0.0f,0.0f };

	GameOut.Color = Colors::Red;
	GameOut.Pos = { 730,320 };
	GameOut.Scale = { 5,5 };
	GameOut.Text = "PressEnter";

	gamestartBlend = 0.0f;
	ControlUINum2 = gamestart;
	
}

void TitleUI::Uninit()
{
	pbackground->Uninit3D(13);
}

void TitleUI::Update(float dt)
{
	/*XMFLOAT2 pos;
	Tool::DeBugMoveV2(pos);*/
	if (GamePad::IsTrigger(GamePad::Button::THUMB_L_UP))
	{
		ControlUINum2++;
		if (ControlUINum2 > 1.0f) ControlUINum2 = 0.0f;
	}
	else if (GamePad::IsTrigger(GamePad::Button::THUMB_L_DOWN))
	{
		ControlUINum2--;
		if (ControlUINum2 < 0.0f) ControlUINum2 = 1.0f;
	}
	switch (ControlUINum2)
	{
	case gamestart:
		GameOut.Scale = { 5.0f,5.0f};
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
	case gameend:
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
	
}

void TitleUI::Draw()
{
	pbackground->PNGDraw2D(-16, -31, 2000, 1200, 13, 1.0f);

	Tool::TextBegain();

	Tool::TextDraw(GameStart);
	Tool::TextDraw(GameOut);
	Tool::TextEnd();
}
