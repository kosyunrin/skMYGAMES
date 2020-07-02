#include "engine.h"

BYTE Input::oldKeyState[256];
BYTE Input::keyState[256];

POINT Input::mousePos;

bool Input::FixCursor;
bool Input::clicked;

void Input::Initialize()
{
	memset(oldKeyState, 0, 256);
	memset(keyState, 0, 256);

	SetCursorPos(GetWindowX() + SCREEN_CENTERX, GetWindowY() + SCREEN_CENTERY);
	GetCursorPos(&mousePos);

	FixCursor = true;
	clicked = false;
}

void Input::Update()
{
	memcpy(oldKeyState, keyState, 256);
	clicked = GetKeyboardState(keyState);

	if (FixCursor)
	{
		GetCursorPos(&mousePos);
		mousePos.x -= GetWindowX() + SCREEN_CENTERX;
		mousePos.y -= GetWindowY() + SCREEN_CENTERY;

		SetCursorPos(GetWindowX() + SCREEN_CENTERX, GetWindowY() + SCREEN_CENTERY);
//		ShowCursor(FALSE);
	}

	if (Input::KeyTrigger('H'))
		FixCursor = !FixCursor;
}
