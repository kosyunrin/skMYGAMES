#include"B_header.h"



CWorld::CWorld()
{
}


CWorld::~CWorld()
{
}
void CWorld::Init()
{
	m_Position = XMFLOAT3(0.0f, -30.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(10.0f, 10.0f, 10.0f);


	e_Modle = new CStaticmodle("asset/Onepiece/Castle.fbx",1);


}

void CWorld::Uninit()
{
	delete e_Modle;
}

void CWorld::Update(float dt)
{
}

void CWorld::Draw()
{
	
	XMMATRIX world;
	
	world = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);//转矩阵全部
	world *=XMMatrixRotationRollPitchYaw(XMConvertToRadians(-90), 0.0f, 0.0f);//转矩阵全部
	world *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMStoreFloat4x4(&m_WorldMatirx, world);


	CRenderer::ShadowDraw();
	e_Modle->Render(world);
	CRenderer::ShadowEnd();

}

void CWorld::DrawShadow()
{
	//CShadow* pShadow = CManager::GetScene()->GetGmeobjs<CShadow>(ShadowLight_ID);

	//CRenderer::SetViewMatrix(&pShadow->GetViewMatrix());
	//CRenderer::SetProjectionMatrix(&pShadow->GetProjectionMatrix());


	//e_Modle->Render(GetMatrixForWorld());
}
