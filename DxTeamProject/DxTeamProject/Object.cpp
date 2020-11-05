#include "stdafx.h"
#include "Object.h"


CObject::CObject()
	: m_ulRefCount(1)
{
	g_pObjectManager->AddObject(this);
}

CObject::~CObject()
{
	g_pObjectManager->RemoveObject(this);
}

void CObject::AddRef()
{
	++m_ulRefCount;
}

void CObject::Release()
{
	--m_ulRefCount;
	if (m_ulRefCount == 0)
		delete this;
}
