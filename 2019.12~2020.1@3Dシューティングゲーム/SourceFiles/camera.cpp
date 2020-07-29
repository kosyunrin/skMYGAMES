#include"B_header.h"
#include"input.h"


void CCamera::Init()
{
	//CRenderer::Debug_move_Rotation3[0] = 70.0f;
	m_Position = XMFLOAT3(0.0f, CamPosH, -10.0f);
	m_Rotation = XMFLOAT3(XMConvertToRadians(CamRotX), 0.0f, 0.0f);


	m_Viewport.left = 0;
	m_Viewport.top = 0;
	m_Viewport.right = SCREEN_WIDTH;
	m_Viewport.bottom = SCREEN_HEIGHT;

}


void CCamera::Uninit()
{
}


void CCamera::Update(float dt)
{
	if (CCollider::ClientPos(CInput::GetMousePosCli()))
	{
		Ray ray=Ray::ScreenToRay(this, CInput::GetmouseX(), CInput::GetmouseY());
		XMVECTOR Pos = XMLoadFloat3(&m_Position);
		XMVECTOR MoveDir = { ray.direction.x,0.0f,ray.direction.z,0.0f };
		MoveDir = XMVector3Normalize(MoveDir);
		Pos += MoveDir*CamMoveSpeed*dt;
		XMStoreFloat3(&m_Position, Pos);
	}
	//m_Position.y = CRenderer::Debug_move_v2[0];
	//m_Rotation.x = CRenderer::Debug_move_v2[1];
}



void CCamera::Draw()
{

	XMMATRIX	m_ViewMatrix;
	XMMATRIX	m_InvViewMatrix;
	XMMATRIX	m_ProjectionMatrix;



	// 價儏乕億乕僩愝掕
	D3D11_VIEWPORT dxViewport;
	dxViewport.Width = (float)(m_Viewport.right - m_Viewport.left);
	dxViewport.Height = (float)(m_Viewport.bottom - m_Viewport.top);
	dxViewport.MinDepth = 0.0f;
	dxViewport.MaxDepth = 1.0f;
	dxViewport.TopLeftX = (float)m_Viewport.left;
	dxViewport.TopLeftY = (float)m_Viewport.top;
	CRenderer::GetDeviceContext()->RSSetViewports(1, &dxViewport);
	dm_Viewport = dxViewport;




	// 價儏乕儅僩儕僋僗愝掕
	m_InvViewMatrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	m_InvViewMatrix *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	XMVECTOR det;
	m_ViewMatrix = XMMatrixInverse(&det, m_InvViewMatrix);

	//XMVECTOR posVec = XMLoadFloat3(&m_Position);
	//XMVECTOR atVec = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	//XMVECTOR upVec = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	//m_ViewMatrix = XMMatrixLookAtLH(posVec, atVec, upVec);
	CRenderer::SetViewMatrix(&m_ViewMatrix);
	XMStoreFloat4x4(&m_View, m_ViewMatrix);




	// 僾儘僕僃僋僔儑儞儅僩儕僋僗愝掕
	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(1.0f, dxViewport.Width / dxViewport.Height, 1.0f, 1000.0f);
	CRenderer::SetProjectionMatrix(&m_ProjectionMatrix);
	XMStoreFloat4x4(&m_Proj, m_ProjectionMatrix);

}

XMVECTOR CCamera::GetPositionXM() const
{
	return XMLoadFloat3(&m_Position);
}

XMFLOAT3 CCamera::GetPosition() const
{
	return m_Position;
}

XMMATRIX CCamera::GetViewXM() const
{
	return XMLoadFloat4x4(&m_View);
}

XMMATRIX CCamera::GetProjXM() const
{
	return XMLoadFloat4x4(&m_Proj);
}

D3D11_VIEWPORT CCamera::GetViewPort() const
{
	return dm_Viewport;
}
bool CCamera::Getvisibility(XMFLOAT3 Position)
{
	XMVECTOR worldPos, viewPos, ProjPos;
	XMFLOAT3 projPosF;
	worldPos = XMLoadFloat3(&Position);
	viewPos = XMVector3TransformCoord(worldPos, this->GetViewXM());
	ProjPos = XMVector3TransformCoord(viewPos, this->GetProjXM());
	XMStoreFloat3(&projPosF, ProjPos);
	 if (-1.0f < projPosF.x&&projPosF.x < 1.0f&&-1.0f < projPosF.y&&projPosF.y < 1.0f)
	//if (-1.3f < projPosF.x&&projPosF.x < 1.3f&&-1.3f < projPosF.y&&projPosF.y < 1.3f)
	{
		return true;
	}
	else
		return false;
}

XMMATRIX CCamera::GetMVP() const
{
	XMMATRIX mvp = XMLoadFloat4x4(&m_View);
	mvp *= XMLoadFloat4x4(&m_Proj);
	return mvp;
}










