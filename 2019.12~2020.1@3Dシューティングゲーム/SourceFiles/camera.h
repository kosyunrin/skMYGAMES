#pragma once


class CCamera:public CGameObject
{
private:

	XMFLOAT3					m_Position;
	XMFLOAT3					m_Rotation;

	RECT m_Viewport;
	
public:
	void Init();
	void Uninit();
	void Update(float dt);
	void Draw();
private:
	/*XMFLOAT3 m_Right;
	XMFLOAT3 m_Up;
	XMFLOAT3 m_Look;*/
	D3D11_VIEWPORT dm_Viewport;
	XMFLOAT4X4 m_View;
	XMFLOAT4X4 m_Proj;
public:
	// ªÒ»°…„œÒª˙Œª÷√
	XMVECTOR GetPositionXM() const;
	XMFLOAT3 GetPosition() const;
//// ªÒ»°…„œÒª˙µƒ◊¯±ÅE·œÚ¡ø
//	XMVECTOR GetRightXM() const;
//	XMFLOAT3 GetRight() const;
//	XMVECTOR GetUpXM() const;
//	XMFLOAT3 GetUp() const;
//	XMVECTOR GetLookXM() const;
//	XMFLOAT3 GetLook() const;
	XMMATRIX GetViewXM() const;
	XMMATRIX GetProjXM() const;
	D3D11_VIEWPORT GetViewPort() const;
	bool Getvisibility(XMFLOAT3 Position);
	XMMATRIX GetMVP() const;
	//XMMATRIX GetViewProjXM() const;



};