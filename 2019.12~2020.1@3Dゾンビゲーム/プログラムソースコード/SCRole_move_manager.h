#pragma once
class CCamera;
class SCRole_move_manager
{
public:
	SCRole_move_manager();
	~SCRole_move_manager();
public:
	static XMVECTOR Lookat(XMFLOAT3 RolePos, XMFLOAT2 mousePos, CCamera* pcamera);
	static float Distance(XMVECTOR& PlPos , XMFLOAT2 mousePos,XMFLOAT3& m_pos);
};

