#pragma once
class Line
{
public:
	Line();
	~Line();
private:
	 ID3D11Buffer* m_VertexBuffer=NULL;
	 ID3D11Buffer* m_indexBuffer=NULL;
public:
	 void Init(float radius);
	 void InitDrawBox(XMFLOAT3* m_Vertex);
	 void DrawLine(XMFLOAT3 orgin);
	 void DrawLineByPlayerWorld(XMMATRIX world);
	 void Uninit();

	 void MapInit();
	 void MapDrawLine();
};

