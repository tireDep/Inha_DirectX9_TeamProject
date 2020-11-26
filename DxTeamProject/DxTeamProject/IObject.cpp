#include "stdafx.h"
#include "Tile.h"
#include "IObject.h"

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

void IObject::CreateObject(const ST_MapData & mapData)
{
	switch (mapData.objType)
	{
	case eTile01: case eTile02:	case eTile03: case eTile04: case eTile05: case eTile06:
	case eTile07: case eTile08:	case eTile09: case eTile10: case eTile11: case eTile12: case eTile13:
	{
		CTile* tile = new CTile;
		tile->Setup(mapData);
	}
	break;

	/*case eBox:
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
	break;*/
	}
}
