#pragma once


class CInput
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];
	static bool locked;

public:
	static void Init();
	static void Uninit();
	static void Update();

	static bool GetKeyPress( BYTE KeyCode );
	static bool GetKeyTrigger( BYTE KeyCode );
	static int GetMouseDate(BYTE KeyCode);
	static LONG GetmouseX();
	static LONG GetmouseY();
	static XMFLOAT2 GetMousePosCli();

};
