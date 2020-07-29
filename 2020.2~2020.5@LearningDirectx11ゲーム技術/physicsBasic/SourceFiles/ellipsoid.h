#pragma once

struct EllipsoidPack {
	XMVECTOR ellipsoidSpace;

	XMVECTOR w_Position;
	XMVECTOR w_Velocity;

	XMVECTOR e_Position;
	XMVECTOR e_Velocity;
	XMVECTOR e_normalizedVelocity;

	float rightVelocity;
	float upVelocity;
	float frontVelocity;

	//Tools
	XMVECTOR intersectionPoint;
	bool foundCollision;
	float nearestDistance;
	int collisionRecursionDepth;
};

class Ellipsoid
{
private:
	std::vector<GameObject*> targetObjects;

	float boundingScale;

	XMVECTOR CollisionTriangle(EllipsoidPack& eP);

	bool SphereCollidingWithTriangle(EllipsoidPack& eP, XMVECTOR& p0, XMVECTOR& p1, XMVECTOR& p2, XMVECTOR& triNormal);
	bool checkPointInTriangle(const XMVECTOR& point, const XMVECTOR& triV1, const XMVECTOR& triV2, const XMVECTOR& triV3);
	bool getLowestRoot(float a, float b, float c, float maxR, float* root);

public:
	Ellipsoid(float boundingScale);
	~Ellipsoid();

	XMVECTOR Update(XMVECTOR position, XMVECTOR right, XMVECTOR up, XMVECTOR front, EllipsoidPack& eP);

	template <typename T>
	void AddTargetObjects()
	{
		std::vector<T*> objects = Manager::GetScene()->GetGameObjects<T>();
		for (T* object : objects)
			targetObjects.push_back(object);
	}
};