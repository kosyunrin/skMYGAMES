#pragma once
class skyBox:public CGameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11Buffer* m_indexBuffer = NULL;
	CTexture* m_Texturefront = NULL;
	CTexture* m_Textureback = NULL;
	CTexture* m_Textureleft = NULL;
	CTexture* m_Textureright = NULL;
	CTexture* m_Texturetop = NULL;
	CTexture* m_Texturebottom = NULL;


public:
	void Init();
	void Uninit();
	void UpDate();
	void Draw();
};

