#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#include <tchar.h>

#include "stdafx.h"
#include "toolMain.h"

HWND hwnd, g_hWnd;
WNDCLASSEX wc; 
CToolMain* g_pMain;
POINT windowPos = { 0, 0 };
POINT windowSize = { 1920, 1080 }; // { 1280, 800 };

void Setup_Window();
void Destroy();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Main code
int main(int, char**)
{
	Setup_Window();

	g_pMain = new CToolMain;
	g_pMain->Setup();

    // Main loop
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            continue;
        }
		else
		{
			g_pMain->Update();
			g_pMain->Render();
		} 
    }

	Destroy();
    return 0;
}

void Setup_Window()
{
#ifdef _DEBUG
	HWND hWindow = GetConsoleWindow();
	ShowWindow(hWindow, SW_SHOW);
#else
	HWND hWindow = GetConsoleWindow();
	ShowWindow(hWindow, SW_HIDE);
#endif // _DEBUG

	wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("MapTool"), NULL };
	::RegisterClassEx(&wc);

	hwnd = ::CreateWindow(wc.lpszClassName, _T("Colorful Travel MapTool"), WS_OVERLAPPEDWINDOW, windowPos.x, windowPos.y, windowSize.x, windowSize.y, NULL, NULL, wc.hInstance, NULL);
	g_hWnd = hwnd;

	::UnregisterClass(wc.lpszClassName, wc.hInstance);

	::ShowWindow(hwnd, SW_SHOWDEFAULT);
	::UpdateWindow(hwnd);
}

void Destroy()
{
	::DestroyWindow(hwnd);
	::UnregisterClass(wc.lpszClassName, wc.hInstance);

	SafeDelete(g_pMain);
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (g_pMain)
	{
		g_pMain->WndProc(hwnd, msg, wParam, lParam);

		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return true;
	}

    switch (msg)
    {
    // case WM_SIZE:
	// 	if (g_pD3DDevice != NULL && wParam != SIZE_MINIMIZED)
	// 		// g_pMain->GetImgui();
    //     return 0;

	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = windowSize.x;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = windowSize.y;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = windowSize.x;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = windowSize.y;
		break;

    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;

	case WM_CLOSE:
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
		break;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
