#pragma once

#define SafeRelease(p) { if(p) p->Release(); p = NULL; }
#define SafeDelete(p) { if(p) delete p; }
#define SafeAddRef(p)	{if(p) p->AddRef() ; }

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

#define Synthesize(varType, varName, funName) \
protected : varType varName ; \
public : inline varType Get##funName(void) const { return varName ; } \
public : inline void Set##funName(const varType var) { varName = var ; }

#define Synthesize_Pass_by_Ref(varType, varName, funName) \
protected : varType varName ; \
public : varType& Get##funName(void) { return varName ; } \
public : void Set##funName(const varType& var) { varName = var ;}

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

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")

#include <iostream>
#include <vector>
#include <map>
#include <string>

extern HWND g_hWnd;

using namespace std;

#include "DeviceManager.h"
#include "ObjectManager.h"
#include "FileLoadManager.h"

struct ST_PC_VERTEX
{
	D3DXVECTOR3  p;
	D3DCOLOR	 c;
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

struct ST_PN_VERTEX
{
	D3DXVECTOR3	p;
	D3DXVECTOR3	n;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL };
};

enum ObjectType
{
#ifdef _DEBUG
	// >> release 버전에 유의할 것!!
	/* Tile */
	eTile01, eTile02, eTile03, eTile04, eTile05, eTile06,
	eTile07, eTile08, eTile09, eTile10, eTile11, eTile12, eTile13,

	/* BackObj, */
	eATree, eSTree, eWTree, eCTree,
	eSomethingElse, eBall, eChair, eUmbrella, eSnowman, eInvisibleWall,

	/* Object */
	eBox, eSphere, eCylinder,

	/* Gimmick, */
	eG_RotationBoard, eG_BreakWall, eG_DoorFrame, eG_Door, eG_ColorChanger, eG_Switch, eG_MovingCube,

	/* Item */
	eBook, eOrb,

	/* Added */
	eFlower,

	eNull

#else
	eTile01, eTile02, eTile03, eTile04, eTile05, eTile06,
	eTile07, eTile08, eTile09, eTile10, eTile11, eTile12, eTile13,
	/* eBackObj, */ eATree, eSTree, eWTree, eCTree,
	eSomethingElse, eBall, eChair, eUmbrella, eSnowman, eInvisibleWall,
	eBox, eSphere, eCylinder,
	/* eGimmick, */ eG_RotationBoard, eG_BreakWall, eG_ColorChanger, eG_Door, eG_Switch,
	eNull
#endif // _Debug
};

struct ST_Gimmick
{
	bool isData;

	float roationSpeed_rotaitonBoard;
	int roationAxialIndex_rotaitonBoard;
	// >> 회전판자

	int conditionIndex;
	int maxMassIndex;
	// >> 스위치?

	float startPos_movingCube;
	float endPos_movingCube;
	float speed_movingCube;
	int directionIndex_movingCube;
	// >> 무빙큐브
};

struct ST_MapData
{
	string strFolderPath;
	string strXFilePath;
	string strTxtPath;

	string strObjName;
	ObjectType objType;

	D3DXVECTOR3 vScale;
	D3DXVECTOR3 vRotate;
	D3DXVECTOR3 vTranslate;

	D3DXCOLOR dxColor;

	ST_Gimmick gimmickData;
};

struct ST_XFile
{
	ID3DXMesh* pMesh;
	ID3DXBuffer* adjBuffer;
	ID3DXBuffer* mtrlBuffer;

	DWORD nMtrlNum;
	vector<D3DMATERIAL9> vecMtrl;
	vector<IDirect3DTexture9*> vecTextrure;
};

struct ST_Sprite
{
	D3DXIMAGE_INFO imageInfo;
	LPDIRECT3DTEXTURE9 lpTexture;
};
