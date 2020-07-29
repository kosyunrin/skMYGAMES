#pragma once

enum LayerID
{
	LayerSkybox,
	LayerScene,
	LayerPlayer,
	LayerEnemy,
	LayerMax
};

class Scene
{
protected:
	std::list<GameObject*> layerObjects[LayerID::LayerMax];

public:
	virtual void Initialize() = 0;

	virtual void Update()
	{
		for (int index = 0; index < LayerID::LayerMax; index++)
		{
			for (GameObject* object : layerObjects[index])
				object->Update();
			layerObjects[index].remove_if([](GameObject* object) {return object->GetDestroyed(); });
		}
	}

	virtual void Update(UINT layer)
	{
		for (GameObject* object : layerObjects[layer])
			object->Update();
	}

	virtual void Render(bool boundingBox)
	{
		for (int index = 0; index < LayerID::LayerMax; index++)
			for (GameObject* object : layerObjects[index])
				object->Render(boundingBox);
	}

	virtual void Render(bool boundingBox, UINT layer)
	{
		for (GameObject* object : layerObjects[layer])
			object->Render(boundingBox);
	}

	virtual void Finalize()
	{
		for (int index = 0; index < LayerID::LayerMax; index++)
		{
			for (GameObject* object : layerObjects[index])
				delete object;
			layerObjects[index].clear();
		}
	}

	/*--------------------------------------------------------------------------------
	Add GameObject
	--------------------------------------------------------------------------------*/
	template <typename T>
	T* AddGameObject(UINT layer)
	{
		T* object = new T();
		layerObjects[layer].push_back(object);
		return object;
	}

	template <typename T>
	T* AddGameObject(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scaling, UINT layer)
	{
		T* object = new T(position, rotation, scaling);
		layerObjects[layer].push_back(object);
		return object;
	}

	template <typename T>
	T* AddGameObject(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scaling, UINT index, UINT layer)
	{
		T* object = new T(position, rotation, scaling, index);
		layerObjects[layer].push_back(object);
		return object;
	}

	template <typename T>
	T* AddGameObject(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scaling, XMVECTOR front, UINT layer)
	{
		T* object = new T(position, rotation, scaling, front);
		layerObjects[layer].push_back(object);
		return object;
	}

	/*--------------------------------------------------------------------------------
	Get GameObject
	--------------------------------------------------------------------------------*/
	template <typename T>
	T* GetGameObject()
	{
		for (int layer = 0; layer < LayerID::LayerMax; layer++)
			for (GameObject* object : layerObjects[layer])
				if (typeid(*object) == typeid(T))
					return (T*)object;
		return nullptr;
	}

	template <typename T>
	std::vector<T*> GetGameObjects()
	{
		std::vector<T*> objects;
		for (int layer = 0; layer < LayerID::LayerMax; layer++)
			for (GameObject* object : layerObjects[layer])
				if (typeid(*object) == typeid(T))
					objects.push_back((T*)object);
		return objects;
	}

	std::vector<GameObject*> GetLayerGameObjects(UINT layer)
	{
		std::vector<GameObject*> objects;
		for (GameObject* object : layerObjects[layer])
			objects.push_back(object);
		return objects;
	}

	/*--------------------------------------------------------------------------------
	Destroy GameObject
	--------------------------------------------------------------------------------*/
	void DestroyGameObject(GameObject* object)
	{
		delete object;
	}
};
