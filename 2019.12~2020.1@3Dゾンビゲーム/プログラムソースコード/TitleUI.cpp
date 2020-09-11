#include"TitleScene.h"



TitleUI::TitleUI()
{
}


TitleUI::~TitleUI()
{
}

void TitleUI::Init()
{
	loaddingblend = 0;
	loaadingcount = 0;
	isGoGame = false;
	GoGame = 0;
	pbackground = std::make_unique<CPolygon>();
	pbackground2 = std::make_unique<CPolygon>();
	pbackground->Init2D(13);
	pbackground2->Init2D(1);
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

	Loadding.Color = Colors::White;
	Loadding.Pos = { 1600,1000 };
	Loadding.Scale = { 1.5,1.5 };
	Loadding.Text = "";
	Loadding.RotPoint = { 0.0f,0.0f };
	
	
}

void TitleUI::Uninit()
{
	pbackground->Uninit3D(13);
	pbackground2->Uninit3D(1);
}

void TitleUI::Update(float dt)
{
	std::string xloadding = ".";

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


	if (isGoGame) GoGame += dt * 3.0f;
	if (GoGame>0)
	{
		Tool::BlendRunUp(loaddingblend, dt, 10.0f);

		if (loaddingblend >= 1)
		{
			Loadding.Text += xloadding;
			loaadingcount++;
			loaddingblend = 0;
			if (loaadingcount > 8)
			{
				loaadingcount = 0;
				Loadding.Text = "Loadding";
			}
		}
	}
	
	
	
}

void TitleUI::Draw()
{
	if(isGoGame)
	pbackground2->PNGDraw2D(-16, -31, 2000, 1200, 1, 1.0f);
	pbackground->PNGDraw2D(-16, -31, 2000, 1200, 13, 1.0f);

	Tool::TextBegain();

	if (!isGoGame)
	{
		Tool::TextDraw(GameStart);
		Tool::TextDraw(GameOut);
	}
	Tool::TextDraw(Loadding);
	Tool::TextEnd();
}
