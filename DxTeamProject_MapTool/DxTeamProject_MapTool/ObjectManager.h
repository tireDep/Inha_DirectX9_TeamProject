#pragma once
#include "Singleton.h"
#include "Ray.h"

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
	void Update(CRay * ray);
	void Render();

	void RemoveClickedObj();

	vector<IObject *> GetVecObject();
};

