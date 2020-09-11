#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <assert.h>

#include <d3d11.h>

#include <DirectXMath.h>
//#include"DDSTextureLoader.h"
using namespace DirectX;

#pragma comment (lib, "d3d11.lib")
#pragma comment	(lib,"DirectXTK.lib")
#pragma comment (lib, "DXGI.lib")
#pragma comment (lib, "D3DCompiler.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "xaudio2.lib")
#include<list>
#include<vector>
//#pragma comment (lib, "DXGI.lib")
//#pragma comment (lib, "D3D10_1.lib")
//#pragma comment (lib, "D3DCompiler.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#include"assimp/Importer.hpp"
#include"assimp/postprocess.h"
#include"assimp/scene.h"
#include"assimp/cimport.h"
#include"assimp/material.h"

#include<DirectXCollision.h>
#include<SpriteBatch.h>
#include<SpriteFont.h>

//#include <vector>
//bool InitDirectInput(HINSTANCE hInstance);
//bool InitDirectInputP(HINSTANCE hInstance);
//#include"CObjManager.h"
#include"BlueTeam.h"
#include"Tools.h"
#include"VerBuffer.h"
#include"IndBuffer.h"
#include"CMangagerOfModel.h"
#include"CShader.h"


#define SCREEN_WIDTH	(1920)			// ウインドウの幅
#define SCREEN_HEIGHT	(1080)			// ウインドウの高さ

HWND GetWindow();
