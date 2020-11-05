#include "stdafx.h"
#include "ObjectManager.h"


CObjectManager::CObjectManager()
{
}


CObjectManager::~CObjectManager()
{
}

void CObjectManager::AddObject(CObject * pObject)
{
	m_setObject.insert(pObject);
}

void CObjectManager::RemoveObject(CObject * pObject)
{
	m_setObject.erase(pObject);
}

void CObjectManager::Destroy()
{
	m_setObject.clear();
}
