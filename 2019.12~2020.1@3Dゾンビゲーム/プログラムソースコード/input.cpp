
#include "main.h"
#include "input.h"


BYTE CInput::m_OldKeyState[256];
BYTE CInput::m_KeyState[256];
POINT Mouse;
bool CInput::locked;

void CInput::Init()
{

	memset( m_OldKeyState, 0, 256 );
	memset( m_KeyState, 0, 256 );
	locked = true;
}

void CInput::Uninit()
{


}

void CInput::Update()
{
	//SetCursor(FALSE);
	if (CInput::GetKeyTrigger('T'))
		locked = !locked;


	memcpy( m_OldKeyState, m_KeyState, 256 );

	GetKeyboardState( m_KeyState );
	if (locked)
	{
		GetCursorPos(&Mouse);
		//ScreenToClient(GetWindow(), &Mouse);
		Mouse.x -= SCREEN_WIDTH / 2;
		Mouse.y -= SCREEN_HEIGHT / 2;
		SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);


	}
	SetCursor(false);
	//CRenderer::Debug_move_v2[0] = Mouse.x;
	//CRenderer::Debug_move_v2[1] = Mouse.y;
}

bool CInput::GetKeyPress(BYTE KeyCode)
{
	return (m_KeyState[KeyCode] & 0x80);
}

bool CInput::GetKeyTrigger(BYTE KeyCode)
{
	return ((m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80));
}

int CInput::GetMouseDate(BYTE KeyCode)
{
	return ((m_KeyState[KeyCode] & 0x0800) && !(m_OldKeyState[KeyCode] & 0x0800));
}

LONG CInput::GetmouseX()
{
	return Mouse.x;
}

LONG CInput::GetmouseY()
{
	return Mouse.y;
}

XMFLOAT2 CInput::GetMousePosCli()
{
	XMFLOAT2 mousePos = XMFLOAT2(Mouse.x, Mouse.y);
	return mousePos;
}
