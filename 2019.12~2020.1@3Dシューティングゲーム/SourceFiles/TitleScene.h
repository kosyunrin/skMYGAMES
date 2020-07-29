#pragma once
#include "main.h"
#include "renderer.h"
#include"game_object.h"
#include "TitleUI.h"
#include"UICamera.h"
#include"Scene.h"
#include"manager.h"
#include"texture.h"
#include"input.h"
#include"CPolygon.h"
#include"GamePad.h"
using namespace Input;

class CCollider2D
{
public:
	static bool BoxCirece(XMFLOAT2 cPoint, XMFLOAT2 p1, XMFLOAT2 p3)
	{
		bool blResult = (cPoint.x >= p1.x && cPoint.x <= p3.x) && (cPoint.y >= p1.y && cPoint.y <= p3.y);
		return blResult;
	}
};
