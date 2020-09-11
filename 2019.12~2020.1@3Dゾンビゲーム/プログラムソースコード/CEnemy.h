#pragma once
class BossState;
class Weakness;
class CEnemy:public CGameObject
{
public:
	CEnemy();
	~CEnemy();
public:
	void Init();
	void Uninit();
	void Update(float dt);
	void Draw();
private:
	CSkinnedfbxanim* pModle;
	//std::unique_ptr<Weakness> pWeakness;
	Line* m_line;
	BoundingBox m_box;
	XMFLOAT4X4 Matrix_World;
	XMFLOAT4X4 Matrix_Box;
	XMFLOAT4X4 Matrix_HeadBox;
	ZOMBIEDATE sDate;
	BossState* pBossState = nullptr;
	XMVECTOR NowfaceDir;
	XMVECTOR TargetDir = {1,0,0,0};
	std::unique_ptr<AStarPathFinding> pAstar;
	std::unique_ptr<Weakness> pWeakness;
public:
	BoundingBox Get_box();
	BoundingBox Get_HeadBox();
	BoundingSphere Get_Sphere();
	BoundingSphere GetEyeSphereBox();
	BoundingBox GetBodySphereBox();
	XMVECTOR XMGet_pos() { return XMLoadFloat3(&m_Position); }
	void SetTriangle(XMFLOAT3* Vpos);
	ZOMBIEDATE* Get_Date() { return &sDate; }
	CSkinnedfbxanim* GetpAnim() { return pModle; }
	XMMATRIX XMGet_WorldMatrix() { return XMLoadFloat4x4(&Matrix_World); }
	XMVECTOR GetNowFaceDir() { return XMVector3Normalize(NowfaceDir); }
	XMVECTOR GetTargetDir() { return TargetDir; }
	void MoveRot();
	void Move();
	void MoveAstar();
	void MoveAstarRot();
	void MoveAstarPatrol();
	void MoveBackx();
	template<int T>
	void MoveRotFreeActionx();
	void MoveAttackx();
	void MoveHurtx();
	void MoveWeaknessx();
	void MoveStandupx();
	void MoveFirstx();


	XMFLOAT3 GetpWeakPos();

	void SetTargetDir(XMVECTOR targdir) { TargetDir = targdir; }
	void SetAnimaState(ZOMBIEDATE SDate)
	{
		sDate.Currentanim = SDate.Currentanim;
	}
	BossState* GetState()
	{
		return pBossState;
	}
	AStarPathFinding* GetPointForAstar() { return pAstar.get(); }
	//Weakness* GetpWeakness() { return pWeakness.get(); }
};


