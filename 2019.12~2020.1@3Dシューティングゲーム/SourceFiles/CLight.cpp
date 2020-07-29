//#include"B_header.h"
//
//
//
//
//
//void CLight::Init()
//{
//
//	m_Position = XMFLOAT3(-2.0f, 5.0f, -10.0f);
//	m_Rotation = XMFLOAT3(0.5f, 0.5f, 0.0f);
//	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
//
//
//}
//
//
//void CLight::Uninit()
//{
//
//
//}
//
//
//void CLight::Update()
//{
//}
//
//
//
//void CLight::Draw()
//{
//	// ビューマトリクス設定
//	m_InvViewMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
//	m_InvViewMatrix *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
//
//	XMVECTOR det;
//	m_ViewMatrix = XMMatrixInverse(&det, m_InvViewMatrix);
//
//
//	// プロジェクションマトリクス設定
//	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(1.0f, SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);
//
//}
//
