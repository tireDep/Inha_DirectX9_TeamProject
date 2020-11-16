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
#include <assert.h>	// warning

#include <MMSystem.h> //FPS


// TODO: reference additional headers your program requires here
#include <set>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip> // setprecision
#include <sstream> // stringstream
using namespace std;

#if _DEBUG
// DEBUG Mode
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#else
// Release Mode
#endif

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

// ---------------------------------------------------
#define Synthesize(varType, varName, funName) \
protected : varType varName ; \
public : inline varType Get##funName(void) const { return varName ; } \
public : inline void Set##funName(const varType var) { varName = var ; }

#define Synthesize_Pass_by_Ref(varType, varName, funName) \
protected : varType varName ; \
public : varType& Get##funName(void) { return varName ; } \
public : void Set##funName(const varType& var) { varName = var ;}

#define SafeAddRef(p)	{if(p) p->AddRef() ; }

#define Synthesize_Add_Ref(varType , varName , funName) \
protected : varType varName ; \
public : virtual varType Get##funName(void) const { return varName ; } \
public : virtual void Set##funName(varType var ) { \
	if( varName != var ) \
	{ \
		SafeAddRef(var) ; \
		SafeRelease(varName) ; \
		varName = var ; \
	} \
}

//SafeAddRef(var); \
//SafeRelease(varName); \
//varName = var; \
//----------------------------------------------------
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")	// FPS


#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "fmodex_vc.lib")


#include "DeviceManager.h"
#include "FontManager.h"
#include "TimeManager.h"
#include "EventManager.h"
#include "GameManager.h"

extern HWND g_hWnd;
//
#include "Object.h"
#include "ObjectManager.h"

struct ST_PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR c;
	bool isPicked;
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3	p;
	D3DXVECTOR3	n;
	D3DXVECTOR2	t;

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};

enum class EventType : int
{
	eInputEvent, eSceneChangeEvent
};

enum class SceneType : int
{
	eMainScene, eGameScene, eUIScene, eResultScene
	// ePauseScene
};

enum class PlayerInputType : int
{
	eUp, eDown, eLeft, eRight, eLeftUp, eLeftDown, eRightUp, eRightDown, eHold
};

struct ST_EVENT
{
	EventType eventType;

	// >> Input
	UINT message;
	WPARAM wParam; 
	LPARAM lParam;
	PlayerInputType playerInput;

	D3DXCOLOR playerColor;
	// << Input

	// >> SceneChange
	SceneType setNowScene;
	// << SceneChange

	// void* ptrMessage;
};

#define GRAY    D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f)
#define BLACK	D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f)
#define WHITE	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
#define RED		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)
#define BLUE	D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)
#define GREEN	D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)
#define YELLOW	D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f)