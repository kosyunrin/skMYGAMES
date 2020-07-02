#pragma once

class Result :public Scene
{
public:
	void Initialize() override;
	void Update() override;
	void Render(bool boundingBox) override;
	void Finalize() override;
};
