#pragma once

class Input
{
private:
	static BYTE oldKeyState[256];
	static BYTE keyState[256];

	static POINT mousePos;

	static bool FixCursor;
	static bool clicked;

public:
	static void Initialize();
	static void Update();

	static bool KeyPress(BYTE KeyCode) { return (keyState[KeyCode] & 0x80); }
	static bool KeyTrigger(BYTE KeyCode) { return ((keyState[KeyCode] & 0x80) && !(oldKeyState[KeyCode] & 0x80)); }

	static LONG MousePosX() { return mousePos.x; }
	static LONG MousePosY() { return mousePos.y; }
	static SHORT MouseLeftDown() { return GetAsyncKeyState(VK_LBUTTON); }
	static SHORT MouseRightDown() { return GetAsyncKeyState(VK_RBUTTON); }
};
