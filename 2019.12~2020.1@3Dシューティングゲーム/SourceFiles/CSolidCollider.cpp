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
	// ����׶��Ӿֲ�����ϵ�任����������ϵ��
	frustum.Transform(frustum, InvView);

	BoundingOrientedBox localOrientedBox, orientedBox;
	BoundingOrientedBox::CreateFromBoundingBox(localOrientedBox, localBox);
	for (auto& mat : Matrices)
	{
		// �������Χ�дӾֲ�����ϵ�任����������ϵ��
		localOrientedBox.Transform(orientedBox, mat);
		// �ཻ���
		if (frustum.Intersects(orientedBox))
			acceptedData.push_back(mat);
	}

	return acceptedData;
}
