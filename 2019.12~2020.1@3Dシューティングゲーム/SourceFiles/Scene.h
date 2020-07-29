#pragma once
#include<typeinfo>
#define List_MAX	(15)
#define Enemy_max	(100)
//#include<iostream>
//#include"camera.h"
//#include"field.h"
//#include"CPolygon.h"
class CScene
{
public:	
	CScene() {}
	virtual ~CScene() {}

	virtual void Init() = 0;
	virtual void Uninit()
	{
		for (int i = 0; i < List_MAX; i++)
		{
			for (CGameObject *object : m_GmaeObject[i])
			{
				object->Uninit();
				delete object;
			}
			m_GmaeObject[i].clear();
		}
	}
	virtual void Update(float dt)
	{
	
		for (int i = 0; i < List_MAX; i++)
		{
			for (CGameObject *object : m_GmaeObject[i])//list 循环里面 不能消除；消除的时候先把true穿给2然后在开始消除
			{
				object->Update(dt);
			}
			m_GmaeObject[i].remove_if([](CGameObject* obj)
			{
				return obj->Destroy();
			});
		}
	}
	virtual void Draw()
	{
		for (int i = 0; i < List_MAX; i++)
		{
			for (CGameObject *object : m_GmaeObject[i])
			{
				object->Draw();
			}
		}
	}

	virtual void DrawShadow()
	{
		for (int i = 0; i < List_MAX; i++)
		{
			for (CGameObject* object : m_GmaeObject[i])
				object->DrawShadow();
		}
	}

	template <typename T>
	T* AddGameObject(int laye)
	{
		T* object = new T();
		object->Init();
		m_GmaeObject[laye].push_back(object);
		return object;
		

	}
	//多体
	template <typename T>
	T*GetGmeobj(int Laye, int num)
	{
		int count = num;
		for (CGameObject* obj : m_GmaeObject[Laye])
		{
			if (typeid(*obj) == typeid(T))
			{
				if (count == 1) 
				{
					return (T*)obj;
				}
				else
				{
					count -= 1;
				}
			}
			
		}
		return nullptr;
	}
	//単体
	template <typename T>
	T*GetGmeobjs(int Laye)
	{
		for (CGameObject* obj : m_GmaeObject[Laye])
		{
			if (typeid(*obj) == typeid(T))
			{
				
				
					return (T*)obj;
				
			}
		}
		return nullptr;
	}
	//敌人复数消除
	/*template <typename T>
	std::vector<T*> Getgameobjs(int Layer)
	{
	std::Vector<T*> objs;
	for (CGameObject* obj : m_GmaeObject[Laye])
	{
		if (typeid(*obj) == typeid(T))
		{
			objs.pish_back((T*)obj);
		}
	}
	return objs;
	}*/
private:
protected:
	std::list<CGameObject*> m_GmaeObject[List_MAX];
public:
	void DestoryObj(CGameObject* obj)
	{
		obj->SetDestroy();
;
	}

};




