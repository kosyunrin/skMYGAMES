#pragma once
#include"renderer.h"
#include"Line.h"
class CShader
{
public:
	/*CShader();
	~CShader();*/
private:
public:
	static void SetWorldMatrix(XMFLOAT3 Scaling, XMFLOAT3 Rotation, XMFLOAT3 position)
	{
		static ID3D11Buffer* m_WorldBuffer = CRenderer::GetBufferOfWorld();
		XMMATRIX world;
		world = XMMatrixScaling(Scaling.x, Scaling.y, Scaling.z);//宙ｴ・
		world *= XMMatrixRotationRollPitchYaw(Rotation.x, Rotation.y, Rotation.z);//ｻﾘﾜ・
		world *= XMMatrixTranslation(position.x, position.y, position.z);//ﾒﾆ・

		CRenderer::GetDeviceContext()->UpdateSubresource(m_WorldBuffer, 0, NULL, &XMMatrixTranspose(world), 0, 0);
	}
	static void SetWorldMatrix_Q(XMFLOAT3 Scaling, XMVECTOR Rotation, XMFLOAT3 position,Line* m_line)
	{
		static ID3D11Buffer* m_WorldBuffer = CRenderer::GetBufferOfWorld();
		XMMATRIX world;
		world = XMMatrixScaling(Scaling.x, Scaling.y, Scaling.z);//宙ｴ・
		world *= XMMatrixRotationQuaternion(Rotation);
		world *= XMMatrixTranslation(position.x, position.y, position.z);//ﾒﾆ・
		//Line::DrawLineByPlayerWorld(world);
		if (m_line != NULL)
			m_line->DrawLineByPlayerWorld(world);
		CRenderer::GetDeviceContext()->UpdateSubresource(m_WorldBuffer, 0, NULL, &XMMatrixTranspose(world), 0, 0);
	}

};

