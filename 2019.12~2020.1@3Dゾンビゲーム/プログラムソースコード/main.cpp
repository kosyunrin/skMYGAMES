#include"main.h"
#include "manager.h"
#include"Engine.h"
Timer m_timer;
const char* CLASS_NAME = "DX11AppClass";
const char* WINDOW_NAME = "DX11";


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//keybody,

HWND g_Window;

HWND GetWindow()
{
	return g_Window;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/*if (!InitDirectInput(hInstance))
	{
		MessageBox(0, "Direct Input Initialization - Failed",
			"Error", MB_OK);
		return 0;
	}
	if (!InitDirectInputP(hInstance))
	{
		MessageBox(0, "Direct Input Initialization - Failed",
			"Error", MB_OK);
		return 0;
	}*/
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	g_Window = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2),
		(SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
		NULL,
		NULL,
		hInstance,
		NULL);


	// 初期化処理(ウィンドウを作成してから行う)
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(0, "textureload Initialization - Failed",
			"Error", MB_OK);
		return -1;
	}
	CManager::Init();
	m_timer.Reset();

	LONG windowinfo= GetWindowLong(g_Window, GWL_STYLE);
	SetWindowLong(g_Window, GWL_STYLE, (windowinfo | WS_POPUP | WS_MAXIMIZE )& ~WS_CAPTION&~WS_THICKFRAME & ~WS_BORDER);
	// ウインドウの表示(初期化処理の後に行う)
	ShowWindow(g_Window, nCmdShow);
	//ShowWindow(g_Window, SW_MAXIMIZE);
	UpdateWindow(g_Window);



	//フレームカウント初期化
	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwCurrentTime = 0;


	// メッセージループ
	MSG msg;

	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			//new 
			
			dwCurrentTime = timeGetTime();

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				m_timer.Tick();

				dwExecLastTime = dwCurrentTime;

				Engine::timerShow(m_timer);
				// 更新処理
				CManager::Update(m_timer.DeltaTime());

				// 描画処理
				CManager::Draw();
			}
		}
	}

	timeEndPeriod(1);				// 分解能を戻す

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	CManager::Uninit();

	return (int)msg.wParam;
}

//imgui
//extern LRESULT Imlwin32_windprochandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//=============================================================================
// ウインドウプロシージャ
//=============================================================================

//


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


