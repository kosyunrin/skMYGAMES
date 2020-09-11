#include"main.h"
#include "CSolidCollider.h"



CSolidCollider::CSolidCollider()
{
}


CSolidCollider::~CSolidCollider()
{
}

std::vector<DirectX::XMMATRIX>XM_CALLCONV CSolidCollider::FrustumCulling(const std::vector<DirectX::XMMATRIX>& Matrices, const DirectX::BoundingBox & localBox, DirectX::FXMMATRIX View, DirectX::CXMMATRIX Proj)
{
	std::vector<DirectX::XMMATRIX> acceptedData;

	BoundingFrustum frustum;
	BoundingFrustum::CreateFromMatrix(frustum, Proj);
	XMMATRIX InvView = XMMatrixInverse(nullptr, View);
	// 将视锥体从局部坐标系变换到世界坐标系中
	frustum.Transform(frustum, InvView);

	BoundingOrientedBox localOrientedBox, orientedBox;
	BoundingOrientedBox::CreateFromBoundingBox(localOrientedBox, localBox);
	for (auto& mat : Matrices)
	{
		// 将有向包围盒从局部坐标系变换到世界坐标系中
		localOrientedBox.Transform(orientedBox, mat);
		// 相交检测
		if (frustum.Intersects(orientedBox))
			acceptedData.push_back(mat);
	}

	return acceptedData;
}
