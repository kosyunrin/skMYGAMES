#include"B_header.h"



CFont::CFont()
{
}


CFont::~CFont()
{
}

void CFont::Init()
{
	isboss = false;
	zombieisnotcomming = true;
	NumberDate.BulleSize = 30;
	NumberDate.Bulletcount = 6;
	NumberDate.YaocaoSize = 0;
	NumberDate.StageNum = 1;
	NumberDate.EnemyCountInTheScene = 10.0f;
	NumberDate.CommingTimer = 30.0f;
	CRenderer::Vstring.clear();


	STRINGDRAW text0;
	text0.Color = Colors::White;
	text0.ID = BulletCount;
	text0.Pos = { 1700.0f,900.0f };
	text0.RotPoint = { 0.0f,0.0f };
	text0.RotSpeed = 0.0f;
	text0.Scale = { 2.0f,2.0f };
	text0.StringSwitch = true;
	text0.Text = std::to_string(NumberDate.Bulletcount)+"/";
	STRINGDRAW text1;
	text1.Color = Colors::White;
	text1.ID = BulletSize;
	text1.Pos = { 1700.0f,900.0f };
	text1.RotPoint = { 0.0f,0.0f };
	text1.RotSpeed = 0.0f;
	text1.Scale = { 2.0f,2.0f };
	text1.StringSwitch = true;
	text1.Text = "    "+ std::to_string(NumberDate.BulleSize);
	STRINGDRAW text2;
	text2.Color = Colors::Red;
	text2.ID = SurvivalTimer;
	text2.Pos = { 800.0f,0.0f };
	text2.RotPoint = { 0.0f,0.0f };
	text2.RotSpeed = 0.0f;
	text2.Scale = { 3.0f,3.0f };
	text2.StringSwitch = true;
	text2.Text = " :   " + std::to_string(NumberDate.LifeTimer);
	STRINGDRAW text3;
	text3.Color = Colors::White;
	text3.ID = AmountOfMoney;
	text3.Pos = { 1700.0f,800.0f };
	text3.RotPoint = { 0.0f,0.0f };
	text3.RotSpeed = 0.0f;
	text3.Scale = { 2.0f,2.0f };
	text3.StringSwitch = true;
	text3.Text = " :   " + std::to_string(NumberDate.MoneySize);
	NumberDate.MoneySize = 0.0f;
	STRINGDRAW text4;
	text4.Color = Colors::White;
	text4.ID = StageCount;
	text4.Pos = { 0,0 };
	text4.RotPoint = { 0.0f,0.0f };
	text4.RotSpeed = 0.0f;
	text4.Scale = { 3.0f,3.0f };
	text4.StringSwitch = true;
	text4.Text = " :   " + std::to_string(NumberDate.StageNum);
	STRINGDRAW text5;
	text5.Color = Colors::White;
	text5.ID = YaochaoCount;
	text5.Pos = { 152.0f,694.0f };
	text5.RotPoint = { 0.0f,0.0f };
	text5.RotSpeed = 0.0f;
	text5.Scale = { 3.0f,3.0f };
	text5.StringSwitch = true;
	text5.Text = " :   " + std::to_string(NumberDate.StageNum);
	STRINGDRAW text6;
	text6.Color = Colors::White;
	text6.ID = EnemySize;
	text6.Pos = { 1800.0f,20.0f };
	text6.RotPoint = { 0.0f,0.0f };
	text6.RotSpeed = 0.0f;
	text6.Scale = { 2.0f,2.0f };
	text6.StringSwitch = true;
	text6.Text =std::to_string(NumberDate.StageNum);
	STRINGDRAW text7;
	text7.Color = Colors::Red;
	text7.ID = ForEnemyTiming;
	text7.Pos = { 1000.0f,95.0f };
	text7.RotPoint = { 0.0f,0.0f };
	text7.RotSpeed = 0.0f;
	text7.Scale = { 1.0f,1.0f };
	text7.StringSwitch = true;
	text7.Text = std::to_string(NumberDate.CommingTimer);


	
	Text::Addtext(text0);
	Text::Addtext(text1);
	Text::Addtext(text2);
	Text::Addtext(text3);
	Text::Addtext(text4);
	Text::Addtext(text5);
	Text::Addtext(text6);
	Text::Addtext(text7);
	//Text::Addtext(text8);

	ptimer = std::make_unique<Timer>();
	ptimer->Reset();
	ptimerforzombie= std::make_unique<Timer>();
	ptimerforzombie->Reset();

	NumberDate.StageNum = 1.0f;
}

void CFont::Uninit()
{
	Goldpurse.clear();
	//CRenderer::Vstring.clear();
}

void CFont::Update(float dt)
{
	//if (CInput::GetKeyTrigger(VK_SPACE)) zombieisnotcomming = -zombieisnotcomming;


	ptimer->Tick();
	NumberDate.LifeTimer = ptimer->TotalTime();
	
	CRenderer::Vstring[BulletCount].Text= std::to_string(NumberDate.Bulletcount) + "/";
	CRenderer::Vstring[BulletSize].Text = "    " + std::to_string(NumberDate.BulleSize);
	CRenderer::Vstring[SurvivalTimer].Text= " Survival " + std::to_string(NumberDate.LifeTimer)+": 00s";
	CRenderer::Vstring[AmountOfMoney].Text = "  " + std::to_string(NumberDate.MoneySize);
	CRenderer::Vstring[StageCount].Text = "  STAGE " + std::to_string(NumberDate.StageNum);
	CRenderer::Vstring[YaochaoCount].Text = std::to_string(NumberDate.YaocaoSize);
	CRenderer::Vstring[EnemySize].Text = std::to_string(NumberDate.EnemyCountInTheScene);
	CRenderer::Vstring[ForEnemyTiming].Text = std::to_string(NumberDate.CommingTimer)+":00s";
	if (zombieisnotcomming)
	{
		if (NumberDate.CommingTimer > 0.0f)
		{
			ptimerforzombie->Tick();
			if (ptimerforzombie->TotalTime() > 1.0f)
			{
				NumberDate.CommingTimer -= 1.0f;
				ptimerforzombie->Reset();
				if (NumberDate.CommingTimer <= 0.5f)
				{
					NumberDate.CommingTimer = 0.0f;
					ptimerforzombie->Reset();
				}
			}
		}
		else
		{
			NumberDate.CommingTimer = 0.0f;
			ptimerforzombie->Tick();
			if (ptimerforzombie->TotalTime() > 2.0f)
			{
				ZombieManager::Zombieiscomming();
				ptimerforzombie->Reset();
			}
		}
	}
	
	CEnemy* pe = CManager::GetScene()->GetGmeobjs<CEnemy>(6);
	if (NumberDate.EnemyCountInTheScene <= 0.0f&&!isboss)
	{
		UImanager3D* pui = CManager::GetScene()->GetGmeobjs<UImanager3D>(UI_ID);
		pui->RestScene();
		pui->SetSwtichOpen(true);
		NumberDate.StageNum += 1;
		isboss = true;
		NumberDate.EnemyCountInTheScene = 1;
		pe->MoveFirstx();
		/*if (pui->GetFadeBlend() >= 1)
		{
			isboss = true;
			pe->MoveFirstx();
		}*/
		/*for (int i = 0; i < ENEMY_SIZE; i++)
		{
			CZombie_man* pman = CManager::GetScene()->GetGmeobj<CZombie_man>(ENEMY_ID, i);
			if (pman != nullptr)
			{
				pman->SetInitalState(zombie_InitalState);
			}
		}
	
		NumberDate.CommingTimer = 30.0f;
		NumberDate.EnemyCountInTheScene = 10.0f;*/
	}
	//Tool::DeBugMoveV2(CRenderer::Vstring[ForEnemyTiming].Pos);

	if (CInput::GetKeyPress('U'))
	{
		NumberDate.EnemyCountInTheScene = 0;
	}

	for (auto it = Goldpurse.begin(); it!=Goldpurse.end();it++)
	{
		it->ptimer->Tick();
		float timer = it->ptimer->TotalTime();
		it->Pos.y -= timer*10.0f;
		if (timer >= 0.5f)
		{
			it = Goldpurse.erase(it);
			if (it == Goldpurse.end()) break;
		}
	}




}

void CFont::Draw()
{
	UImanager3D* pui = CManager::GetScene()->GetGmeobjs<UImanager3D>(UI_ID);
	if (!pui->GetSceneSwtich())
	{
		CRenderer::spritebich->Begin();
		Text::TextDraw();
		for (int i = 0; i < Goldpurse.size(); i++)
		{
			CRenderer::spritefont->DrawString(CRenderer::spritebich.get(), Tool::StrToWtr(Goldpurse[i].Text).c_str(), Goldpurse[i].Pos, Goldpurse[i].Color, Goldpurse[i].RotSpeed, Goldpurse[i].RotPoint, Goldpurse[i].Scale);
		}
		CRenderer::spritebich->End();
		CRenderer::DrawStringBack();
	}
	else
	{
	}
	
}

GOLDPOOR CFont::GetGold(XMFLOAT2 pos, int money)
{
	GOLDPOOR _gold;
	_gold.Color = Colors::White;
	_gold.Pos = { pos.x,pos.y };
	_gold.Text = "+"+std::to_string(money);
	_gold.ptimer = new Timer();
	_gold.ptimer->Reset();
	_gold.Scale = { 1.0f,1.0f };
	_gold.RotPoint = { 0.0f,0.0f };
	_gold.RotSpeed = 0.0f;

	return _gold;
}

