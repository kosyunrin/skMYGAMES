#pragma once
class CPolygon
{
public:
	CPolygon();
	~CPolygon();

private: 
	ID3D11Buffer* m_VertexBuffer = NULL;
	CTexture* m_Texture;
	float w;
	float h;
	float Count;
	XMFLOAT4X4 World;


public:
	void Init();
	void Init2D(int nubmber);
	void Init2D_tga(int nubmber);
	void Ini3DTex(const wchar_t * FileName);
	void Init3D(int texturenumber);
	void Uninit();
	void Uninit3D(int tex);
	void UnintTag(int number);
	void UpDate();
	void Draw(float Posx, float Posy, float ScaleW, float ScaleH, float tx, float ty, float tw, float th, int texNum);
	void DrawJpgPng(float Posx, float Posy, float ScaleW, float ScaleH, float R, float G, float B,float Alpha,int texNum);
	void Draw_animation2D(float Posx, float Posy, float ScaleW, float ScaleH,int texNum, int anim_lie_count, int anim_hang_count,float anim_speed);
	void DrawString2D(float Posx, float Posy, float ScaleW, float ScaleH, int texNum, int anim_lie_count, int anim_hang_count, int number);
	void DrawPlayerLife(float Posx,float Posy, float Posz, float ScaleW, float ScaleH, float R, float G, float B, float Alpha, int texNum,XMMATRIX world);
	void Draw3DTex(XMMATRIX world);
	void PNGDraw2D(float Posx, float Posy, float ScaleW, float ScaleH, int texNum,float color);
public:
	void SetWorld(XMMATRIX world) { XMStoreFloat4x4(&World, world); }
	XMMATRIX Getlifeworld() { return XMLoadFloat4x4(&World); }

	//void Draw(float Posx,float Posy,float ScaleW,float ScaleH);
};



