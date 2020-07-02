#pragma once

class Manager
{
private:
	static std::unique_ptr<Scene> scene;

public:
	static void Initialize();
	static void Finalize();
	static void Update();
	static void Render();

	template<typename T>
	static void setScene()
	{
		if (scene)
		{
			scene->Finalize();
			scene.reset();
		}
		std::unique_ptr<T> nextScene = std::make_unique<T>();
		scene = std::move(nextScene);
		scene->Initialize();
	}

	static Scene* GetScene() { return scene.get(); }
};
