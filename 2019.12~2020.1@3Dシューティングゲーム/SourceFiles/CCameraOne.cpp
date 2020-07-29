#include"B_header.h"
#include <fstream>




void CCameraOne::Init()
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



	m_spotlight.ambient = XMFLOAT3(100.0f, 100.0f, 100.0f);
	m_spotlight.diffuse = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_spotlight.specular = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_spotlight.position = XMFLOAT3(0.0f, 0.0f, 10.0f);
	m_spotlight.direction = XMFLOAT3(0.0f, -0.09f, 1.0f);
	m_spotlight.constant = 1.0f;
	m_spotlight.Linear = 0.09f;
	m_spotlight.quadratic = 0.032f;//fanwei
	m_spotlight.cutOff = std::cos(XMConvertToRadians(-0.1f));
	m_spotlight.outerCutOff = std::cos(XMConvertToRadians(19.0f));

	Sun.Direction = XMFLOAT4(0.0f, -1.0f, 0.0f, 0.0f);
	Sun.Diffuse = COLOR(0.0f, 0.0f, 0.0f,0.0f);
	Sun.Ambient = COLOR(0.4f, 0.4f, 0.4f, 0.4f);
	Sun.Specular = { 0.5f, 0.5f, 0.5f ,0.0f };
	Sun.CameraPos = { m_Position.x,m_Position.y,m_Position.z,0.0f };

	//CRenderer::SetSpotLight(m_spotlight);
}


void CCameraOne::Uninit()
{
}


void CCameraOne::Update(float dt)
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
	//camForward = XMVectorSetY(camForward, 0.0f);
	camRight = XMVectorSet(-XMVectorGetZ(camForward), 0.0f, XMVectorGetX(camForward), 0.0f);
	camRight = XMVector3Normalize(camRight);

	CP0* pp0 = CManager::GetScene()->GetGmeobjs<CP0>(4);
	if (!CInput::GetKeyPress('T'))
	{
		if (!pp0->GetP0Dataptr()->BeHurtAnimControl&&pp0->GetP0Dataptr()->CurrentAnim != _NQdie)
		{
			camYaw += CInput::GetmouseX()*0.001f;
			camPitch += CInput::GetmouseY()*0.001f;
			if (pp0->GetP0Dataptr()->CurrentAnim != _miaozhun && pp0->GetP0Dataptr()->CurrentAnim != _NAttack)
			{
				if (std::abs(GamePad::ThumbRX()) > 0.1f)
					camYaw += GamePad::ThumbRX()*0.05f;
				if (std::abs(GamePad::ThumbRY()) > 0.1f)
					camPitch += GamePad::ThumbRY()*-0.05f;
			}
			else
			{
				if (std::abs(GamePad::ThumbRX()) > 0.1f)
					camYaw += GamePad::ThumbRX()*0.01f;
				if (std::abs(GamePad::ThumbRY()) > 0.1f)
					camPitch += GamePad::ThumbRY()*-0.01f;
			}
			if (camPitch > 0.8f)
				camPitch = 0.8f;
			if (camPitch < -0.5f)
				camPitch = -0.5f;
		}
		XMStoreFloat3(&m_Position, camPosition);
		XMStoreFloat3(&Forwardcam, camForward);
		XMStoreFloat3(&Rightcam, camRight);


	}
	//Tool::MoveLight(m_spotlight);
	Sun.CameraPos = { m_Position.x,m_Position.y,m_Position.z,0.0f };
	//Tool::MoveSun(Sun);
	XMFLOAT3 SpotDir = { camPitch,camYaw,0.0f };
	//XMStoreFloat3(&SpotDir,Tool::GetNowFaceDir(pp0->GetMatrixForWorld())*XMMatrixRotationX(CRenderer::Debug_move_v2[0]);
	m_spotlight.direction = Forwardcam;

	XMVECTOR SpotPos = XMLoadFloat3(&m_Position)+ XMLoadFloat3(&Forwardcam)*7.5f;
	XMStoreFloat3(&m_spotlight.position, SpotPos);
	//+XMLoadFloat3(&SpotDir)*130.0f

}



void CCameraOne::Draw()
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

	//Tool::DeBugMoveV3(lightPos);
	//m_spotlight.position = lightPos;
	
	//m_spotlight.direction = Forwardcam;
	CShadow* pShadow = CManager::GetScene()->GetGmeobjs<CShadow>(ShadowLight_ID);
	XMStoreFloat4x4(&Sun.View, XMMatrixTranspose(pShadow->GetViewMatrix()));
	XMStoreFloat4x4(&Sun.Pro, XMMatrixTranspose(pShadow->GetProjectionMatrix()));
	CRenderer::SetLight(Sun);


	CRenderer::SetSpotLight(m_spotlight);
	
	//CRenderer::SetLight(paralletLight);

	XMMATRIX XcamView;
	XcamView = XMMatrixLookAtLH(XMLoadFloat3(&m_Position), XMLoadFloat3(&Target), XMLoadFloat3(&Upcam));
	CRenderer::SetViewMatrix(&XcamView);
	XMStoreFloat4x4(&camView, XcamView);

	XMMATRIX camProjection;
	camProjection = XMMatrixPerspectiveFovLH(0.4f*3.14f, dxViewport.Width / dxViewport.Height, 1.0f, 1000.0f);
	XMStoreFloat4x4(&camPro, camProjection);

	CRenderer::SetProjectionMatrix(&camProjection);




}
void CCameraOne::set(XMVECTOR camTarget1)
{
	XMStoreFloat3(&Target, camTarget1);
}

XMVECTOR CCameraOne::getForward()
{
	return XMLoadFloat3(&Forwardcam);
}

XMVECTOR CCameraOne::getcamRight()
{
	return XMLoadFloat3(&Rightcam);
}

float CCameraOne::getangle()
{
	return camYaw;
}


XMVECTOR CCameraOne::getTarget()
{
	return XMLoadFloat3(&Target);
}

XMVECTOR CCameraOne::getCamUp()
{
	return XMLoadFloat3(&Upcam);
}

XMMATRIX CCameraOne::get_VIEWMatrix()
{
	return XMLoadFloat4x4(&camView);
}
