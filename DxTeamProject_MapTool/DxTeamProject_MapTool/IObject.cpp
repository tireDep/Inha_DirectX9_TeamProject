#include "stdafx.h"
#include "IObject.h"
#include "Box.h"
#include "Sphere.h"
#include "Cylinder.h"

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

void IObject::CreateObject(const ObjectType objType)
{
	// >> todo : Setup에서 화면 중앙으로 세팅 되어야 할 듯
	if (objType == eBox)
	{
		CBox* box = new CBox;
		box->Setup();
	}
	else if (objType == eSphere)
	{
		CSphere* sphere = new CSphere;
		sphere->Setup();
	}
	else if (objType == eCylinder)
	{
		CCylinder* cylinder = new CCylinder;
		cylinder->Setup();
	}
}

void IObject::CreateObject(const ST_MapData& mapData)
{
	if (mapData.objType == eBox)
	{
		CBox* box = new CBox;
		box->Setup(mapData);
	}
	else if (mapData.objType == eSphere)
	{
		CSphere* sphere = new CSphere;
		sphere->Setup(mapData);
	}
	else if (mapData.objType == eCylinder)
	{
		CCylinder* cylinder = new CCylinder;
		cylinder->Setup(mapData);
	}
}
