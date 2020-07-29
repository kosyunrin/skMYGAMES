#include "main.h"
#include"input.h"
#include"Timer.h"
#include "renderer.h"
#include"model.h"
#include"game_object.h"
#include"TitleUI.h"
#include"Scene.h"
#include"manager.h"
#include "Title.h"
#include"game.h"
#include"GamePad.h"



Title::Title()
{
}


Title::~Title()
{
}

void Title::Init()
{
	AddGameObject<TitleUI>(0);
}

void Title::Uninit()
{
	CScene::Uninit();
}

void Title::Update(float dt)
{
	CScene::Update(dt);
	if (CInput::GetKeyTrigger('I'))
	{
		CManager::SetScene<game>();
	}
	else if (CInput::GetKeyTrigger(VK_RETURN))
	{
		CManager::SetScene<game>();
	}

	TitleUI* pUi = CManager::GetScene()->GetGmeobjs<TitleUI>(0);
	if (pUi != nullptr)
	{
		switch (pUi->GetUINum())
		{
		case gamestart:
			if(Input::GamePad::IsTrigger(Input::GamePad::Button::A)) CManager::SetScene<game>();
			break;
		case gameend:
			if (Input::GamePad::IsTrigger(Input::GamePad::Button::A)) DestroyWindow(GetWindow());
			break;
		}
	}
}
