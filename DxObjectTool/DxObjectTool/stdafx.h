// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <assert.h>
#include <vector>
using namespace std;
// TODO: reference additional headers your program requires here
//#if _DEBUG
//// DEBUG Mode
//#ifdef UNICODE
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
//#else
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
//#endif
//#else
//// Release Mode
//#endif

#define SafeDelete(p)  { if(p) delete p; }
#define SafeRelease(p) { if(p) p->Release(); p = NULL; }

#define SingleTone(class_name) \
private:\
	class_name(void);\
	~class_name(void);\
public:\
	static class_name* GetInstance()\
	{\
		static class_name instance;\
		return &instance;\
	}

#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")

#include "DeviceManager.h"

extern HWND g_hWnd;

struct ST_PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR c;

	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};