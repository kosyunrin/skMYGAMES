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
//	// �r���[�}�g���N�X�ݒ�
//	m_InvViewMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
//	m_InvViewMatrix *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
//
//	XMVECTOR det;
//	m_ViewMatrix = XMMatrixInverse(&det, m_InvViewMatrix);
//
//
//	// �v���W�F�N�V�����}�g���N�X�ݒ�
//	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(1.0f, SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);
//
//}
//
