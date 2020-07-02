#pragma once

class Camera
{
private:
	static XMFLOAT3 m_Position;
	static XMFLOAT3 m_Rotation;
	static XMFLOAT3 offset;

	static XMVECTOR m_PositionVec;
	static XMVECTOR m_Front;
	static XMVECTOR m_Right;
	static XMVECTOR m_Up;
	static XMVECTOR m_At;

	static XMMATRIX viewMatrix;
	static XMMATRIX projectionMatrix;

	static std::vector<XMFLOAT4> frustumPlane;

	static void GetFrustumPlanes();

public:
	static void Initialize();
	static void Update();
	static void Render();

	static void ImGui();

	static bool GetVisibility(XMFLOAT3 min, XMFLOAT3 max);

	static XMFLOAT3 GetPosition() { return m_Position; }
	static XMFLOAT3 GetRotation() { return m_Rotation; }

	static XMVECTOR GetPositionVec() { return m_PositionVec; }
	static XMVECTOR GetFront() { return m_Front; }
	static XMVECTOR GetRight() { return m_Right; }
	static XMVECTOR GetUp() { return m_Up; }
	static XMVECTOR GetAt() { return m_At; }

	static XMMATRIX GetViewMatrix() { return viewMatrix; }
	static XMMATRIX GetProjectionMatrix() { return projectionMatrix; }
};
