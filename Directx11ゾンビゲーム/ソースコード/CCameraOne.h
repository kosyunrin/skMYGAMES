#pragma once
class CCameraOne :public CGameObject
{
private:
	RECT m_Viewport;
	D3D11_VIEWPORT dm_Viewport;
	float camYaw = 0.0f;
	float camPitch = 0.0f;



	XMFLOAT3 Upcam;
	XMFLOAT3 Forwardcam;
	XMFLOAT3 Rightcam;

	XMFLOAT3 Target;
	XMFLOAT4X4 camView;
	XMFLOAT4X4 camPro;
	SpotlLight m_spotlight;
	LIGHT Sun;



public:
	void Init();
	void Uninit();
	void Update(float dt);
	void Draw();
	void  set(XMVECTOR camTarget);
	XMVECTOR getForward();
	XMVECTOR getcamRight(); 
	float getangle(); 
	float Get_AngleX() { return camPitch; }
	XMVECTOR getTarget(); 
	XMVECTOR getCamUp(); 
	XMVECTOR Get_PosXM() { return XMLoadFloat3(&m_Position); } 
	XMMATRIX get_VIEWMatrix(); 
	XMMATRIX Get_ProMatrix() { return XMLoadFloat4x4(&camPro); } 
	D3D11_VIEWPORT Get_Viewport() { return dm_Viewport; } 
	void SetcamYaw(float deg) { camYaw = deg; }
	void SetcamPitch(float heght) { camPitch = heght; }
	void SetcamPitchadd(float height) { camPitch += height; }
	void SetSunAmbient(COLOR color)
	{
		Sun.Ambient = color;
	}
	
};

