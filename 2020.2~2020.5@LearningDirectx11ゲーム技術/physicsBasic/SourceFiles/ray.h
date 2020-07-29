#pragma once

class Ray
{
private:
	std::vector<GameObject*> targets;

	XMVECTOR rayPos;
	XMVECTOR rayDir;

	UINT closestTargetID;
	UINT closestCollisionID;

	XMFLOAT3 closestIntersect;
	float closestDistance;

	bool percisive;

	void RayVector();
	void PickingBoundingBox();
	void PickingTriangles(Collision* collision);

	bool PointvsTriangle(XMVECTOR v1, XMVECTOR v2, XMVECTOR v3, XMVECTOR point);

public:
	Ray();
	~Ray();

	void Update();
	void ImGui();

	UINT GetClosestTargetID() { return closestTargetID; }
	UINT GetClosestCollisionID() { return  closestCollisionID; }

	XMFLOAT3 GetClosestIntersect() { return closestIntersect; }
	float GetClosestDistance() { return closestDistance; }

	template <typename T>
	void AddTargetObjects()
	{
		std::vector<T*> objects = Manager::GetScene()->GetGameObjects<T>();
		for (T* object : objects)
			targets.push_back(object);
	}
};
