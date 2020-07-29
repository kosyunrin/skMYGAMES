#pragma once
#include"main.h"
#include"renderer.h"
#include"game_object.h"
#include"Ray_collision.h"
//Ray::Ray()
//	: origin(), direction(0.0f, 0.0f, 1.0f)
//{
//}
//
//Ray::Ray(const XMFLOAT3 & origin, const XMFLOAT3 & direction)
//	: origin(origin)
//{
//	// ÉäÏßµÄdirection³¤¶È±ØÐEª1.0f£¬Îó²ûðÚ1e-5fÄÚ
//	XMVECTOR dirLength = XMVector3Length(XMLoadFloat3(&direction));
//	XMVECTOR error = XMVectorAbs(dirLength - XMVectorSplatOne());
//	assert(XMVector3Less(error, XMVectorReplicate(1e-5f)));
//
//	XMStoreFloat3(&this->direction, XMVector3Normalize(XMLoadFloat3(&direction)));
//}
//
//Ray Ray::ScreenToRay(const CCamera* camera, float screenX, float screenY)
//{
//	// ******************
//	// ½ÚÑ¡×ÔDirectX::XMVector3Unprojectº¯Êý£¬²¢Ê¡ÂÔÁË´ÓÊÀ½ç×ø±Eµµ½¾Ö²¿×ø±EµµÄ±ä»»
//	//
//
//	// ½«ÆÁÄ»×ø±Eã´ÓÊÓ¿Ú±ä»»»ØNDC×ø±Eµ
//	static const XMVECTORF32 D = { { { -1.0f, 1.0f, 0.0f, 0.0f } } };
//	XMVECTOR V = XMVectorSet(screenX, screenY, 0.0f, 1.0f);
//	D3D11_VIEWPORT viewPort = camera->GetViewPort();
//
//	XMVECTOR Scale = XMVectorSet(viewPort.Width * 0.5f, -viewPort.Height * 0.5f, viewPort.MaxDepth - viewPort.MinDepth, 1.0f);
//	Scale = XMVectorReciprocal(Scale);
//
//	XMVECTOR Offset = XMVectorSet(-viewPort.TopLeftX, -viewPort.TopLeftY, -viewPort.MinDepth, 0.0f);
//	Offset = XMVectorMultiplyAdd(Scale, Offset, D.v);
//
//	// ´ÓNDC×ø±Eµ±ä»»»ØÊÀ½ç×ø±Eµ
//	XMMATRIX Transform = XMMatrixMultiply(camera->GetViewXM(), camera->GetProjXM());
//	Transform = XMMatrixInverse(nullptr, Transform);
//
//	XMVECTOR Target = XMVectorMultiplyAdd(V, Scale, Offset);
//	Target = XMVector3TransformCoord(Target, Transform);
//
//	// Çó³öÉäÏß
//	XMFLOAT3 direction;
//	XMStoreFloat3(&direction, XMVector3Normalize(Target - camera->GetPositionXM()));
//	return Ray(camera->GetPosition(), direction);
//}
//
//bool Ray::Hit(const BoundingBox & box, float * pOutDist, float maxDist)
//{
//
//	float dist;
//	bool res = box.Intersects(XMLoadFloat3(&origin), XMLoadFloat3(&direction), dist);
//	if (pOutDist)
//		*pOutDist = dist;
//	return dist > maxDist ? false : res;
//}
//
//bool Ray::Hit(const BoundingOrientedBox & box, float * pOutDist, float maxDist)
//{
//	float dist;
//	bool res = box.Intersects(XMLoadFloat3(&origin), XMLoadFloat3(&direction), dist);
//	if (pOutDist)
//		*pOutDist = dist;
//	return dist > maxDist ? false : res;
//}
//
//bool Ray::Hit(const BoundingSphere & sphere, float * pOutDist, float maxDist)
//{
//	float dist;
//	bool res = sphere.Intersects(XMLoadFloat3(&origin), XMLoadFloat3(&direction), dist);
//	if (pOutDist)
//		*pOutDist = dist;
//	return dist > maxDist ? false : res;
//}
//
//bool XM_CALLCONV Ray::Hit(FXMVECTOR V0, FXMVECTOR V1, FXMVECTOR V2, float * pOutDist, float maxDist)
//{
//	float dist;
//	bool res = TriangleTests::Intersects(XMLoadFloat3(&origin), XMLoadFloat3(&direction), V0, V1, V2, dist);
//	if (pOutDist)
//		*pOutDist = dist;
//	return dist > maxDist ? false : res;
//}

Ray_collision::Ray_collision()
{
	//ver_temp.clear();
}


Ray_collision::~Ray_collision()
{
	/*ver_temp.clear();
	int_temp.clear();*/
}

bool Ray_collision::IntersectTriangle(const XMVECTOR & orig, const XMVECTOR & dir, XMVECTOR & v0, XMVECTOR & v1, XMVECTOR & v2/*, float * t, float * u, float * v*/)
{
	float tt = 0.0f;  float uu = 0.0f; float vv = 0.0f;
	// E1
	XMVECTOR E1 = v1 - v0;

	// E2
	XMVECTOR E2 = v2 - v0;

	// P
	//XMVECTOR P = dir.Cross(E2);
	XMVECTOR P = XMVector3Cross(dir,E2);

	// determinant
	//float det = E1.Dot(P);
	XMVECTOR Pm= XMVector3Dot(E1, P);
	XMFLOAT3 ss;
	XMStoreFloat3(&ss, Pm);
	float det =ss.x;

	// keep det > 0, modify T accordingly
	XMVECTOR T;
	if (det > 0)
	{
		T = orig - v0;
	}
	else
	{
		T = v0 - orig;
		det = -det;
	}

	// If determinant is near zero, ray lies in plane of triangle
	if (det < 0.0001f)
		return false;

	// Calculate u and make sure u <= 1
	XMVECTOR Pmm = XMVector3Dot(T, P);
	XMFLOAT3 sss;
	XMStoreFloat3(&sss, Pmm);
	uu = sss.x;
	//*u = T.Dot(P);
	if (uu < 0.0f || uu > det)
		return false;

	// Q
	//XMVECTOR Q = T.Cross(E1);

	XMVECTOR Q = XMVector3Cross(T,E1);

	// Calculate v and make sure u + v <= 1
	XMVECTOR Pmmm = XMVector3Dot(dir, Q);
	XMFLOAT3 ssss;
	XMStoreFloat3(&ssss, Pmmm);
	vv = ssss.x;
	//*v = dir.Dot(Q);
	if (vv < 0.0f || uu + vv > det)
		return false;

	// Calculate t, scale parameters, ray intersects triangle

	XMVECTOR Pmmmm = XMVector3Dot(E2, Q);
	XMFLOAT3 sssss;
	XMStoreFloat3(&sssss, Pmmmm);
	tt = sssss.x;
	//*t = E2.Dot(Q);

	float fInvDet = 1.0f / det;
	tt *= fInvDet;
	uu *= fInvDet;
	vv *= fInvDet;
	XMVECTOR jiaodianv = orig + dir * tt;
	////XMStoreFloat3(&jiaodian, jiaodianv);
	//if (jiaodian.y >= 0.0f)
	//	jiaodian.y = 0.0f;
	return true;
}

//void Ray_collision::Set_vec( std::vector<VERTEX_3D> v,  std::vector<unsigned short> s)
//{
//	BVertex_vec = v;
//	BInt_vec = s;
//}
