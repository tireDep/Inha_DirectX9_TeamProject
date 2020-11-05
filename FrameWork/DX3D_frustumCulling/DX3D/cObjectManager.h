#pragma once
#include "stdafx.h"

#define g_pObjectManger cObjectManager::GetInstance()

class cObjectManager
{
private:
	Singletone(cObjectManager);

	set<cObject*> m_setObject;

public:
	void AddObject(cObject* pObject);
	void RemoveObject(cObject* pObject);
	void Destroy();

};