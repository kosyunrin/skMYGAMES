#include"main.h"
#include"input.h"
#include "SCRole_move_manager.h"
#include"game_object.h"
#include"camera.h"


SCRole_move_manager::SCRole_move_manager()
{
}


SCRole_move_manager::~SCRole_move_manager()
{
}

XMVECTOR SCRole_move_manager::Lookat(XMFLOAT3 RolePos, XMFLOAT2 mousePos, CCamera* pcamera)
{
	//CCamera* ge = CManager::GetScene()->GetGmeobjs<CEnemy>(_Enemy)
		// 将屏幕坐标点从视口变换回NDC坐标系
	static const XMVECTORF32 D = { { { -1.0f, 1.0f, 0.0f, 0.0f } } };
	XMVECTOR V = XMVectorSet(mousePos.x, mousePos.y, 0.0f, 1.0f);
	D3D11_VIEWPORT viewPort = pcamera->GetViewPort();

	XMVECTOR Scale = XMVectorSet(viewPort.Width * 0.5f, -viewPort.Height * 0.5f, viewPort.MaxDepth - viewPort.MinDepth, 1.0f);
	Scale = XMVectorReciprocal(Scale);

	XMVECTOR Offset = XMVectorSet(-viewPort.TopLeftX, -viewPort.TopLeftY, -viewPort.MinDepth, 0.0f);
	Offset = XMVectorMultiplyAdd(Scale, Offset, D.v);

	// 从NDC坐标系变换回世界坐标系
	XMMATRIX Transform = XMMatrixMultiply(pcamera->GetViewXM(), pcamera->GetProjXM());
	Transform = XMMatrixInverse(nullptr, Transform);

	XMVECTOR mouseTarget = XMVectorMultiplyAdd(V, Scale, Offset);
	mouseTarget = XMVector3TransformCoord(mouseTarget, Transform);
	XMFLOAT3 asd;
	XMStoreFloat3(&asd, mouseTarget);




	XMVECTOR x = XMLoadFloat3(&RolePos);
	XMVECTOR role_vector = XMVector3Normalize( XMVectorSetY(x, 0.0f));

	//XMFLOAT2 xx = XMFLOAT2(mousePos.x, mousePos.y);
	//XMVECTOR mouseVector = XMVector2Normalize(XMLoadFloat2(&xx));
	XMVECTOR Role_move_direction = XMVector3Normalize(mouseTarget - role_vector);
	XMVECTOR Role_move_direction2 = XMVectorSetY(Role_move_direction, 0.0f);
	return Role_move_direction2;
}

float SCRole_move_manager::Distance(XMVECTOR& PlPos,XMFLOAT2 mousePos, XMFLOAT3& m_pos)
{
	XMStoreFloat3(&m_pos,PlPos);
	float dis;
	dis = sqrt((mousePos.x - m_pos.x)*(mousePos.x - m_pos.x) + (mousePos.y - m_pos.y)*(mousePos.y - m_pos.y));
	return dis;
}
