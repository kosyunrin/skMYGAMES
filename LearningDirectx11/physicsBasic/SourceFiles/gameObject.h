#pragma once
class Collision;

class GameObject
{
protected:
	XMFLOAT3 m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	XMVECTOR m_PositionVec = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR m_Right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR m_Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR m_Front = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR m_At = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	XMMATRIX worldMatrix = XMMatrixIdentity();

	UINT health;

	bool destroyed = false;
	bool targeted = false;

	virtual void Initialize();
	virtual void Finalize();

public:
	virtual void Update();
	virtual void Render(bool boundingBox);

	void SetPosition(XMFLOAT3 position) { m_Position = position; }
	void SetRotation(XMFLOAT3 rotation) { m_Rotation = rotation; }
	void SetScale(XMFLOAT3 scale) { m_Scale = scale; }
	void SetPositionVec(XMVECTOR posVec) { m_PositionVec = posVec; }
	void SetFront(XMVECTOR front) { m_Front = front; }
	void SetRight(XMVECTOR right) { m_Right = right; }
	void SetUp(XMVECTOR up) { m_Up = up; }
	void SetAt(XMVECTOR at) { m_At = at; }

	XMFLOAT3 GetPosition() { return m_Position; }
	XMFLOAT3 GetRotation() { return m_Rotation; }
	XMFLOAT3 GetScale() { return m_Scale; }
	XMVECTOR GetPositionVec() { return m_PositionVec; }
	XMVECTOR GetFront() { return m_Front; }
	XMVECTOR GetRight() { return m_Right; }
	XMVECTOR GetUp() { return m_Up; }
	XMVECTOR GetAt() { return m_At; }

	void ReduceHealth(UINT amount) { health -= amount; }
	void AddHealth(UINT amount) { health += amount; }
	UINT GetHealth() { return health; }

	void SetDestroyed(bool b) { destroyed = b; }
	bool GetDestroyed();

	void SetTargeted(bool b) { targeted = b; }
	bool GetTargeted() { return targeted; }

/*--------------------------------------------------------------------------------
Collision
--------------------------------------------------------------------------------*/
protected:
	std::vector<Collision*> myCollisions;
public:
	std::vector<Collision*> GetMyCollisions() { return myCollisions; }
};