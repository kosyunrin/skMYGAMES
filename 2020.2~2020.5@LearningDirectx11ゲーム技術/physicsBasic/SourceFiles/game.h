#pragma once

class Game :public Scene
{
private:
	std::unique_ptr<RTT> reflection;
	std::unique_ptr<RTT> light;
	std::unique_ptr<Shadow> shadow;
	std::unique_ptr<Ray> ray;

	void ImGui();

public:
	void Initialize() override;
	void Update() override;
	void Render(bool boundingBox) override;
	void Finalize() override;
};
