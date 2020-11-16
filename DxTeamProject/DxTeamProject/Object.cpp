#include "stdafx.h"
#include "Object.h"
#include "Ray.h"

int CObject::m_nRefCount = 0;

CObject::CObject()
{
	CObject::m_nRefCount += 1;
	g_pObjectManager->AddObject(this);
}

CObject::~CObject()
{
}

void CObject::Release()
{
	g_pObjectManager->RemoveObject(this);
	CObject::m_nRefCount -= 1;
}

void CObject::ReceiveEvent(ST_EVENT eventMsg)
{
}
