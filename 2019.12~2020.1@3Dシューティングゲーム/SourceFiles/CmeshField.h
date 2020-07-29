#pragma once
class CmeshField:public CGameObject
{
public:
	CmeshField();
	~CmeshField();

private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11Buffer* m_indexBuffer = NULL;
	CTexture* m_Texture = NULL;
	unsigned int vertexMax;
	unsigned int indexMax;
	VERTEX_3D*	vertex;
	WORD* index;
public:
	void Init();
	void Uninit();
	void UpDate(float dt);
	void Draw();
	void setinit(int m, int n, float r, float x, float y,float z);
};

