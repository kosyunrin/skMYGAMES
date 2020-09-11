#include "TitleScene.h"



UICamera::UICamera()
{
}


UICamera::~UICamera()
{
}

void UICamera::Init()
{
	m_Viewport.left = 0;
	m_Viewport.top = 0;
	m_Viewport.right = SCREEN_WIDTH;
	m_Viewport.bottom = SCREEN_HEIGHT;


	m_Position = { 0.0f,0.0f,1.0f };
	Target = { 0.0f,0.0f,0.0f };
	Upcam = { 0.0f, 1.0f, 0.0f };
	Forwardcam = { 0.0f, 0.0f, 1.0f };
	Rightcam = { 1.0f, 0.0f, 0.0f };



	m_spotlight.ambient = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_spotlight.diffuse = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_spotlight.specular = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_spotlight.position = XMFLOAT3(-2.0f, 0.4f, 0.4f);
	m_spotlight.direction = XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_spotlight.constant = 1.0f;
	m_spotlight.Linear = 0.09f;
	m_spotlight.quadratic = 0.032f;//fanwei
	m_spotlight.cutOff = std::cos(XMConvertToRadians(0.1f));
	m_spotlight.outerCutOff = std::cos(XMConvertToRadians(15.0f));
}

void UICamera::Uninit()
{
}

void UICamera::Update(float dt)
{
	XMVECTOR camPosition;
	XMVECTOR camTarget = XMLoadFloat3(&Target);
	XMVECTOR camForward = XMLoadFloat3(&Forwardcam);
	XMVECTOR camRight = XMLoadFloat3(&Rightcam);

	XMVECTOR DefaultForward = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
	XMMATRIX camRotationMatrix;
	camRotationMatrix = XMMatrixRotationRollPitchYaw(camPitch, camYaw, 0);
	camPosition = XMVector3TransformNormal(DefaultForward, camRotationMatrix);
	camPosition = XMVector3Normalize(camPosition);
	float CamToPlayer = 6.0f;
	camPosition = ((camPosition * CamToPlayer) + camTarget);

	bool Alt = false;
	if (CInput::GetKeyPress('K'))
		Alt = true;
	if (!Alt)
		camForward = XMVector3Normalize(camTarget - camPosition);
	camForward = XMVectorSetY(camForward, 0.0f);
	camRight = XMVectorSet(-XMVectorGetZ(camForward), 0.0f, XMVectorGetX(camForward), 0.0f);
	camRight = XMVector3Normalize(camRight);

	XMStoreFloat3(&m_Position, camPosition);
	XMStoreFloat3(&Forwardcam, camForward);
	XMStoreFloat3(&Rightcam, camRight);
}

void UICamera::Draw()
{
	// ビューポート設定
	D3D11_VIEWPORT dxViewport;
	dxViewport.Width = (float)(m_Viewport.right - m_Viewport.left);
	dxViewport.Height = (float)(m_Viewport.bottom - m_Viewport.top);
	dxViewport.MinDepth = 0.0f;
	dxViewport.MaxDepth = 1.0f;
	dxViewport.TopLeftX = (float)m_Viewport.left;
	dxViewport.TopLeftY = (float)m_Viewport.top;
	dm_Viewport = dxViewport;

	CRenderer::GetDeviceContext()->RSSetViewports(1, &dxViewport);

	XMFLOAT3 lightPos = { 0.0f,-11.0f,13.70f };
	//Tool::DeBugMoveV3(lightPos);
	m_spotlight.position = lightPos;

	//m_spotlight.direction = Rightcam;
	CRenderer::SetSpotLight(m_spotlight);

	XMMATRIX XcamView;
	XcamView = XMMatrixLookAtLH(XMLoadFloat3(&m_Position), XMLoadFloat3(&Target), XMLoadFloat3(&Upcam));
	CRenderer::SetViewMatrix(&XcamView);
	XMStoreFloat4x4(&camView, XcamView);

	XMMATRIX camProjection;
	camProjection = XMMatrixPerspectiveFovLH(0.4f*3.14f, dxViewport.Width / dxViewport.Height, 1.0f, 1000.0f);
	XMStoreFloat4x4(&camPro, camProjection);

	CRenderer::SetProjectionMatrix(&camProjection);

}
void UICamera::set(XMVECTOR camTarget1)
{
	XMStoreFloat3(&Target, camTarget1);
}

XMVECTOR UICamera::getForward()
{
	return XMLoadFloat3(&Forwardcam);
}

XMVECTOR UICamera::getcamRight()
{
	return XMLoadFloat3(&Rightcam);
}

float UICamera::getangle()
{
	return camYaw;
}


XMVECTOR UICamera::getTarget()
{
	return XMLoadFloat3(&Target);
}

XMVECTOR UICamera::getCamUp()
{
	return XMLoadFloat3(&Upcam);
}

XMMATRIX UICamera::get_VIEWMatrix()
{
	return XMLoadFloat4x4(&camView);
}

