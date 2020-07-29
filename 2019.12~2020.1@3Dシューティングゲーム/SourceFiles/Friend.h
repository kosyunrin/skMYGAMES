#pragma once
class Friend:public CGameObject
{
public:
	Friend();
	~Friend();
public:
	void Init();
	void Uninit();
	void Update(float dt);
	void Draw();
	void SetPos(XMFLOAT3 pos);
private:
	//SKinAnimationModel* e_Modle;
	//SkinnedModel* e_Modle;
	//CSkinnedfbxanim* e_Modle;
	CStaticmodle* e_Modle;
	int animation;
	CPolygon* pLife;
	Line* m_line;
	SFriendDate sOOU;
	//CAx* Caxin;
	XMFLOAT4X4 worldd;
};

