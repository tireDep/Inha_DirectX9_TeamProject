#pragma once
#include "Singleton.h"

class IListener;

#define g_pInputManager CInputManager::GetInstance()

class CInputManager : public CSingleton<CInputManager>
{
private:
	bool m_IsInScreen = true;
	vector<IListener*> m_vecListener;

public:
	bool AddListener(IListener* listener);
	bool RemoveListener(IListener* listener);

	void CheckInput(UINT message, WPARAM wParam, LPARAM lParam);
};

