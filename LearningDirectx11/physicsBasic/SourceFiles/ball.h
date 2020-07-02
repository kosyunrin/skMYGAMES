#pragma once

class Ball :public GameObject
{
private:
	UINT ID;

	XMVECTOR quaternion;

	void Initialize() override;

public:
	Ball(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scaling, UINT ID);

	void Update() override;
	void Render(bool boundingBox) override;
};
