#pragma once
class CGameObject
{
public:
	CGameObject()
	{
		m_Destroy = false;
	}
	virtual ~CGameObject(){}
	virtual void Init(){}
	virtual void Uninit(){}
	virtual void Update(float dt) { timer++; }
	virtual void Draw(){}
	virtual void DrawShadow(){}
	 
	 void SetDestroy()
	 {
		 m_Destroy = true;
	 }
	 bool Destroy()
	 {
		 //消除预定
		 //父亲里面调用了就开始消除
		 if (m_Destroy)
		 {
			 Uninit();
			 delete this;
			 return true;
		 }
		 else
		 {
			 return false;
		 }
	 }
private:
protected:
	XMFLOAT3					m_Position;
	XMFLOAT3					m_Rotation;
	XMFLOAT3					m_Scale;
	XMVECTOR					m_Front;
	XMFLOAT4X4             m_WorldMatirx;
	bool m_Destroy = false;
public:
	XMFLOAT3 GetPosition() { return m_Position; }
	XMFLOAT3 GetRotation() { return m_Rotation; }
	XMFLOAT3 GetScale() { return m_Scale; }
	int timer = 0;

	void SetPosition(XMFLOAT3 Position) { m_Position = Position; }
	void SetRotation(XMFLOAT3 Rotation) { m_Rotation = Rotation; }
	void SetScale(XMFLOAT3 Scale) { m_Scale = Scale; }
	void SetFront(XMVECTOR front) { m_Front = front; }
	void SetMyRotY(float y) { m_Rotation.y += y; }
	XMVECTOR GetVectorPos() { return XMLoadFloat3(&m_Position); }
	XMMATRIX GetMatrixForWorld(){ return XMLoadFloat4x4(&m_WorldMatirx); }
	BoundingSphere GetSphereBox()
	{
		BoundingSphere box;
		box.Center = m_Position;
		box.Radius = 7.0f;
		return box;
	}
	BoundingSphere GetSphereBox(float size)
	{
		BoundingSphere box;
		box.Center = m_Position;
		box.Radius = size;
		return box;
	}
	
	

};
