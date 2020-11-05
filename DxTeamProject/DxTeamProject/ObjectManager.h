#pragma once

#define		g_pObjectManager CObjectManager::GetInstance()

class CObjectManager
{
	//public:
	//	cObjectManager();
	//	~cObjectManager();

private:
	
	SingleTone(CObjectManager);
	std::set<CObject*> m_setObject;

public:
	void AddObject(CObject* pObject);
	void RemoveObject(CObject* pObject);
	void Destroy();

};

