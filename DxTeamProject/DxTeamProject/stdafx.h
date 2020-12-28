// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define _CRT_SECURE_NO_WARNINGS
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

#include <tchar.h>
#include <fstream>

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
#define SafeDeleteArray(p)	{ if(p) delete[]p; p=NULL; }
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

enum class Color : int
{
	Red = 0, Yellow, Green, Blue, Black, White, NONE = 999
};

enum class Pick : int
{
	Red = 0, Yellow, Green, Blue, Black, White, NONE = 999
};
//
#include "Object.h"
#include "ObjectManager.h"
#include "PhysicsObjectManager.h"
#include "FileLoadManager.h"
#include "SoundManager.h"

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

struct ST_PT_VERTEX
{
	D3DXVECTOR3	p;
	D3DXVECTOR2	t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};

enum class EventType : int
{
	eInputEvent, eSceneChangeEvent, 
	eColorChangeEvent, eChangedColorEvent, eColorEffect,
	eConditionChange,
	eNull
};

enum class SceneType
{
	eMainScene, ePickMainScene , eGameScene, eUIScene, eResultScene, 
	eEndingScene,eLoadStart, eLoading, ePauseScene,
	eNull
};

enum class PlayerInputType : int
{
	eUp, eDown, eLeft, eRight, eLeftUp, eLeftDown, eRightUp, eRightDown, eHold, eHoldPush, eHoldPull, eJump, eReset,
	eNull
};

struct ST_EVENT
{
	EventType eventType = EventType::eNull;
	
	// >> Input
	UINT message = 0;
	WPARAM wParam = 0; 
	LPARAM lParam = 0;
	PlayerInputType playerInput = PlayerInputType::eNull;
	// << Input

	// >> SceneChange
	SceneType setNowScene = SceneType::eNull;
	// << SceneChange

	// >> ConditionChange
	string conditionName = "";
	bool isCondition = "true";
	// << ConditionChange

	float duration = 0.0f;

	void* ptrMessage = NULL;
};

struct ST_XFile
{
	ID3DXMesh* pMesh = NULL;
	ID3DXBuffer* adjBuffer = NULL;
	ID3DXBuffer* mtrlBuffer = NULL;

	DWORD nMtrlNum = 0;
	vector<D3DMATERIAL9> vecMtrl;
	vector<IDirect3DTexture9*> vecTextrure;
};

enum ObjectType
{
	/* Tile */
	eTile01, eTile02, eTile03, eTile04, eTile05, eTile06,
	eTile07, eTile08, eTile09, eTile10, eTile11, eTile12, eTile13,

	/* BackObj, */
	eATree, eSTree, eWTree, eCTree,
	eSomethingElse, eBall, eChair, eUmbrella, eSnowman, eInvisibleWall,

	/* Object */
	eBox, eSphere, eCylinder,

	/* Gimmick, */
	eG_RotationBoard, eG_BreakWall, eG_DoorFrame, eG_Door, eG_ColorChanger, eG_Switch,  eG_MovingCube,

	/* Item */
	eBook, eOrb,

	/* Added */
	eFlower, eSprout, eBridge, eTrace, eTrigger,

	eNull
};

enum class OnOffCondition { eOrb, eItem, eSwitch, eNull };

struct ST_Gimmick
{
	bool isData = false;

	float roationSpeed_rotaitonBoard = 0.0f;
	int roationAxialIndex_rotaitonBoard = 0;
	// >> 회전판자

	int weightIndex = 0;
	int maxMassIndex_switch = 0;
	// >> 스위치?

	float startPos_movingCube = 0.0f;
	float endPos_movingCube = 0.0f;
	float speed_movingCube = 0.0f;
	int directionIndex_movingCube = 0;
	// >> 무빙큐브

	int onOffConditionIndex = 0;
	string conditionName = "";
	int conditionOrbIndex = 0;
	// >> 문, 컬러레이저 조건
};

struct ST_MapData
{
	string strFolderPath = "";
	string strXFilePath = "";
	string strTxtPath = "";

	string strObjName = "";
	ObjectType objType = ObjectType::eNull;

	D3DXVECTOR3 vScale = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 vRotate = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 vTranslate = D3DXVECTOR3(0, 0, 0);

	D3DXCOLOR dxColor = D3DXCOLOR(1, 1, 1, 1);

	vector<string> vecColorTag;

	int triggerIndex = 0;
	int zoneIndex = 0;

	ST_Gimmick gimmickData;
};

struct ST_Sprite
{
	D3DXIMAGE_INFO imageInfo;
	LPDIRECT3DTEXTURE9 lpTexture = NULL;
};

#define GRAY    D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f)
#define BLACK	D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f)
#define WHITE	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
#define RED		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)
#define BLUE	D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)
#define GREEN	D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)
#define YELLOW	D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f)

// Physical close to zero
inline bool CloseToZero(float testValue)
{
	bool answer = (testValue >= -0.000001f) && (testValue <= 0.000001f) ? true : false;
	return answer;
}

#include "ReleaseTimer.h"


enum class TriggerType { eSave, eZone };
enum class ZoneType { eWinter, eFall, eZone };