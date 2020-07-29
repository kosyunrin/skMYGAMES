#pragma once

class CollisionSystem
{
private:
	static void ObjectCollision(GameObject* object1, GameObject* object2);
	static bool BoundingBoxCollision(Collision* c1, Collision* c2);

	template<typename A, typename B>
	static void AABBCollision()
	{
		std::vector<A*> as = Manager::GetScene()->GetGameObjects<A>();
		std::vector<B*> bs = Manager::GetScene()->GetGameObjects<B>();

		if (as.size() != 0 && bs.size() != 0)
		{
			for (int i = 0; i < as.size(); i++)
			{
				A* a = as[i];
				for (int j = 0; j < bs.size(); j++)
				{
					B* b = bs[j];
					ObjectCollision(a, b);
				}
			}
		}
	}

public:
	static void Update();
};