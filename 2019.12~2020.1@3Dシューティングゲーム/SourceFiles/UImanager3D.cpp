#include"B_header.h"
#include"CPlayerManger.h"



UImanager3D::UImanager3D()
{
}


UImanager3D::~UImanager3D()
{
}

void UImanager3D::Init()
{
	bEquipmentMenu = false;
	SceneOutBlend = 0.0f;
	pPoBButton= std::make_unique<CPolygon>();
	pPoBButton->Init2D_tga(8);
	pZombieRun2D = std::make_unique<CPolygon>();
	pZombieRun2D->Init2D_tga(7);
	pSceneOut = std::make_unique<CPolygon>();
	pSceneOut->Init2D(1);
	SceneSwtich = false;
	pGun = std::make_unique<CPolygon>();
	pGun->Init3D(0);
	m_Position= { -131.0f,11.1f,192.0f };
	Gun2Pos = { 143.0f, 13.6f, 5.2f };
	RedMedicinePos = { 136.0f,10.6f,-144.8f };
	HerbPos = { -136.0f,10.6f,-144.8f };
	
	pYaoshui = std::make_unique<CPolygon>();
	pYaoshui->Init2D(2);
	pGold = std::make_unique<CPolygon>();
	pGold->Init2D(3);
	pGun2 = std::make_unique<CPolygon>();
	pGun2->Init3D(0);
	pTama = std::make_unique<CPolygon>();
	pTama->Init2D(5);
	penemy = std::make_unique<CPolygon>();
	penemy->Init2D(4);

	//
	pTiliyaoshui = std::make_unique<CPolygon>();
	pTiliyaoshui->Init2D(8);

	pTiliyaoshui3D = std::make_unique<CPolygon>();
	pTiliyaoshui3D->Init3D(11);

	pbeijintiao = std::make_unique<CPolygon>();
	pbeijintiao->Init2D(9);

	pYaoshui3D = std::make_unique<CPolygon>();
	pYaoshui3D->Init3D(12);

	movetiao = std::make_unique<CPolygon>();
	movetiao->Init2D(10);
	//candan
	pK = std::make_unique<CPolygon>();
	pK->Init2D(14);
	SQUI = std::make_unique<CPolygon>();
	SQUI->Init2D(15);
	DUI = std::make_unique<CPolygon>();
	DUI->Init2D(16);

	RedYSUI = std::make_unique<CPolygon>();
	RedYSUI->Init2D(8);

	TLYSUI = std::make_unique<CPolygon>();
	TLYSUI->Init2D(2);

	//AddEquipment(Equipment::TiliYaoshiu);// tili yaoshui ==  red hong

	CanDanBlend = 0.0f;
	CandanUIheight = 590;
	candanUIBool = false;
	equipment = Equipment::Gun;
}

void UImanager3D::Uninit()
{
	pPoBButton->UnintTag(8);
	pZombieRun2D->UnintTag(7);
	pSceneOut->Uninit3D(1);
	pGun->Uninit3D(0);
	pYaoshui->Uninit3D(2);
	pGold->Uninit3D(3);
	pGun2->Uninit3D(0);
	pTama->Uninit3D(5);
	penemy->Uninit3D(4);
	pTiliyaoshui->Uninit3D(8);
	pbeijintiao->Uninit3D(9);
	movetiao->Uninit3D(10);
	pTiliyaoshui3D->Uninit3D(11);
	pYaoshui3D->Uninit3D(12);
	pK->Uninit3D(14);
	SQUI->Uninit3D(15);
	DUI->Uninit3D(16);
	RedYSUI->Uninit3D(8);
	TLYSUI->Uninit3D(2);
}

void UImanager3D::Update(float dt)
{
	
	//CRenderer::Debug_move_v2[0] = CInput::GetMouseDate(MOUSEEVENTF_WHEEL);

	CP0* pP0 = CManager::GetScene()->GetGmeobjs<CP0>(4);
	if(SceneSwtich)
	Tool::BlendRunUp(SceneOutBlend, dt, 0.2f);
	if (SceneOutBlend == 1.0f) SceneSwtich = false;
	//float controlfloat = -1.0f;
	//|| CInput::GetKeyTrigger(MOUSEEVENTF_LEFTDOWN)
	if (CInput::GetKeyTrigger(VK_DOWN)|| CInput::GetKeyTrigger('S'))
	{
		controlfloat = 1.0f;
		candanUIBool = true;
	}
	else if(CInput::GetKeyTrigger(VK_UP) || CInput::GetKeyTrigger('W'))
	{
		controlfloat = -1.0f;
		candanUIBool = true;
	}
	if (candanUIBool)
	{
		Tool::BlendRunUp(CanDanBlend, dt, 10.0f);
	}
	if (CanDanBlend == 1.0f)
	{
		candanUIBool = false;
		controlfloat >= 1.0f ? CandanUIheight += 110.0f : CandanUIheight -= 110.0f;
		if (CandanUIheight < 590)CandanUIheight = 590;
		else if (CandanUIheight > 700+Vector_Equipment.size()*110) CandanUIheight = 700 + Vector_Equipment.size() * 110;
		CanDanBlend = 0.0f;
	}

	if (bEquipmentMenu)
	{
		CCameraOne* pc = CManager::GetScene()->GetGmeobjs<CCameraOne>(_Camera);
		pc->SetSunAmbient(COLOR(0.01f, 0.01f, 0.01f, 0.01f));
		switch (equipment)
		{
		case Equipment::Gun:
			if (CInput::GetKeyTrigger(VK_LBUTTON))
			{
				pP0->SetMiaozhunPos(XMFLOAT2(SCREEN_WIDTH / 2 + 50.0f, SCREEN_HEIGHT / 2 + 10.0f));
				pP0->SetMyWeapon_Type(WEAPON::Type::Gun);
				pc->SetSunAmbient(COLOR(0.4f, 0.4f, 0.4f, 0.4f));
				bEquipmentMenu = false;
			}
			break;
		case Equipment::Knife:
			if (CInput::GetKeyTrigger(VK_LBUTTON))
			{
				pP0->SetMiaozhunPos(XMFLOAT2(SCREEN_WIDTH / 2 - 200.0f, SCREEN_HEIGHT / 2 + 110.0f));
				pP0->SetMyWeapon_Type(WEAPON::Type::knfie);
				pc->SetSunAmbient(COLOR(0.4f, 0.4f, 0.4f, 0.4f));
				bEquipmentMenu = false;
			}
			break;
		case Equipment::YaoShui:
			if (CInput::GetKeyTrigger(VK_LBUTTON))
			{
				CFont* pf = CManager::GetScene()->GetGmeobjs<CFont>(FONT_ID);
				SNumber* pdate = pf->GetNumDatePtr();
				pdate->YaocaoSize -= 1.0f;
				pP0->GetP0Dataptr()->HP += 5.0f;
				if (pdate->YaocaoSize <= 0.0)
				{
					pdate->YaocaoSize = 0.0f;
					DeleteEquipment(Equipment::YaoShui);
				}
				pc->SetSunAmbient(COLOR(0.4f, 0.4f, 0.4f, 0.4f));
				bEquipmentMenu = false;
			}
			break;
		case Equipment::TiliYaoshiu:
			if (CInput::GetKeyTrigger(VK_LBUTTON))
			{
			
				pc->SetSunAmbient(COLOR(0.4f, 0.4f, 0.4f, 0.4f));
				bEquipmentMenu = false;
			}
			break;
		}
	}
		
}

void UImanager3D::Draw()
{
	CP0* pP0 = CManager::GetScene()->GetGmeobjs<CP0>(4);


	//3D
	XMFLOAT3 rot = {24.0f,10.9f,0.1f};

	XMMATRIX Gunworld;
	Gunworld = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
	Gunworld *= XMMatrixScaling(1.0f, 1.0f, 1.0f);
	Gunworld *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);


	XMMATRIX Gunworld2;
	Gunworld2 = XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
	Gunworld2 *= XMMatrixScaling(1.0f, 1.0f, 1.0f);
	Gunworld2 *= XMMatrixTranslation(Gun2Pos.x, Gun2Pos.y, Gun2Pos.z);

	XMMATRIX tiliyaoji;
	tiliyaoji = XMMatrixRotationRollPitchYaw(7.8f, 3.2f, 0.0f);
	tiliyaoji *= XMMatrixScaling(1.0f, 1.0f, 1.0f);
	tiliyaoji *= XMMatrixTranslation(RedMedicinePos.x, RedMedicinePos.y, RedMedicinePos.z);

	XMMATRIX tiliyaoji2;
	tiliyaoji2 = XMMatrixRotationRollPitchYaw(7.8f, 3.2f, 0.0f);
	tiliyaoji2 *= XMMatrixScaling(1.0f, 1.0f, 1.0f);
	tiliyaoji2 *= XMMatrixTranslation(HerbPos.x, HerbPos.y, HerbPos.z);

	pGun->DrawPlayerLife(0.0f, 0.0f, 0.0f, 7.0f, 7.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0, Gunworld);

	pGun2->DrawPlayerLife(0.0f, 0.0f, 0.0f, 7.0f, 7.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0, Gunworld2);
	pTiliyaoshui3D->DrawPlayerLife(0.0f, 0.0f, 0.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 11, tiliyaoji);
	pYaoshui3D->DrawPlayerLife(0.0f, 0.0f, 0.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 12, tiliyaoji2);
	
	

	//2D
	if (SceneSwtich)
	{
		pSceneOut->PNGDraw2D(0, 0, 1920, 1080, 1, SceneOutBlend);
	}
	//zhuangei
	float SQUIPOS = CandanUIheight + 110 * CanDanBlend*controlfloat;
	float DUIPOS = CandanUIheight - 110 + 110 * CanDanBlend*controlfloat;
	float EQUIPOS_ADD_ONE = CandanUIheight - 220 + 110 * CanDanBlend*controlfloat;
	float EQUIPOS_ADD_TWO = CandanUIheight - 330 + 110 * CanDanBlend*controlfloat;
	//RedYSUI->PNGDraw2D(900, EQUIPOS_ADD_ONE, 105, 65, 8, 1.0f);
	//TLYSUI->PNGDraw2D(900, EQUIPOS_ADD_TWO, 105, 65, 2, 1.0f);
	if (bEquipmentMenu)
	{
		SQUI->PNGDraw2D(900, SQUIPOS, 105, 55, 15, 1.0f);
		for (int i = 0; i < Vector_Equipment.size(); i++)
		{
			float pos;
			int textID = Vector_Equipment[i].textID;
			switch (i)
			{
			case 0:
				pos = EQUIPOS_ADD_ONE;
				break;
			case 1:
				pos = EQUIPOS_ADD_TWO;
				break;
			}
			if (pos == 590)
			{
				switch (textID)
				{
				case 2:
					equipment = Equipment::TiliYaoshiu;
					break;
				case 8:
					equipment = Equipment::YaoShui;
					break;
				}
			}
			Vector_Equipment[i].pEquipment->PNGDraw2D(900, pos, 105, 65, textID, 1.0f);
		}
		DUI->PNGDraw2D(900, DUIPOS, 120, 70, 16, 1.0f);
		pK->PNGDraw2D(815, 505, 290, 186, 14, 1.0f);
		if (SQUIPOS == 590) equipment = Equipment::Gun;
		else if (DUIPOS == 590) equipment = Equipment::Knife;
	}

	///
	pYaoshui->PNGDraw2D(50.0f, 860.0f, 80.0f, 80.0f, 2, 1.0f);
	pTiliyaoshui->PNGDraw2D(50.0f, 700.0f, 80.0f, 80.0f, 8, 1.0f);
	if (pP0 != nullptr)
	{
		movetiao->PNGDraw2D(156.0f + 2.7f, 907.6f +3.1f, pP0->GetP0Dataptr()->PhysicalBar, 21.9f-4.8f, 10, 1.0f);
	}
	pbeijintiao->PNGDraw2D(156.0f,904.0f, 300.0f, 30.0f, 9, 1.0f);
	pGold->PNGDraw2D(1600.0f, 810.0f, 50.0f, 50.0f,3, 1.0f);
	pTama->PNGDraw2D(1600.0f, 906, 50.0f, 50.0f, 5, 1.0f);
	penemy->PNGDraw2D(1700.0f,28.04f, 50.0f, 50.0f, 4, 1.0f);
	CFont* pf = CManager::GetScene()->GetGmeobjs<CFont>(FONT_ID);
	float zombiespeed=0.0f;
	pf->GetNumDatePtr()->CommingTimer > 0.0f ? zombiespeed = 0.0f : zombiespeed = 0.3f;
	pZombieRun2D->Draw_animation2D(958, 96, 30.f, 30.f, 7, 8, 1, zombiespeed);


	for (int i = 0; i < 2; i++)
	{
		CBlueArmy* pBarmy = CManager::GetScene()->GetGmeobj<CBlueArmy>(5, i);
		//BARMYDATE *sBadte = pBarmy->GetsBdate();
		//sBadte->life = 200.0f;
		if (pBarmy!=nullptr)
		{
			BARMYDATE *sBadte = pBarmy->GetsBdate();
			int lifesize = 100;
			float lifeW = sBadte->life / lifesize;
			XMMATRIX w = sBadte->pLife->Getlifeworld();
			sBadte->pLife->DrawPlayerLife(-1.0f, 5.0f, -1.0f, lifeW, 0.2f, 1.0f, 1.0f, 1.0f, 1.0f, 3, w);
		}
	}
	for (int i = 0; i < 2; i++)
	{
		CRedArmy* pRarmy = CManager::GetScene()->GetGmeobj<CRedArmy>(6, i);
		//BARMYDATE *sBadte = pBarmy->GetsBdate();
		//sBadte->life = 200.0f;
		if (pRarmy != nullptr)
		{
			BARMYDATE *sRadte = pRarmy->GetsRdate();
			int lifesize = 100;
			float lifeW = sRadte->life / lifesize;
			XMMATRIX w = sRadte->pLife->Getlifeworld();
			sRadte->pLife->DrawPlayerLife(-1.0f, 5.0f, -1.0f, lifeW, 0.2f, 1.0f, 1.0f, 1.0f, 1.0f, 0, w);
		}
	}
	//playerlife
	CPlayer* pPlayer = CManager::GetScene()->GetGmeobjs<CPlayer>(3);
	if (pPlayer != nullptr)
	{
		LPlayerOneDate* sP0Date = pPlayer->GetP0Date();
		int lifesize = 1000;
		float lifeW = sP0Date->life / lifesize;
		XMMATRIX  w = sP0Date->pLife->Getlifeworld();
		sP0Date->pLife->DrawPlayerLife(-1.0f, 7.0f, -1.0f, lifeW, 0.2f, 1.0f, 1.0f, 1.0f, 1.0f, 0, w);
	}
	//Bhoulife
	SoldierHouseBlue* pBhouse = CManager::GetScene()->GetGmeobjs<SoldierHouseBlue>(7);
	if (pBhouse != nullptr)
	{
		House* sBDate = pBhouse->GetDate_house();
		int lifesize = 1000;
		float lifeW = sBDate->HP / lifesize;
		XMMATRIX  w = sBDate->pLife->Getlifeworld();
		sBDate->pLife->DrawPlayerLife(-1.0f, 7.0f, -1.0f, lifeW, 0.2f, 1.0f, 1.0f, 1.0f, 1.0f, 3, w);
	}
	if (pP0 != nullptr)
	{

		if(pP0->GetZhunXS())
		pP0->GetZhunxin()->PNGDraw2D(pP0->Get_ZXpos().x, pP0->Get_ZXpos().y, pP0->Get_ZXWH(), pP0->Get_ZXWH(), 6,pP0->Get_color());

		float a = 0.0f;
		a = 0.2f*5.0f / pP0->GetP0Dataptr()->HP;

		if(pP0->GetP0Dataptr()->BeHurtAnimControl)
		pPoBButton->Draw_animation2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 150.0f, 100.0f, 8, 2,1,0.3f);

		//pP0->GetZhunxin()->PNGDraw2D(0, 0, 1920, 1080, 7, a);///blood bei jing
		//pP0->GetZhunxin()->PNGDraw2D(0, 0, 10.0f, 10.0f, 8, 1.0f);
	

	}
	CEnemy* pe = CManager::GetScene()->GetGmeobjs<CEnemy>(6);
	if (pe != nullptr)
	{
		ZOMBIEDATE*  date = pe->Get_Date();
		if(date->Currentanim==Zombie_hurt)
		date->pBlood->Draw_animation2D(SCREEN_WIDTH / 2 + 110.0f, SCREEN_HEIGHT / 2 - 15.0f, 50.0f, 100.0f, 7, 6, 1, 0.3f);
	}




}

