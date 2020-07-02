#include "engine.h"
#include "player.h"
#include "staticObject.h"
#include "collisionSystem.h"

void CollisionSystem::Update()
{
//	AABBCollision<Player, StaticObject>();
}

void CollisionSystem::ObjectCollision(GameObject* object1, GameObject* object2)
{
	for (int i = 0; i < object1->GetMyCollisions().size(); i++)
	{
		Collision* a = object1->GetMyCollisions()[i];
		for (int j = 0; j < object2->GetMyCollisions().size(); j++)
		{
			Collision* b = object2->GetMyCollisions()[j];
			if (BoundingBoxCollision(a, b))
			{
//				object1->SetDestroyed(TRUE);
				object2->SetDestroyed(TRUE);
			}
		}
	}
}

bool CollisionSystem::BoundingBoxCollision(Collision* object1, Collision* object2)
{
	XMFLOAT3 min1 = object1->GetBoundingBox()->GetMinWorld();
	XMFLOAT3 max1 = object1->GetBoundingBox()->GetMaxWorld();
	XMFLOAT3 min2 = object2->GetBoundingBox()->GetMinWorld();
	XMFLOAT3 max2 = object2->GetBoundingBox()->GetMaxWorld();

	if (max1.x > min2.x)
		if (min1.x < max2.x)
			if (max1.y > min2.y)
				if (min1.y < max2.y)
					if (max1.z > min2.z)
						if (min1.z < max2.z)
							return true;
	return false;
}