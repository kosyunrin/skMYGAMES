#pragma once
#define _CRT_SECURE_NO_WARNINGS

#define SCREEN_WIDTH 3072
#define SCREEN_HEIGHT 1920

#define SCREEN_CENTERX (SCREEN_WIDTH / 2)
#define SCREEN_CENTERY (SCREEN_HEIGHT / 2)

#include <stdio.h>
#include <windows.h>
#include <wrl/client.h>
#include <d3d11.h>
#include <DirectXMath.h>

#include <string>
#include <typeinfo>
#include <vector>
#include <list>
#include <map>
#include <memory>

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_win32.h"
#include "Imgui/imgui_impl_dx11.h"

using namespace Microsoft::WRL;
using namespace DirectX;

HWND GetWindow();

UINT GetWindowX();
UINT GetWindowY();

UINT GetClientWidth();
UINT GetClientHeight();
