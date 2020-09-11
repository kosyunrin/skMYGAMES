#pragma once
class CSolidCollider
{
public:
	CSolidCollider();
	~CSolidCollider();
public:
	static std::vector<DirectX::XMMATRIX> XM_CALLCONV FrustumCulling(
		const std::vector<DirectX::XMMATRIX>& Matrices, const DirectX::BoundingBox& localBox, DirectX::FXMMATRIX View, DirectX::CXMMATRIX Proj);
};

