#pragma once
//class CCamera;
//struct Ray
//{
//	Ray();
//	Ray(const XMFLOAT3& origin, const XMFLOAT3& direction);
//
//	static Ray ScreenToRay(const CCamera* camera, float screenX, float screenY);
//
//	bool Hit(const BoundingBox& box, float* pOutDist = nullptr, float maxDist = FLT_MAX);
//	bool Hit(const BoundingOrientedBox& box, float* pOutDist = nullptr, float maxDist = FLT_MAX);
//	bool Hit(const BoundingSphere& sphere, float* pOutDist = nullptr, float maxDist = FLT_MAX);
//	bool XM_CALLCONV Hit(FXMVECTOR V0, FXMVECTOR V1, FXMVECTOR V2, float* pOutDist = nullptr, float maxDist = FLT_MAX);
//
//	XMFLOAT3 origin;		// ����ԭ��E
//	XMFLOAT3 direction;	// ��λ��������
//};
 class Ray_collision
{
public:
	Ray_collision();
	~Ray_collision();
public:
	static bool IntersectTriangle(const XMVECTOR& orig, const XMVECTOR& dir,
		XMVECTOR& v0, XMVECTOR& v1, XMVECTOR& v2);

};

