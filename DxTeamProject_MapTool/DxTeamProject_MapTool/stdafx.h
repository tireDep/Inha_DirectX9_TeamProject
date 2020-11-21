#pragma once

#define SafeRelease(p) { if(p) p->Release(); p = NULL; }
#define SafeDelete(p) { if(p) delete p; }
#define SingleTone(class_name)\
private:\
	class_name(void);\
	~class_name(void);\
public:\
	static class_name* GetInstance()\
	{\
		static class_name instance;\
		return &instance;\
	}

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")

#include <iostream>
#include <vector>
#include <string>

#include "DeviceManager.h"

extern HWND g_hWnd;

using namespace std;