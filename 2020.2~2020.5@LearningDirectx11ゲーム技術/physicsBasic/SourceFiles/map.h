#pragma once

class Map : public GameObject
{
private:
	UINT ID;

	void Initialize() override;

public:
	Map();

	void Update() override;
	void Render(bool boundingBox) override;
};