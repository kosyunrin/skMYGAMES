#pragma once
class CShadow : public CGameObject
{
private:

	XMMATRIX	m_ViewMatrix;
	XMMATRIX	m_InvViewMatrix;
	XMMATRIX	m_ProjectionMatrix;

public:
	void Init();
	void Uninit();
	void Update(float dt);
	void Draw();

	XMMATRIX GetViewMatrix() { return m_ViewMatrix; }
	XMMATRIX GetProjectionMatrix() { return m_ProjectionMatrix; }

};

