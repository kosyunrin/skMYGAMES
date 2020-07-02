#pragma once

class Title :public Scene
{
public:
	void Initialize() override;
	void Update() override;
	void Render(bool boundingBox) override;
	void Finalize() override;
};
