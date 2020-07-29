#include "engine.h"
#include "enemy.h"
#include "ray.h"

Ray::Ray()
{
	rayPos = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	rayDir = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	closestDistance = FLT_MAX;
	closestIntersect = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);
	closestTargetID = UINT_MAX;
	closestCollisionID = UINT_MAX;
	percisive = true;

	AddTargetObjects<Enemy>();
}

Ray::~Ray()
{
}

void Ray::Update()
{
	this->RayVector();
	this->PickingBoundingBox();
}

void Ray::ImGui()
{
	ImGui::Begin("Ray");
	ImGui::Checkbox("Percisive", &percisive);
	ImGui::Text("Intersect = %.4f  %.4f  %.4f", closestIntersect.x, closestIntersect.y, closestIntersect.z);
	ImGui::Text("Distance = %.4f", closestDistance);
	ImGui::End();
}

void Ray::RayVector()
{
	POINT cursorPos;
	GetCursorPos(&cursorPos);

	cursorPos.x -= GetWindowX();
	cursorPos.y -= GetWindowY();

	XMVECTOR rayInViewSpacePos = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR rayInViewSpaceDir = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	float rayX, rayY, rayZ;

	XMMATRIX projectionMatrix = Camera::GetProjectionMatrix();

	/*
	//Transform 2D pick position on screen space to 3D ray in view space
	rayX = (((2.0f * cursorPos.x) / GetClientWidth()) - 1.0f) / XMVectorGetX(projectionMatrix.r[0]);
	rayY = -(((2.0f * cursorPos.y) / GetClientHeight()) - 1.0f) / XMVectorGetY(projectionMatrix.r[1]);
	rayZ = 1.0f;

	rayInViewSpaceDir = XMVectorSet(rayX, rayY, rayZ, 0.0f);
	*/

	//Ray at center of the screen
	rayInViewSpaceDir = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	//Transform 3D Ray from view space to world space
	XMMATRIX rayWorldMatrix;
	XMVECTOR determinant;

	rayWorldMatrix = XMMatrixInverse(&determinant, Camera::GetViewMatrix());

	rayPos = XMVector3TransformCoord(rayInViewSpacePos, rayWorldMatrix);
	rayDir = XMVector3TransformNormal(rayInViewSpaceDir, rayWorldMatrix);
}

void Ray::PickingBoundingBox()
{
	closestDistance = FLT_MAX;
	closestIntersect = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);
	
	closestTargetID = UINT_MAX;
	closestCollisionID = UINT_MAX;

	//Loop through all targets
	for (int index = 0; index < targets.size(); index++)
	{
		std::vector<Collision*> collisionObjects = targets[index]->GetMyCollisions();
		
		//Loop through all collision objects
		for (int c = 0; c < collisionObjects.size(); c++)
		{
			Collision* collision = collisionObjects[c];

			std::vector<XMFLOAT3> boundingVertices = collision->GetBoundingBox()->GetWorldVertices();

			//Loop through all bounding vertices
			for (int v = 0; v < boundingVertices.size() / 3; v++)
			{
				XMVECTOR v1 = XMLoadFloat3(&boundingVertices[((size_t)v * 3) + 0]);
				XMVECTOR v2 = XMLoadFloat3(&boundingVertices[((size_t)v * 3) + 1]);
				XMVECTOR v3 = XMLoadFloat3(&boundingVertices[((size_t)v * 3) + 2]);

				//Triangle's normal
				XMVECTOR edge1 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
				XMVECTOR edge2 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
				XMVECTOR faceNormal = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

				edge1 = v2 - v1;
				edge2 = v3 - v1;

				faceNormal = XMVector3Cross(edge1, edge2);
				faceNormal = XMVector3Normalize(faceNormal);

				//Plane equation
				float A = XMVectorGetX(faceNormal);
				float B = XMVectorGetY(faceNormal);
				float C = XMVectorGetZ(faceNormal);
				float D = (-A * XMVectorGetX(v1) - B * XMVectorGetY(v1) - C * XMVectorGetZ(v1));

				//Find where will the ray intersects with the triangle plane
				float ep1, ep2;
				float distance = 0.0f;
				XMFLOAT3 intersect;
				XMVECTOR pointInPlane = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

				ep1 = (XMVectorGetX(rayPos) * A) + (XMVectorGetY(rayPos) * B) + (XMVectorGetZ(rayPos) * C);
				ep2 = (XMVectorGetX(rayDir) * A) + (XMVectorGetY(rayDir) * B) + (XMVectorGetZ(rayDir) * C);

				//Make sure there are no divide-by-zeros problem
				if (ep2 != 0.0f)
					distance = -(ep1 + D) / (ep2);

				//Make sure never pick triangle behind the camera
				if (distance > 0.0f && distance < closestDistance)
				{
					//Get the point on the plane
					intersect.x = XMVectorGetX(rayPos) + XMVectorGetX(rayDir) * distance;
					intersect.y = XMVectorGetY(rayPos) + XMVectorGetY(rayDir) * distance;
					intersect.z = XMVectorGetZ(rayPos) + XMVectorGetZ(rayDir) * distance;

					pointInPlane = XMVectorSet(intersect.x, intersect.y, intersect.z, 0.0f);

					//Check if point is in the triangle
					if (PointvsTriangle(v1, v2, v3, pointInPlane))
					{
						if (!percisive)
						{
							//Update the closest distance
							closestDistance = distance;
							//Update the intersection point
							closestIntersect = intersect;
						}
						//Update the closest target
						closestTargetID = index;
						//Update the closest collision
						closestCollisionID = c;
					}
				}
			}
		}
	}
	
	if (!percisive)
	{
		//Reset targeted enemy to false
		for (GameObject* o : targets)
			o->SetTargeted(FALSE);

		//Set targeted enemy to true
		if (closestTargetID != UINT_MAX && closestCollisionID != UINT_MAX)
			targets[closestTargetID]->SetTargeted(TRUE);
	}
	else
	{
		//Collision with triangle
		if(closestTargetID != UINT_MAX && closestCollisionID != UINT_MAX)
			this->PickingTriangles(targets[closestTargetID]->GetMyCollisions()[closestCollisionID]);
	}
}

void Ray::PickingTriangles(Collision* collision)
{
	bool hasCollision = false;

	closestDistance = FLT_MAX;
	closestIntersect = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);

	std::vector<XMFLOAT3> collisionVertices = collision->GetVertices();
	std::vector<DWORD> collisionIndices = collision->GetIndices();

	//Loop through each triangle in the object
	for (int i = 0; i < collisionIndices.size() / 3; i++)
	{
		XMVECTOR v1 = XMLoadFloat3(&collisionVertices[collisionIndices[((size_t)i * 3) + 0]]);
		XMVECTOR v2 = XMLoadFloat3(&collisionVertices[collisionIndices[((size_t)i * 3) + 1]]);
		XMVECTOR v3 = XMLoadFloat3(&collisionVertices[collisionIndices[((size_t)i * 3) + 2]]);

		//Transform vertices to world space
		v1 = XMVector3TransformCoord(v1, collision->GetWorldMatrix());
		v2 = XMVector3TransformCoord(v2, collision->GetWorldMatrix());
		v3 = XMVector3TransformCoord(v3, collision->GetWorldMatrix());

		//Triangle normal
		XMVECTOR edge1 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR edge2 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR faceNormal = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

		edge1 = v2 - v1;
		edge2 = v3 - v1;

		faceNormal = XMVector3Cross(edge1, edge2);
		faceNormal = XMVector3Normalize(faceNormal);

		//Plane equation
		float A = XMVectorGetX(faceNormal);
		float B = XMVectorGetY(faceNormal);
		float C = XMVectorGetZ(faceNormal);
		float D = (-A * XMVectorGetX(v1) - B * XMVectorGetY(v1) - C * XMVectorGetZ(v1));

		//Find where will the ray intersects with the triangle plane
		float ep1, ep2;
		float distance = 0.0f;
		XMFLOAT3 intersect;
		XMVECTOR pointInPlane = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

		ep1 = (XMVectorGetX(rayPos) * A) + (XMVectorGetY(rayPos) * B) + (XMVectorGetZ(rayPos) * C);
		ep2 = (XMVectorGetX(rayDir) * A) + (XMVectorGetY(rayDir) * B) + (XMVectorGetZ(rayDir) * C);

		//Make sure there are no divide-by-zeros problem
		if (ep2 != 0.0f)
			distance = -(ep1 + D) / (ep2);

		if (distance > 0.0f && distance < closestDistance)
		{
			//Get the point on the plane
			intersect.x = XMVectorGetX(rayPos) + XMVectorGetX(rayDir) * distance;
			intersect.y = XMVectorGetY(rayPos) + XMVectorGetY(rayDir) * distance;
			intersect.z = XMVectorGetZ(rayPos) + XMVectorGetZ(rayDir) * distance;

			pointInPlane = XMVectorSet(intersect.x, intersect.y, intersect.z, 0.0f);

			//Check if point is in the triangle
			if (PointvsTriangle(v1, v2, v3, pointInPlane))
			{
				//Update collision check
				hasCollision = true;
				//Update the closest distance
				closestDistance = distance;
				//Update the closest distance intersect
				closestIntersect = intersect;
			}
		}
	}

	if (hasCollision)
	{
		//Reset targeted enemy to false
		for (GameObject* o : targets)
			o->SetTargeted(FALSE);

		//Set targeted enemy to true
		targets[closestTargetID]->SetTargeted(TRUE);
	}
}

bool Ray::PointvsTriangle(XMVECTOR v1, XMVECTOR v2, XMVECTOR v3, XMVECTOR point)
{
	XMVECTOR cp1 = XMVector3Cross((v3 - v2), (point - v2));
	XMVECTOR cp2 = XMVector3Cross((v3 - v2), (v1 - v2));

	if (XMVectorGetX(XMVector3Dot(cp1, cp2)) >= 0)
	{
		cp1 = XMVector3Cross((v3 - v1), (point - v1));
		cp2 = XMVector3Cross((v3 - v1), (v2 - v1));

		if (XMVectorGetX(XMVector3Dot(cp1, cp2)) >= 0)
		{
			cp1 = XMVector3Cross((v2 - v1), (point - v1));
			cp2 = XMVector3Cross((v2 - v1), (v3 - v1));

			if (XMVectorGetX(XMVector3Dot(cp1, cp2)) >= 0)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	return false;
}
