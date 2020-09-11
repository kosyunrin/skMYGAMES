#include"B_header.h"
#include "game.h"
#include"end.h"
#include"Title.h"
#include"input.h"
#include"Timer.h"


game::game()
{
}


game::~game()
{
}
void game::Init()
{
	AddGameObject<CCameraOne>(_Camera);
	AddGameObject<CShadow>(ShadowLight_ID);
	AddGameObject<skyBox>(2);

	//AddGameObject<CFont>(2);
	//AddGameObject<CField>(_Cfield);
	//AddGameObject<CPlayer>(3);
	//AddGameObject<CEnemy>(_Enemy);
	AddGameObject<CP0>(4);
	AddGameObject<CWorld>(5);
	//AddGameObject<CEnemy>(4)->SetPos(0, XMFLOAT3(5.0f, 0.0f, 0.0f));
	AddGameObject<CEnemy>(6);
	AddGameObject<CZombie_man>(ENEMY_ID)->GetStrutForData()->ID=1.0f;
	AddGameObject<CZombie_man>(ENEMY_ID);
	AddGameObject<CZombie_man>(ENEMY_ID);
	AddGameObject<CZombie_man>(ENEMY_ID);
	AddGameObject<CZombie_man>(ENEMY_ID);
	AddGameObject<CZombie_man>(ENEMY_ID);
	AddGameObject<CZombie_man>(ENEMY_ID);
	AddGameObject<CZombie_man>(ENEMY_ID);
	AddGameObject<CZombie_man>(ENEMY_ID);
	AddGameObject<CZombie_man>(ENEMY_ID);
	//AddGameObject<CZombie_man>(7);
	//AddGameObject<CZombie_man>(7);
	AddGameObject<CMap>(8);
	AddGameObject<CBlock>(9);
	//AddGameObject<CBlood>(10);
	//AddGameObject<CBlock>(9)->SetPosition({0.0f,0.0f,150.0f});
	/*for (UINT i = 0; i < 10; i++)
	{
		AddGameObject<CArmy>(5)->SetPosition(XMFLOAT3(5.0f, 0.0f, i));
	}*/
	//AddGameObject<CBlueArmy>(5);
	//AddGameObject<CRedArmy>(6);
	//AddGameObject<SoldierHouseBlue>(7);
	//Enemy 4
	//redbullet 5
	//AddGameObject<CmeshField>(_Cmeshfield);
	//AddGameObject<SoldierHouseRed>(_solderHousered);
	//AddGameObject<SoldierHouseBlue>(_solderHouseblue);
	//bluebullet 9
	//friend 10
	//AddGameObject<Friend>(_Friend);
	//AddGameObject<GameUI>(10);
	AddGameObject<UImanager3D>(UI_ID);

	AddGameObject<CFont>(FONT_ID);

	//AddGameObject<Cbullet>(12);
	M_BGM = new CAudioClip();
	M_BGM->Load("asset/Music/backgroundMK.wav");
	M_BGM->Play(true);
	pTimer = new Timer();
	pTimer->Reset();
}

void game::Uninit()
{

	CScene::Uninit();
	/*M_BGM->Uninit();
	delete M_BGM;*/
	delete pTimer;
	delete M_BGM;
	
}

void game::Update(float dt)
{
	CScene::Update(dt);


	//pTimer->Tick();//ji shi qi

	/*if (pTimer->TotalTime() > 5.0f)
	{
		for (int i = 0; i < 2; i++)
		{
			CBlueArmy* pB = CScene::GetGmeobj<CBlueArmy>(5, i);
			if (pB != nullptr)
			{
				BARMYDATE* sBdate = pB->GetsBdate();
				if (sBdate->life <= 0)
				{
					sBdate->life = 200.0f;
					pB->SetPosition(XMFLOAT3(58.0f, 0.0f, 0.0f));
				}
			}
		}
		pTimer->Reset();
	}*/






	//
	SoldierHouseBlue* pBH = CManager::GetScene()->GetGmeobjs<SoldierHouseBlue>(7);
	if (pBH != nullptr)
	{
		House* sBH = pBH->GetDate_house();
		if (sBH->HP <= 0)
		{
			M_BGM->Unload();
			CManager::SetScene<end>();

		}
	}
	
	CP0* p0 = CManager::GetScene()->GetGmeobjs<CP0>(4);
	CEnemy* pe = CManager::GetScene()->GetGmeobjs<CEnemy>(6);
	if (p0 != nullptr)
	{
		if (CInput::GetKeyTrigger('I'))
		{
			M_BGM->Unload();
			CManager::SetScene<end>();
		}
		if (p0->GetP0Dataptr()->BeHurtAnimControl)
		{
			pTimer->Tick();//ji shi qi
			P0Date* SDate = p0->GetP0Dataptr();

			if (pTimer->TotalTime() <= 5.0f)
			{

				if (CInput::GetKeyTrigger('B') || GamePad::IsTrigger(GamePad::Button::B)) SDate->TouchNum++;
				if (SDate->TouchNum > 30.0f) SDate->BeHurtAnimControl = false;
			}
			else
			{
				p0->SetMovie(LensTwo);
				CRenderer::RunSwtichForZombie = true;
				UImanager3D* pui = CManager::GetScene()->GetGmeobjs<UImanager3D>(UI_ID);
				pui->SetSwtichOpen(true);
				if (pui->GetFadeBlend() >= 1.0f)
				{
					M_BGM->Unload();
					CManager::SetScene<end>();
				}
			}
		}
		else if (p0->GetP0Dataptr()->HP <= 0)
		{
			p0->SetMovie(LensTwo);
			CRenderer::RunSwtichForZombie = true;
			UImanager3D* pui = CManager::GetScene()->GetGmeobjs<UImanager3D>(UI_ID);
			pui->SetSwtichOpen(true);
			if (pui->GetFadeBlend() >= 1.0f)
			{
				M_BGM->Unload();
				CManager::SetScene<end>();
			}
		}
		else if (pe->Get_Date()->HP <= 0)
		{
			UImanager3D* pui = CManager::GetScene()->GetGmeobjs<UImanager3D>(UI_ID);
			//pui->RestScene();
			pui->SetSwtichOpen(true);
			if (pui->GetFadeBlend() >= 1.0f)
			{
				M_BGM->Unload();
				CManager::SetScene<Title>();
			}
		}
		else
		{
			pTimer->Reset();
		}
	}
}


