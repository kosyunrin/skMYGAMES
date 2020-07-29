#pragma once

class StaticObject :public GameObject
{
private:
	UINT ID;

	void Initialize() override;

public:
	StaticObject(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scaling, UINT ID);

	void Update() override;
	void Render(bool boundingBox) override;
};
