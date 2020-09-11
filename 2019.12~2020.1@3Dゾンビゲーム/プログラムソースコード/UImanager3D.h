#pragma once
class UImanager3D :public CGameObject
{
public:
	UImanager3D();
	~UImanager3D();
	void Init();
	void Uninit();
	void Update(float dt);
	void Draw();
private:
	Equipment equipment;
	bool bEquipmentMenu;
	std::unique_ptr<CPolygon> pPoBButton;
	std::unique_ptr<CPolygon> pZombieRun2D;
	std::unique_ptr<CPolygon> pSceneOut;
	std::unique_ptr<CPolygon> pGun;
	std::unique_ptr<CPolygon> pGun2;
	std::unique_ptr<CPolygon> pYaoshui;
	std::unique_ptr<CPolygon> pGold;
	std::unique_ptr<CPolygon> pTama;
	std::unique_ptr<CPolygon> penemy;
	std::unique_ptr<CPolygon> pTiliyaoshui;
	std::unique_ptr<CPolygon> pbeijintiao;
	std::unique_ptr<CPolygon> movetiao;
	std::unique_ptr<CPolygon> pTiliyaoshui3D;
	std::unique_ptr<CPolygon> pYaoshui3D;
	std::unique_ptr<CPolygon> pK;
	std::unique_ptr<CPolygon> SQUI;
	std::unique_ptr<CPolygon> DUI;
	std::unique_ptr<CPolygon> RedYSUI;
	std::unique_ptr<CPolygon> TLYSUI;
	std::unique_ptr<CPolygon> Balck;
	std::unique_ptr<CPolygon> BossLife;
	std::unique_ptr<CPolygon> Sm;
	std::vector<EquipmentUI> Vector_Equipment;
	float controlfloat;
	bool candanUIBool;
	float CanDanBlend;
	float CandanUIheight;
	XMFLOAT3 Gun2Pos;
	XMFLOAT3 RedMedicinePos;
	XMFLOAT3 HerbPos;
	float SceneOutBlend;
	bool SceneSwtich;
public:
	void AddEquipment(Equipment equipment)
	{
		EquipmentUI asd1;

		switch (equipment)
		{
		case Equipment::Gun:
			break;
		case Equipment::Knife:
			break;
		case Equipment::YaoShui:

			asd1.pEquipment = RedYSUI.get();
			asd1.textID = (8);
			Vector_Equipment.push_back(asd1);
			break;
		case Equipment::TiliYaoshiu:
			asd1.pEquipment = TLYSUI.get();
			asd1.textID = (2);
			Vector_Equipment.push_back(asd1);
			break;
		}
	}
	void DeleteEquipment(Equipment equipment)
	{
		int textNum;
		switch (equipment)
		{
		case Equipment::Gun:
			break;
		case Equipment::Knife:
			break;
		case Equipment::YaoShui:
			textNum = 8;
			break;
		case Equipment::TiliYaoshiu:
			textNum = 2;
			break;
		}
		for (auto it = Vector_Equipment.begin(); it != Vector_Equipment.end(); it++) {

			if (it->textID == textNum)
				it = Vector_Equipment.erase(it);
			if (it == Vector_Equipment.end()) break;
		}
	}
	void SetSwtichOpen(bool x)
	{
		SceneSwtich = true;
	}
	void RestScene()
	{
		SceneOutBlend = 0.0f;
		SceneSwtich = false;
	}
	int GetFadeBlend() { return SceneOutBlend; }
	bool GetSceneSwtich() { return SceneSwtich; }
	XMFLOAT3 GetGun2Pos() { return Gun2Pos; }
	XMFLOAT3 GetRedPos() { return RedMedicinePos; }
	XMFLOAT3 GetHerbPos() { return HerbPos; }
	void SetEquipmentSwitch()
	{
		bEquipmentMenu = !bEquipmentMenu;
	}
	bool GetEquipmentSwitch()
	{
		return bEquipmentMenu;
	}
};

