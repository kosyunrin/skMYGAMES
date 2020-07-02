#pragma once

class CScene;//前方宣言只能用指针

class CManager
{
public:
	static void Init();
	static void Uninit();
	static void Update(float dt);
	static void Draw();
	static CScene* GetScene();
	template<typename T>
	static void SetScene()
	{
		if (m_Scene != nullptr)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}
		T* SCene = new T();
		m_Scene = SCene;
		SCene->Init();
	}
private:
	static CScene* m_Scene;
	//static CInput* g_input;


};