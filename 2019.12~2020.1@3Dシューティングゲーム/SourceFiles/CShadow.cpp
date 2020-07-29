#include"B_header.h"





void CShadow::Init()
{

	m_Position = XMFLOAT3(1.0f, 8.5f, 38.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);


}


void CShadow::Uninit()
{
	

}


void CShadow::Update(float dt)
{
	XMVECTOR BeiFace = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0);
	XMVECTOR ZuoFace= XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0);
	Tool::DeBugMoveV3(m_Position);
	CP0* p0 = CManager::GetScene()->GetGmeobjs<CP0>(4);
	XMVECTOR p0now_backFace = Tool::GetNowDir(p0->GetMatrixForWorld(), BeiFace);
	ZuoFace= Tool::GetNowDir(p0->GetMatrixForWorld(), ZuoFace);
	XMVECTOR thispos = p0->GetVectorPos() - p0now_backFace * -1000.0f;
	thispos = thispos - ZuoFace * 400.0f;
	XMStoreFloat3(&m_Position, thispos);
	m_Position.y = 30.0f;


	float Deg = XMVectorGetY(XMVector3AngleBetweenVectors(BeiFace, -p0now_backFace));
	Tool::GET_ANGLE(-p0now_backFace, BeiFace) > 0.0f ? m_Rotation.y = -Deg : m_Rotation.y = Deg;

	CRenderer::Debug_move_v3[0] = m_Position.x;
	CRenderer::Debug_move_v3[1] = m_Position.y;
	CRenderer::Debug_move_v3[2] = m_Position.z;
	//Tool::DeBugMoveV3two(m_Rotation);
	//m_Rotation.y = XMConvertToDegrees(90);
}



void CShadow::Draw()
{
	// ビューマトリクス設定
	m_InvViewMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	m_InvViewMatrix *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	XMVECTOR det;
	m_ViewMatrix = XMMatrixInverse(&det, m_InvViewMatrix);


	// プロジェクションマトリクス設定
	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(1.0f, SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

}

