#include "stdafx.h"
#include "IObject.h"
#include "Box.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Tile.h"
#include "Background.h"

int IObject::m_nRefCnt = 0;

IObject::IObject()
{
	g_pObjectManager->AddObject(this);
	IObject::m_nRefCnt += 1;
}

IObject::~IObject()
{
}

void IObject::Release()
{
	g_pObjectManager->RemoveObject(this);
	IObject::m_nRefCnt -= 1;
}

void IObject::SetRefCnt(int set)
{
	IObject::m_nRefCnt = set;
}

void IObject::CreateObject(const ObjectType objType, int index)
{
	// >> FileLoader 생성
	switch (objType)
	{
	case eTile01: case eTile02:	case eTile03: case eTile04: case eTile05: case eTile06:
	case eTile07: case eTile08:	case eTile09: case eTile10: case eTile11: case eTile12: case eTile13:
	{
		ST_MapData mapData;
		mapData.vScale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);
		mapData.vRotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		mapData.vTranslate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// >> todo : translate 현 위치 중앙으로 받아오기

		mapData.objType = objType;

		mapData.strObjName = string("Tile") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Tile";
		mapData.strTxtPath = "Texture_01.png";

		if(objType == eTile10 || objType == eTile11 || objType == eTile12 || objType == eTile13)
			mapData.strXFilePath = string("Tile_") + to_string(objType + 1) + ".X";
		else
			mapData.strXFilePath = string("Tile_0") + to_string(objType + 1) + ".X";

		CTile* tile = new CTile;
		tile->Setup(mapData);
	}
		break;

	// todo : setup에서 화면 중앙 위치로 이동
	case eBox:
	{
		CBox* box = new CBox;
		box->Setup();
	}
		break;

	case eSphere:
	{
		CSphere* sphere = new CSphere;
		sphere->Setup();
	}
		break;

	case eCylinder:
	{
		CCylinder* cylinder = new CCylinder;
		cylinder->Setup();
	}
		break;

	case eATree:
	{
		ST_MapData mapData;
		mapData.vScale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);
		mapData.vRotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		mapData.vTranslate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// >> todo : translate 현 위치 중앙으로 받아오기

		mapData.objType = objType;

		mapData.strObjName = string("AutumnTree") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Background";
		mapData.strTxtPath = "autumn_texture.png";

		mapData.strXFilePath = string("AutumnTree_0") + to_string(index + 1) + ".X";

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
		break;

	case eSTree:
	{
		ST_MapData mapData;
		mapData.vScale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);
		mapData.vRotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		mapData.vTranslate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// >> todo : translate 현 위치 중앙으로 받아오기

		mapData.objType = objType;

		mapData.strObjName = string("SummerTree") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Background";
		mapData.strTxtPath = "summer_texture.png";

		mapData.strXFilePath = string("SummerTree_0") + to_string(index + 1) + ".X";

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
	break;

	case eWTree:
	{
		ST_MapData mapData;
		mapData.vScale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);
		mapData.vRotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		mapData.vTranslate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// >> todo : translate 현 위치 중앙으로 받아오기

		mapData.objType = objType;

		mapData.strObjName = string("WinterTree") + to_string(m_nRefCnt + 1);
		mapData.strFolderPath = "Resource/XFile/Background";
		mapData.strTxtPath = "winter_texture.png";

		mapData.strXFilePath = string("WinterTree_0") + to_string(index + 1) + ".X";

		CBackground* background = new CBackground;
		background->Setup(mapData);
	}
	break;

	}
}

void IObject::CreateObject(const ST_MapData& mapData)
{
	// >> SaveLoad 파일 생성
	switch (mapData.objType)
	{
	case eTile01: case eTile02:	case eTile03: case eTile04: case eTile05: case eTile06:
	case eTile07: case eTile08:	case eTile09: case eTile10: case eTile11: case eTile12: case eTile13:
	{
		CTile* tile = new CTile;
		tile->Setup(mapData);
	}
	break;

	case eBox:
	{
		CBox* box = new CBox;
		box->Setup(mapData);
	}
	break;

	case eSphere:
	{
		CSphere* sphere = new CSphere;
		sphere->Setup(mapData);
	}
	break;

	case eCylinder:
	{
		CCylinder* cylinder = new CCylinder;
		cylinder->Setup(mapData);
	}
	break;

	case eATree:
	case eSTree:
	case eWTree:
		CBackground* background = new CBackground;
		background->Setup(mapData);
		break;
	}
}
