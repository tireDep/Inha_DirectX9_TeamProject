#include "stdafx.h"
#include "cObject.h"

cObject::cObject() 
	: m_ulRefCount(1)	// 자기자신이 있어서 1
{
	g_pObjectManger->AddObject(this);
}

cObject::~cObject()
{
	g_pObjectManger->RemoveObject(this);
}

void cObject::AddRef()
{
	++m_ulRefCount;
}

void cObject::Release()
{
	--m_ulRefCount;

	if (m_ulRefCount == 0)
		delete this;	// 실질적으로 사용되지 않음
}
