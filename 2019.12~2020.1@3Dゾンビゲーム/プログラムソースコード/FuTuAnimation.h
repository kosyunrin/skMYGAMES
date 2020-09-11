#pragma once
typedef struct MESHs
{
	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_IndexBuffer;
	unsigned int IndexNum;
};
class FuTuAnimation
{
public:
	FuTuAnimation();
	~FuTuAnimation();
private:
	MESHs* m_Mesh;
	unsigned int m_MeshNum;
	const aiScene* m_Scene;
	
public:
	void Draw();
	void Load(const char* FileName);
	void Unload();

public:
	void Draw(XMMATRIX Matrix);
	void DrawMesh(aiNode* Node, XMMATRIX Matrix);
};

