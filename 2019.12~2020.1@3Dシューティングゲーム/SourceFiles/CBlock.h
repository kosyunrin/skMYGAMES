#pragma once
class CBlock : public CGameObject
{
public:
	CBlock();
	~CBlock();
public:
	void Init();
	void Uninit();
	void Update(float dt);
	void Draw();
private:
	CSkinnedfbxanim* pModle;
	CStaticmodle* pSmode;
public:
	CStaticmodle* Get_pMode() { return pSmode; }
	XMMATRIX GetXMATRIX()
	{
		XMMATRIX worlds;
		worlds = XMMatrixRotationRollPitchYaw(XMConvertToRadians(-90.0f), 0.0f, 0.0f);
		worlds *= XMMatrixScaling(0.20f, 0.20f, 0.20f);
		worlds *= XMMatrixTranslation(6.0f, 0.0f, 30.0f);
		return worlds;
	}
	
};

