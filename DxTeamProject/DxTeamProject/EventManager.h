#pragma once
#include "Singleton.h"

struct ST_EVENT;
class IListener;

#define g_pEventManager CEventManager::GetInstance()

class CEventManager : public CSingleton<CEventManager>
{
private:
	bool m_IsInScreen = true;
	vector<int> m_vecInputNum;
	vector<IListener*> m_vecListener;

public:
	bool AddListener(IListener* listener);
	bool RemoveListener(IListener* listener);

	void Setup();
	void Update();
	void CheckEvent(ST_EVENT eventMsg);
};

