#include "stdafx.h"
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
