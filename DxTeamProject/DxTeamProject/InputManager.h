#pragma once
#include "Singleton.h"

class IListener;

#define g_pInputManager CInputManager::GetInstance()

class CInputManager : public CSingleton<CInputManager>
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
	void CheckInput(UINT message, WPARAM wParam, LPARAM lParam);
};

