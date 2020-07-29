#pragma once
#define aabb		(100)
struct MymapPos
{
	int Row;
	int Col;
};
struct Map
{
	MymapPos pos;
	XMFLOAT3 jinD;
	XMFLOAT3 YuanD;
};
class CField:public CGameObject
{
	float x = 0;
public:
	CField();
	~CField();

private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11Buffer* m_indexBuffer = NULL;
	CTexture* m_Texture = NULL;
	VERTEX_3D m_Vertex[aabb*aabb];
	//unsigned short index[(aabb - 1)*(aabb - 1) * 6];
	XMFLOAT3 va, vb;
	std::vector<XMFLOAT3> jinD;
	std::vector<XMFLOAT3> YuanD;
	Map SMap[aabb - 1][aabb - 1];
	int map[(aabb - 1)*(aabb - 1)];

public:
	void Init();
	void Uninit();
	void UpDate(float dt);
	void Draw();
	float GetHeight(XMFLOAT3 Postion);
	//std::vector<VERTEX_3D> Get_floor_vector3D();
	//std::vector<unsigned short> Get_floor_int();
};

