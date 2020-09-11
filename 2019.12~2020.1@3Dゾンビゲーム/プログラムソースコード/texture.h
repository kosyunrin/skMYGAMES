#pragma once

#include "main.h"
#include "renderer.h"
#include<WICTextureLoader.h>
#include<DDSTextureLoader.h>



#define TEXTURE_MAX (sizeof(g_Files)/sizeof(g_Files[0]))
#define TEXTURE_JpgPngMAX (sizeof(Go_OpenJpgPng)/sizeof(Go_OpenJpgPng[0]))
#define TEXTURE_NAME (64)


struct TextureFile
{
	const char name[TEXTURE_NAME];
	int width;
	int height;
	ID3D11ShaderResourceView* m_ShaderResourceView;
};
static TextureFile g_Files[]
{
	{"./asset/BackAttack.tga"},
	{"./asset/Onepiece/TGA/szi.tga"},
	{"./asset/Onepiece/TGA/rednumber.tga"},
	{"./asset/Texiao1.tga"},
	{"./asset/Texiao0.tga"},
	{"./asset/UItexiao1.tga"},
	{"./asset/GameTexture/anniu0.tga"},
	{"./asset/GameTexture/zombie2Danimation.tga"},
	{"./asset/GameTexture/BButton.tga"}
};
struct TextureJpgPng 
{
	const wchar_t name[TEXTURE_NAME];
	ID3D11ShaderResourceView* m_ShaderResourceView;
};
static TextureJpgPng Go_OpenJpgPng[]
{
	{L"asset/UItex/qiang.png"},
	{L"asset/UItex/Black.png"},
	{L"asset/UItex/yaocao.jpg"},
	{L"asset/UItex/gold.png"},
	{L"asset/UItex/zombie.jpg"},
	{L"asset/UItex/zhidan.jpg"},
	{L"asset/UItex/zhunxin.png"},
	{L"asset/UItex/shous.png"},
	{L"asset/UItex/yaoshuihong.png"},
	{L"asset/UItex/nengliangzhu.png"},
	{L"asset/UItex/nengliangzhu2.png"},
	{L"asset/UItex/yaoshuihong3D.png"},
	{L"asset/UItex/yaocao3D.png"},
	{L"asset/UItex/UI.png"},
	{L"asset/UItex/candank.png"},//14
	{L"asset/UItex/sqiang.png"},//15
	{L"asset/UItex/dao.png" },//16
	{L"asset/UItex/sm.png" }
};
class CTexture
{

public:
	CTexture() {}
	CTexture(const char* path);

	void LoadALLTga();
	void Load( const char *FileName );
	void LoadAny(const wchar_t *FileName);
	void LoadAnyJpgPng();
	void LoadPJtexture(int texNumber);
	void LoadTga(int number);
	void LoadDDs(const wchar_t *FileName);
	void Unload();
	void UnloadAllTga();
	void UnloadAllJpgPng();
	void UnloadPJtex(int tex);
	void UnloadTag(int number);
	ID3D11ShaderResourceView* Gettex();
	

	ID3D11ShaderResourceView* GetShaderResourceView(){ return m_ShaderResourceView; }
	ID3D11ShaderResourceView* GetShaderResourceViewIndex(int texture);
	ID3D11ShaderResourceView* GetShaderResourceViewJpgPng(int texture);
	int Texture_GetWidth(int texture);
	int Texture_GetHeight(int texture);


private:

	ID3D11Texture2D*			m_Texture;
	ID3D11ShaderResourceView*	m_ShaderResourceView;//要创建着色器资源视图

};