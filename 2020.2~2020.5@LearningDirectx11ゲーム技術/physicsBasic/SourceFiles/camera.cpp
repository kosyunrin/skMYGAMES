#include "engine.h"
#include "player.h"
#include "camera.h"

XMFLOAT3 Camera::m_Position;
XMFLOAT3 Camera::m_Rotation;
XMFLOAT3 Camera::offset;

XMVECTOR Camera::m_PositionVec;
XMVECTOR Camera::m_Front;
XMVECTOR Camera::m_Right;
XMVECTOR Camera::m_Up;
XMVECTOR Camera::m_At;

XMMATRIX Camera::viewMatrix;
XMMATRIX Camera::projectionMatrix;

std::vector<XMFLOAT4> Camera::frustumPlane;

void Camera::Initialize()
{
	m_Position = XMFLOAT3(0.0f, 10.0f, -20.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_PositionVec = XMVectorSet(0.0f, 10.0f, -20.0f, 0.0f);
	m_Front = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	m_Right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	m_Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	m_At = XMVectorSet(0.0f, 0.0f, 20.0f, 0.0f);

	offset = XMFLOAT3(0.5f, 1.4f, -7.5f);

    frustumPlane.resize(6);
}

void Camera::Update()
{
	Player* player = Manager::GetScene()->GetGameObject<Player>();

	m_Rotation = player->GetRotation();

	m_At = player->GetAt();
	m_Front = player->GetFront();
	m_Right = player->GetRight();
	m_Up = player->GetUp();

	m_PositionVec = m_At + (m_Right * offset.x) + (m_Up * offset.y) + (m_Front * offset.z);
	m_At = m_At + (m_Right * offset.x) + (m_Up * offset.y);

	XMStoreFloat3(&m_Position, m_PositionVec);

	ConstantBuffer::SetCamera(m_Position);

	//Frustum
    GetFrustumPlanes();
}

void Camera::Render()
{
	viewMatrix = XMMatrixLookAtLH(m_PositionVec, m_At, m_Up);
	ConstantBuffer::SetViewMatrix(&viewMatrix);

	projectionMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(60.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 1.0f, 1000.0f);
	ConstantBuffer::SetProjectionMatrix(&projectionMatrix);
}

void Camera::ImGui()
{
	ImGui::Begin("Camera");
	ImGui::DragFloat3("Offset", &offset.x, 0.1f);
	ImGui::End();
}

bool Camera::GetVisibility(XMFLOAT3 minWorld, XMFLOAT3 maxWorld)
{
    // Loop through each frustum plane
    for (int planeID = 0; planeID < frustumPlane.size(); ++planeID)
    {
        XMVECTOR planeNormal = XMVectorSet(frustumPlane[planeID].x, frustumPlane[planeID].y, frustumPlane[planeID].z, 0.0f);
        float planeConstant = frustumPlane[planeID].w;

        XMFLOAT3 axisVertex;

        if (frustumPlane[planeID].x < 0.0f)
            axisVertex.x = minWorld.x;
        else
            axisVertex.x = maxWorld.x;

        if (frustumPlane[planeID].y < 0.0f)
            axisVertex.y = minWorld.y;
        else
            axisVertex.y = maxWorld.y;

        if (frustumPlane[planeID].z < 0.0f)
            axisVertex.z = minWorld.z;
        else
            axisVertex.z = maxWorld.z;

        if (XMVectorGetX(XMVector3Dot(planeNormal, XMLoadFloat3(&axisVertex))) + planeConstant < 0.0f)
            return false;
    }
    return true;
}

void Camera::GetFrustumPlanes()
{
    XMMATRIX viewProjMatrix = viewMatrix * projectionMatrix;
   
    XMFLOAT4X4 viewProj;
    XMStoreFloat4x4(&viewProj, viewProjMatrix);

    // Left Frustum Plane
    frustumPlane[0].x = viewProj._14 + viewProj._11;
    frustumPlane[0].y = viewProj._24 + viewProj._21;
    frustumPlane[0].z = viewProj._34 + viewProj._31;
    frustumPlane[0].w = viewProj._44 + viewProj._41;

    // Right Frustum Plane
    frustumPlane[1].x = viewProj._14 - viewProj._11;
    frustumPlane[1].y = viewProj._24 - viewProj._21;
    frustumPlane[1].z = viewProj._34 - viewProj._31;
    frustumPlane[1].w = viewProj._44 - viewProj._41;

    // Top Frustum Plane
    frustumPlane[2].x = viewProj._14 - viewProj._12;
    frustumPlane[2].y = viewProj._24 - viewProj._22;
    frustumPlane[2].z = viewProj._34 - viewProj._32;
    frustumPlane[2].w = viewProj._44 - viewProj._42;

    // Bottom Frustum Plane
    frustumPlane[3].x = viewProj._14 + viewProj._12;
    frustumPlane[3].y = viewProj._24 + viewProj._22;
    frustumPlane[3].z = viewProj._34 + viewProj._32;
    frustumPlane[3].w = viewProj._44 + viewProj._42;

    // Near Frustum Plane
    frustumPlane[4].x = viewProj._13;
    frustumPlane[4].y = viewProj._23;
    frustumPlane[4].z = viewProj._33;
    frustumPlane[4].w = viewProj._43;

    // Far Frustum Plane
    frustumPlane[5].x = viewProj._14 - viewProj._13;
    frustumPlane[5].y = viewProj._24 - viewProj._23;
    frustumPlane[5].z = viewProj._34 - viewProj._33;
    frustumPlane[5].w = viewProj._44 - viewProj._43;

    // Normalize plane normals
    for (int index = 0; index < frustumPlane.size(); ++index)
    {
        float length = sqrt((frustumPlane[index].x * frustumPlane[index].x) + (frustumPlane[index].y * frustumPlane[index].y) + (frustumPlane[index].z * frustumPlane[index].z));
        frustumPlane[index].x /= length;
        frustumPlane[index].y /= length;
        frustumPlane[index].z /= length;
        frustumPlane[index].w /= length;
    }
}
