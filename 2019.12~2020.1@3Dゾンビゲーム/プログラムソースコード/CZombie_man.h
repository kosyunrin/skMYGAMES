#pragma once
class Music;
class CZombie_man :public CGameObject ,public FSM_AI, public CBlackBloard
{
public:
	CZombie_man();
	~CZombie_man();
public:
	void Init();
	void Uninit();
	void Update(float dt);
	void Draw();
private:
	std::unique_ptr<Music> m_music;
	CSkinnedfbxanim* pModle;
	Line* m_line;
	BoundingBox m_box;
	BoundingBox mheadBox;
	XMFLOAT4X4 Matrix_Box;
	XMFLOAT4X4 Matrix_HeadBox;
	std::unique_ptr<Timer> ptimer;
	std::unique_ptr<CObjPhySics> PhySics;
	
public:
	void SetAtRestPos(int a, int b);
	void SetInitalState(ZombieState state);
	BoundingBox Get_box();
	BoundingBox Get_HeadBox();
	BoundingBox Get_ColliderBox()
	{
		XMMATRIX Collider;
		Collider = XMMatrixRotationRollPitchYaw(XMConvertToRadians(90), 0.0f, 0.0f);//转矩阵全部
		Collider *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);//转矩阵全部
		Collider *= XMMatrixScaling(m_Scale.x - 0.005f, m_Scale.y - 0.025f, m_Scale.z + 0.3f);
		Collider *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

		BoundingBox box;
		m_box.Transform(box, Collider);
		return box;
	}
	BoundingBox GetBoxForRay()
	{
		XMMATRIX M_bodyW;
		M_bodyW = XMMatrixRotationRollPitchYaw(XMConvertToRadians(90), 0.0f, 0.0f);//转矩阵全部
		M_bodyW *= XMMatrixScaling(m_Scale.x - 0.065f, m_Scale.y - 0.025f, m_Scale.z + 0.05f);
		M_bodyW *= XMMatrixTranslation(m_Position.x, m_Position.y+10.0f, m_Position.z);
		BoundingBox box;
		m_box.Transform(box, M_bodyW);
		return box;
	}
	void SetTriangle(XMFLOAT3* Vpos);

	//AI 
public:
	void   FSMMove(float dt) override;
	void   UNMove(float dt) override;
	bool	  isBool(int index) override;
	//BET
private:
	CBET_Node* BetRoot=NULL;
	bool once = false;
	bool once2 = false;
};


