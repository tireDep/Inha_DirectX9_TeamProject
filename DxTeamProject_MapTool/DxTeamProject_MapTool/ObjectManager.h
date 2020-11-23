#pragma once
#include "Singleton.h"

class IObject;

#define g_pObjectManager CObjectManager::GetInstance()

class CObjectManager : public CSingleton<CObjectManager>
{
private:
	vector<IObject *> m_vecObject;

public:
	void AddObject(IObject* pObject);
	void RemoveObject(IObject* pObject);
	void Destroy();

	void Update();
	void Render();
};

