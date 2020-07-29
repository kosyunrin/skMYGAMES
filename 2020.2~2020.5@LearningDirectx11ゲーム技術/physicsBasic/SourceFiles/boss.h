#pragma once
#include "gameObject.h"

class Boss : public GameObject
{
private:
	std::unique_ptr<MultiSkinnedModel> model;

	UINT event;

	void Initialize() override;

public:
	Boss();

	void Update() override;
	void Render(bool boundingBox) override;
};