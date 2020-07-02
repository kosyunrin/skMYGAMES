#include "engine.h"
#include "manager.h"
#include "main.h"

/*--------------------------------------------------------------------------------
Define Constant
--------------------------------------------------------------------------------*/
const wchar_t* CLASS_NAME = L"Paverick";
const wchar_t* WINDOW_NAME = L"Paverick";

/*--------------------------------------------------------------------------------
Define Variable
--------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND window;

UINT clientWidth;
UINT clientHeight;

/*--------------------------------------------------------------------------------
Center Window
--------------------------------------------------------------------------------*/
RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

//Get desktop size
UINT desktopWidth = GetSystemMetrics(SM_CXSCREEN);
UINT desktopHeight = GetSystemMetrics(SM_CYSCREEN);

//Calculate screen size
UINT windowWidth = wr.right - wr.left;
UINT windowHeight = wr.bottom - wr.top;

//Set window in center of desktop size
UINT windowX = (desktopWidth - windowWidth) / 2;
UINT windowY = (desktopHeight - windowHeight) / 2;

/*--------------------------------------------------------------------------------
Main
--------------------------------------------------------------------------------*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//For DirectXTK Engine
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		Engine::ErrorMsg("DirectXTK CoInitialize Failed");
		return false;
	}

	//Window Class Registration
	WNDCLASS wc = {}; //Window Class Initialize
	wc.lpfnWndProc = WndProc; //Window Procedure
	wc.lpszClassName = CLASS_NAME; //Window Class Name
	wc.hInstance = hInstance; //Instance Handle
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //Mouse Cursor
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW); //Background Color

	RegisterClass(&wc); //System Registration

	//Create Windows
	window = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		windowX,
		windowY,
		windowWidth,
		windowHeight,
		NULL,
		NULL,
		hInstance,
		NULL);

	//Initialize
	Manager::Initialize();

	//Show Windows
	ShowWindow(window, nCmdShow);
	UpdateWindow(window);

	//Frame Counter
	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwCurrentTime = 0;

	//Game Loop
	MSG msg;
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//Translate & Dispatch Message
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				Manager::Update();
				Manager::Render();
			}
		}
	}
	timeEndPeriod(1);	

	//Windows Class Unregister
	UnregisterClass(CLASS_NAME, wc.hInstance);

	//Finalize
	Manager::Finalize();

	return (int)msg.wParam;
}

//ImGui
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//Windows Procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//ImGui
	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

	switch (uMsg)
	{
	case WM_KEYDOWN: //Escape
		if (wParam == VK_ESCAPE)
		{
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;

	case WM_SIZE:
		clientWidth = LOWORD(lParam);
		clientHeight = HIWORD(lParam);
		return 0;

	case WM_CLOSE: //Window Close
		DestroyWindow(hWnd);

		return 0;

	case WM_DESTROY: //Window Destroy
		PostQuitMessage(0);
		return 0;
	};
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

HWND GetWindow() {return window;}

UINT GetWindowX() {return windowX;}
UINT GetWindowY() {return windowY;}

UINT GetClientWidth() {return clientWidth;}
UINT GetClientHeight() {return clientHeight;}