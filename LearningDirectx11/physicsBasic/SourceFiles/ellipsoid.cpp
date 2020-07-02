#include "engine.h"
#include "ellipsoid.h"

Ellipsoid::Ellipsoid(float boundingScale)
{
	this->boundingScale = boundingScale;
}

Ellipsoid::~Ellipsoid()
{
}

XMVECTOR Ellipsoid::Update(XMVECTOR position, XMVECTOR right, XMVECTOR up, XMVECTOR front, EllipsoidPack& eP)
{
	eP.w_Position = position;
	eP.w_Velocity = (eP.rightVelocity * right) + (eP.upVelocity * up) + (eP.frontVelocity * front);

	//Transform from world space to ellipsoid space
	eP.e_Velocity = eP.w_Velocity/eP.ellipsoidSpace;
	eP.e_Position = eP.w_Position/eP.ellipsoidSpace;

	//Check for a collision with our world, this function will call itself 5 times at most,
	//or until the velocity vector is used up
	eP.collisionRecursionDepth = 0;

	XMVECTOR finalPosition = CollisionTriangle(eP);

	//Transform from ellipsoid space back to world space
	finalPosition = finalPosition * eP.ellipsoidSpace;

	return finalPosition;
}

XMVECTOR Ellipsoid::CollisionTriangle(EllipsoidPack& eP)
{
	float unitsPerMeter = 100.0f;

	float unitScale = unitsPerMeter / 100.0f;
	//Use to prevent actual touching the triangle, it would cause problems
	//since each loop it would always find a collision instead of just sliding along the triangle
	float veryCloseDistance = 0.005f * unitScale;

	//This will stop us from entering an infinite loop, or a very long loop
	if (eP.collisionRecursionDepth > 5)
		return eP.e_Position;

	//Normalize velocity vector
	eP.e_normalizedVelocity = XMVector3Normalize(eP.e_Velocity);

	//Initialize collision settings
	eP.foundCollision = false;
	eP.nearestDistance = 0.0f;

	/*--------------------------------------------------------------------------------
	Check collision with all triangle
	--------------------------------------------------------------------------------*/
	//For faster collision check
	XMFLOAT3 subjectMin, subjectMax;
	XMStoreFloat3(&subjectMin, eP.w_Position);
	XMStoreFloat3(&subjectMax, eP.w_Position);

	subjectMin = XMFLOAT3(subjectMin.x - boundingScale, subjectMin.y - boundingScale, subjectMin.z - boundingScale);
	subjectMax = XMFLOAT3(subjectMax.x + boundingScale, subjectMax.y + boundingScale, subjectMax.z + boundingScale);

	for(int index = 0; index < targetObjects.size(); index++)
	{
		std::vector<Collision*> collisionObjects = targetObjects[index]->GetMyCollisions();

		//Loop through all bounding vertices
		for (int c = 0; c < collisionObjects.size(); c++)
		{
			Collision* collision = collisionObjects[c];

			//Bounding box vertices
			std::vector<XMFLOAT3> boundingVertices = collision->GetBoundingBox()->GetWorldVertices();
			XMFLOAT3 boundingMin = collision->GetBoundingBox()->GetMinWorld();
			XMFLOAT3 boundingMax = collision->GetBoundingBox()->GetMaxWorld();

			//Meshes vertices
			std::vector<XMFLOAT3> vertices = collision->GetVertices();
			std::vector<DWORD> indices = collision->GetIndices();
			XMMATRIX worldMatrix = collision->GetWorldMatrix();

			/*--------------------------------------------------------------------------------
			Check collision with bounding box
			--------------------------------------------------------------------------------*/
			if (boundingMax.x > subjectMin.x)
				if (boundingMin.x < subjectMax.x)
					if (boundingMax.y > subjectMin.y)
						if (boundingMin.y < subjectMax.y)
							if (boundingMax.z > subjectMin.z)
								if (boundingMin.z < subjectMax.z)
								{
									//Loop through all vertices
									for (int v = 0; v < indices.size() / 3; v++)
									{
										XMFLOAT3 p0 = vertices[indices[((size_t)v * 3) + 0]];
										XMFLOAT3 p1 = vertices[indices[((size_t)v * 3) + 1]];
										XMFLOAT3 p2 = vertices[indices[((size_t)v * 3) + 2]];

										p0 = Engine::VertexToWorld(p0, worldMatrix);
										p1 = Engine::VertexToWorld(p1, worldMatrix);
										p2 = Engine::VertexToWorld(p2, worldMatrix);

										XMVECTOR p0Vec = XMLoadFloat3(&p0);
										XMVECTOR p1Vec = XMLoadFloat3(&p1);
										XMVECTOR p2Vec = XMLoadFloat3(&p2);

										//Transform it into ellipsoid space
										p0Vec = p0Vec / eP.ellipsoidSpace;
										p1Vec = p1Vec / eP.ellipsoidSpace;
										p2Vec = p2Vec / eP.ellipsoidSpace;

										//Calculate the normal for this triangle
										XMVECTOR triNormal;
										triNormal = XMVector3Normalize(XMVector3Cross((p1Vec - p0Vec), (p2Vec - p0Vec)));

										//Check whether colliding with this triangle
										SphereCollidingWithTriangle(eP, p0Vec, p1Vec, p2Vec, triNormal);
									}
								}
		}
	}

	//If there was no collision, return the position + velocity
	if (eP.foundCollision == false) {
		return eP.e_Position + eP.e_Velocity;
	}

	/*--------------------------------------------------------------------------------
	Have collision with any of the triangles
	--------------------------------------------------------------------------------*/
	//Where the sphere would travel if there was no collisions. Use this vector to find
	//the new "sliding" vector based off the plane created from the sphere and collision point
	XMVECTOR destinationPoint = eP.e_Position + eP.e_Velocity;
	//Initialize newPosition
	XMVECTOR newPosition = eP.e_Position;

	//If the position is further than "veryCloseDistance" from the point of collision, we will move the sphere along the velocity path until it "almost" touches the triangle.
	//We do this so that the next recursion (if there is one) does not detect a collision with the triangle we just collided with. We don't need to find a collision
	//with the triangle we just collided with because we will be moving parallel to it now, and if we were finding the collision with it every recursion, we would 
	//finish our 5 recursions without ever moving after touching a triangle, because before the triangle has a chance to move
	//down the new velocity path it would find the collision with the triangle, and simply recompute the same velocity vector it computed the first time. This would happen because of
	//floating point innacuracy. theoretically, we would not have to worry about this because after the new velocity vector is created, it SHOULD be perfectly parallel
	//to the triangle, and we detect that in our code and basically skip triangles who are perfectly parallel with the velocity vector. But like i said, because of innacuracy.
	//The new velocity vector might be VERY SLIGHTLY pointed down towards the triangles plane, which would make us waste a recursion just to recompute the same
	//velocity vector. Basically, the whole sliding thing works without this, but it's a lot more "choppy" and "sticky", where you get stuck in random places.
	if (eP.nearestDistance >= veryCloseDistance)
	{
		//Move the new position down velocity vector to almost touch the collision point
		XMVECTOR V = eP.e_Velocity;
		V = XMVector3Normalize(V);
		V = V * (eP.nearestDistance - veryCloseDistance);
		newPosition = eP.e_Position + V;

		//Adjust polygon intersection point (so sliding plane will be unaffected by the fact that we move slightly less than collision tells us)
		V = XMVector3Normalize(V);
		eP.intersectionPoint -= veryCloseDistance * V;
	}

	//This is our sliding plane (point in the plane and plane normal)
	XMVECTOR slidePlaneOrigin = eP.intersectionPoint;
	XMVECTOR slidePlaneNormal = newPosition - eP.intersectionPoint;
	slidePlaneNormal = XMVector3Normalize(slidePlaneNormal);

	//We will use the sliding plane to compute our new "destination" point and new velocity vector. To do this, we will need to solve another quadratic
	//equation (Ax + By + Cz + D = 0), where D is what we call the plane constant, which we use to find the distance between the sliding plane and our original
	//destination point (original as up until now, since it's likely that this is not the first recursion of this function, and the original destination has been changed up until now).

	//First the point in the plane
	float x = XMVectorGetX(slidePlaneOrigin);
	float y = XMVectorGetY(slidePlaneOrigin);
	float z = XMVectorGetZ(slidePlaneOrigin);

	//Next the planes normal
	float A = XMVectorGetX(slidePlaneNormal);
	float B = XMVectorGetY(slidePlaneNormal);
	float C = XMVectorGetZ(slidePlaneNormal);
	float D = -((A * x) + (B * y) + (C * z));

	//To keep the variable names clear, we will rename D to planeConstant
	float planeConstant = D;

	//Get the distance between sliding plane and destination point
	float signedDistFromDestPointToSlidingPlane = XMVectorGetX(XMVector3Dot(destinationPoint, slidePlaneNormal)) + planeConstant;

	//Now we calculate the new destination point. To get the new destination point, we will subtract
	//the distance from the plane to the original destination point (down the planes normal) from the
	//original destination point. It's easier to picture this in your head than explain, so let me try
	//to give you a very simple picture. Pretend you are this equation, standing on the plane, where UP
	//(your head) is pointing the same direction as the plane's normal. directly below you is the "destination"
	//point of the sphere. Your job as this equation is to "pull" the destination point up (towards the planes
	//normal) until it is resting "in" the plane. If you can picture this the way i'm trying to get you to, you
	//can see that the new velocity vector (from the point of collision between sphere and plane) to the new
	//destination is "shorter" and parallel to the plane, so that now when the sphere follows this new velocity
	//vector, it will be traveling parallel (sliding) across the triangle, at the same time, it does not travel
	//as far as it would have if there was no collision. This is exactly what we want, because when you think about
	//it, we do not run up mountains as fast as we run on flat ground, and if we run straight into a wall in our
	//game, we will just stop moving, or if we run ALMOST straight into the wall, we will not go cruising sideways,
	//but instead slowly move to either side. In my lesson on braynzarsoft.net, This is explained in pictures
	XMVECTOR newDestinationPoint = destinationPoint - signedDistFromDestPointToSlidingPlane * slidePlaneNormal;

	//I believe this line was covered briefly in the above explanation
	XMVECTOR newVelocityVector = newDestinationPoint - eP.intersectionPoint;

	//After this check, we will recurse. This check makes sure that we have not
	//come to the end of our velocity vector (or very close to it, because if the velocity
	//vector is very small, there is no reason to lose performance by doing an extra recurse
	//when we won't even notice the distance "thrown away" by this check anyway) before
	//we recurse
	if (XMVectorGetX(XMVector3Length(newVelocityVector)) < veryCloseDistance) {
		return newPosition;
	}

	//We are going to recurse now since a collision was found and the velocity
	//changed directions. we need to check if the new velocity vector will
	//cause the sphere to collide with other geometry.
	eP.collisionRecursionDepth++;
	eP.e_Position = newPosition;
	eP.e_Velocity = newVelocityVector;

	return CollisionTriangle(eP);
}

bool Ellipsoid::SphereCollidingWithTriangle(EllipsoidPack& eP, XMVECTOR& p0, XMVECTOR& p1, XMVECTOR& p2, XMVECTOR& triNormal)
{
	//Check to see if triangle is facing velocity vector, return if not
	float facing = XMVectorGetX(XMVector3Dot(triNormal, eP.e_normalizedVelocity));

	if (facing <= 0)
	{
		XMVECTOR velocity = eP.e_Velocity;
		XMVECTOR position = eP.e_Position;

		//t0 is when collide with the front side of the triangle
		float t0;
		//t1 is when collide with the backside after it goes through the triangle
		float t1;

		//If sphere is in the plane, it will not intersect with the center of the triangle instead possibly intersect with one of the vertices or edges first
		bool sphereInPlane = false;

		/*--------------------------------------------------------------------------------
		Find the distance using plane equation
		--------------------------------------------------------------------------------*/
		//Point on the plane
		float x = XMVectorGetX(p0);
		float y = XMVectorGetY(p0);
		float z = XMVectorGetZ(p0);

		//Plane normal
		float A = XMVectorGetX(triNormal);
		float B = XMVectorGetY(triNormal);
		float C = XMVectorGetZ(triNormal);

		float D = -((A * x) + (B * y) + (C * z));

		//To keep the variable names clear, we will rename D to planeConstant
		float planeConstant = D;

		//Get the signed distance from the object position
		float signedDistFromPositionToTriPlane = XMVectorGetX(XMVector3Dot(position, triNormal)) + planeConstant;

		//This will be used a couple times below, so we'll just calculate and store it now
		float planeNormalDotVelocity = XMVectorGetX(XMVector3Dot(triNormal, velocity));

		/*--------------------------------------------------------------------------------
		Sphere vs Triangle Plane Collision
		--------------------------------------------------------------------------------*/
		//Check to see if the velocity vector is parallel with the plane
		if (planeNormalDotVelocity == 0.0f)
		{
			if (fabs(signedDistFromPositionToTriPlane) >= 1.0f)
			{
				//If sphere is not in plane, and velocity is parallel to plane, no collision possible
				return false;
			}
			else
			{
				//If sphere is in the plane, so we will now only test for a collision with the triangle's vertices and edges
				sphereInPlane = true;
			}
		}
		else
		{
			//t0 is when collide with the front side of the triangle
			t0 = (1.0f - signedDistFromPositionToTriPlane) / planeNormalDotVelocity;
			//t1 is when collide with the backside after it goes through the triangle
			t1 = (-1.0f - signedDistFromPositionToTriPlane) / planeNormalDotVelocity;

			//t0 has to be smaller than t1
			if (t0 > t1)
			{
				float temp = t0;
				t0 = t1;
				t1 = temp;
			}

			//Remember that when t(t0 and t1) is zero(0) it is at time zero, which means the beginning of the velocity vector. Basically, it represents the spheres origin.
			//When t is 1, then the sphere is at the end of the velocity vector. So what we want to do now is find of the collision happens outside the(0, 1) timeframe, 
			//which represents the full length of the velocity vector.If t0 is greater than 1, then we know both contacts with the plane are past the length of the velocity vector, 
			//and there was no collision, so we can return.Same goes for if t1 is less than 0, which means that both contacts with the plane happened behind the velocity vector
			if (t0 > 1.0f || t1 < 0.0f)
			{
				return false;
			}

			//Clamp it
			if (t0 < 0.0f)
				t0 = 0.0f;
			if (t1 > 1.0f)
				t1 = 1.0f;
		}

		/*--------------------------------------------------------------------------------
		Sphere vs Inside-Triangle Plane Collision
		--------------------------------------------------------------------------------*/
		//Point that collision occurs
		XMVECTOR collisionPoint;
		//Collision with current triangle
		bool collidingWithTri = false;

		float t = 1.0f;

		//If the sphere is not in the triangle plane
		if (!sphereInPlane)
		{
			//Get the point on the triangles plane where the sphere touches the plane
			XMVECTOR planeIntersectionPoint = (position + t0 * velocity - triNormal);

			//Checks if a point on a triangle's plane is inside the triangle
			if (checkPointInTriangle(planeIntersectionPoint, p0, p1, p2))
			{
				collidingWithTri = true;
				t = t0;
				collisionPoint = planeIntersectionPoint;
			}
		}

		/*--------------------------------------------------------------------------------
		Sphere vs Triangle Vertex Collision
		--------------------------------------------------------------------------------*/
		if (collidingWithTri == false)
		{
			float a, b, c;

			//We can use the squared velocities length below when checking for collisions with the edges of the triangles to, so to keep things clear, we won't set a directly
			float velocityLengthSquared = XMVectorGetX(XMVector3Length(velocity));
			velocityLengthSquared *= velocityLengthSquared;

			//We'll start by setting 'a', since all 3 point equations use this 'a'
			a = velocityLengthSquared;

			//This is a temporary variable to hold the distance down the velocity vector that the sphere will touch the vertex.
			float newT;

			//v0
			b = 2.0f * (XMVectorGetX(XMVector3Dot(velocity, position - p0)));
			c = XMVectorGetX(XMVector3Length((p0 - position)));
			c = (c * c) - 1.0f;
			if (getLowestRoot(a, b, c, t, &newT)) {
				t = newT;
				collidingWithTri = true;
				collisionPoint = p0;
			}

			//v1
			b = 2.0f * (XMVectorGetX(XMVector3Dot(velocity, position - p1)));
			c = XMVectorGetX(XMVector3Length((p1 - position)));
			c = (c * c) - 1.0f;
			if (getLowestRoot(a, b, c, t, &newT)) {
				t = newT;
				collidingWithTri = true;
				collisionPoint = p1;
			}

			//v2
			b = 2.0f * (XMVectorGetX(XMVector3Dot(velocity, position - p2)));
			c = XMVectorGetX(XMVector3Length((p2 - position)));
			c = (c * c) - 1.0f;
			if (getLowestRoot(a, b, c, t, &newT)) {
				t = newT;
				collidingWithTri = true;
				collisionPoint = p2;
			}

			/*--------------------------------------------------------------------------------
			Sphere vs Triangle Edge Collision
			--------------------------------------------------------------------------------*/
			//Even though there might have been a collision with a vertex, we will still check for a collision with an edge of the triangle in case an edge was hit before the vertex.

			//Edge (p0, p1):
			XMVECTOR edge = p1 - p0;
			XMVECTOR spherePositionToVertex = p0 - position;
			float edgeLengthSquared = XMVectorGetX(XMVector3Length(edge));
			edgeLengthSquared *= edgeLengthSquared;
			float edgeDotVelocity = XMVectorGetX(XMVector3Dot(edge, velocity));
			float edgeDotSpherePositionToVertex = XMVectorGetX(XMVector3Dot(edge, spherePositionToVertex));
			float spherePositionToVertexLengthSquared = XMVectorGetX(XMVector3Length(spherePositionToVertex));
			spherePositionToVertexLengthSquared = spherePositionToVertexLengthSquared * spherePositionToVertexLengthSquared;

			//Equation parameters
			a = edgeLengthSquared * -velocityLengthSquared + (edgeDotVelocity * edgeDotVelocity);
			b = edgeLengthSquared * (2.0f * XMVectorGetX(XMVector3Dot(velocity, spherePositionToVertex))) - (2.0f * edgeDotVelocity * edgeDotSpherePositionToVertex);
			c = edgeLengthSquared * (1.0f - spherePositionToVertexLengthSquared) + (edgeDotSpherePositionToVertex * edgeDotSpherePositionToVertex);

			//We start by finding if the swept sphere collides with the edges "infinite line"
			if (getLowestRoot(a, b, c, t, &newT)) {
				//Now we check to see if the collision happened between the two vertices that make up this edge
				float f = (edgeDotVelocity * newT - edgeDotSpherePositionToVertex) / edgeLengthSquared;
				if (f >= 0.0f && f <= 1.0f) {
					//If the collision with the edge happened, we set the results
					t = newT;
					collidingWithTri = true;
					collisionPoint = p0 + f * edge;
				}
			}

			//Edge (p1, p2):
			edge = p2 - p1;
			spherePositionToVertex = p1 - position;
			edgeLengthSquared = XMVectorGetX(XMVector3Length(edge));
			edgeLengthSquared = edgeLengthSquared * edgeLengthSquared;
			edgeDotVelocity = XMVectorGetX(XMVector3Dot(edge, eP.e_Velocity));
			edgeDotSpherePositionToVertex = XMVectorGetX(XMVector3Dot(edge, spherePositionToVertex));
			spherePositionToVertexLengthSquared = XMVectorGetX(XMVector3Length(spherePositionToVertex));
			spherePositionToVertexLengthSquared = spherePositionToVertexLengthSquared * spherePositionToVertexLengthSquared;

			a = edgeLengthSquared * -velocityLengthSquared + (edgeDotVelocity * edgeDotVelocity);
			b = edgeLengthSquared * (2.0f * XMVectorGetX(XMVector3Dot(velocity, spherePositionToVertex))) - (2.0f * edgeDotVelocity * edgeDotSpherePositionToVertex);
			c = edgeLengthSquared * (1.0f - spherePositionToVertexLengthSquared) + (edgeDotSpherePositionToVertex * edgeDotSpherePositionToVertex);

			if (getLowestRoot(a, b, c, t, &newT)) {
				float f = (edgeDotVelocity * newT - edgeDotSpherePositionToVertex) / edgeLengthSquared;
				if (f >= 0.0f && f <= 1.0f) {
					t = newT;
					collidingWithTri = true;
					collisionPoint = p1 + f * edge;
				}
			}

			//Edge (p2, p0):
			edge = p0 - p2;
			spherePositionToVertex = p2 - position;
			edgeLengthSquared = XMVectorGetX(XMVector3Length(edge));
			edgeLengthSquared = edgeLengthSquared * edgeLengthSquared;
			edgeDotVelocity = XMVectorGetX(XMVector3Dot(edge, velocity));
			edgeDotSpherePositionToVertex = XMVectorGetX(XMVector3Dot(edge, spherePositionToVertex));
			spherePositionToVertexLengthSquared = XMVectorGetX(XMVector3Length(spherePositionToVertex));
			spherePositionToVertexLengthSquared = spherePositionToVertexLengthSquared * spherePositionToVertexLengthSquared;

			a = edgeLengthSquared * -velocityLengthSquared + (edgeDotVelocity * edgeDotVelocity);
			b = edgeLengthSquared * (2.0f * XMVectorGetX(XMVector3Dot(velocity, spherePositionToVertex))) - (2.0f * edgeDotVelocity * edgeDotSpherePositionToVertex);
			c = edgeLengthSquared * (1.0f - spherePositionToVertexLengthSquared) + (edgeDotSpherePositionToVertex * edgeDotSpherePositionToVertex);

			if (getLowestRoot(a, b, c, t, &newT)) {
				float f = (edgeDotVelocity * newT - edgeDotSpherePositionToVertex) / edgeLengthSquared;
				if (f >= 0.0f && f <= 1.0f) {
					t = newT;
					collidingWithTri = true;
					collisionPoint = p2 + f * edge;
				}
			}
		}

		//If we have found a collision, we will set the results of the collision here
		if (collidingWithTri == true)
		{
			//We find the distance to the collision using the time variable (t) times the length of the velocity vector
			float distToCollision = t * XMVectorGetX(XMVector3Length(velocity));

			//Now we check if this is the first triangle that has been collided with OR it is 
			//the closest triangle yet that was collided with
			if (eP.foundCollision == false || distToCollision < eP.nearestDistance) {

				//Collision response information (used for "sliding")
				eP.nearestDistance = distToCollision;
				eP.intersectionPoint = collisionPoint;

				//Make sure this is set to true if we've made it this far
				eP.foundCollision = true;
				return true;
			}
		}
	}
	return false;
}

bool Ellipsoid::checkPointInTriangle(const XMVECTOR& point, const XMVECTOR& triV1, const XMVECTOR& triV2, const XMVECTOR& triV3)
{
	XMVECTOR cp1 = XMVector3Cross((triV3 - triV2), (point - triV2));
	XMVECTOR cp2 = XMVector3Cross((triV3 - triV2), (triV1 - triV2));
	if (XMVectorGetX(XMVector3Dot(cp1, cp2)) >= 0)
	{
		cp1 = XMVector3Cross((triV3 - triV1), (point - triV1));
		cp2 = XMVector3Cross((triV3 - triV1), (triV2 - triV1));
		if (XMVectorGetX(XMVector3Dot(cp1, cp2)) >= 0)
		{
			cp1 = XMVector3Cross((triV2 - triV1), (point - triV1));
			cp2 = XMVector3Cross((triV2 - triV1), (triV3 - triV1));
			if (XMVectorGetX(XMVector3Dot(cp1, cp2)) >= 0)
			{
				return true;
			}
		}
	}
	return false;
}

//Check if the equation can be solved
//If the equation was solved, we can set a couple things. First we set t (distance down velocity vector the sphere first collides with vertex)
//to the temporary newT, Then we set collidingWithTri to be true so we know there was for sure a collision with the triangle, then we set
//the exact point the sphere collides with the triangle, which is the position of the vertex it collides with
bool Ellipsoid::getLowestRoot(float a, float b, float c, float maxR, float* root)
{
	//Check if a solution exists
	float determinant = b * b - 4.0f * a * c;
	//If determinant is negative it means no solutions.
	if (determinant < 0.0f) return false;
	//calculate the two roots: (if determinant == 0 then
	//x1==x2 but lets disregard that slight optimization)
	float sqrtD = sqrt(determinant);
	float r1 = (-b - sqrtD) / (2 * a);
	float r2 = (-b + sqrtD) / (2 * a);
	//Sort so x1 <= x2
	if (r1 > r2) {
		float temp = r2;
		r2 = r1;
		r1 = temp;
	}
	//Get lowest root:
	if (r1 > 0 && r1 < maxR) {
		*root = r1;
		return true;
	}
	//It is possible that we want x2 - this can happen
	//if x1 < 0
	if (r2 > 0 && r2 < maxR) {
		*root = r2;
		return true;
	}

	//No (valid) solutions
	return false;
}