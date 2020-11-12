#pragma once
#include "IListener.h"

#define g_gameManager CGameManager::GetInstance()

class CGameManager : public IListener 
{
private:
	bool m_isDevMoveIn;
	bool m_isDevMode;

	bool m_isUIModeIn;
	bool m_isUIMode;

	CGameManager();

public:
	static CGameManager* GetInstance();
	virtual ~CGameManager() { }

	bool GetDevMode();
	bool GetUImode();

	void ReceiveInput(UINT message, WPARAM wParam, LPARAM lParam) override;
	string GetName() override;

	void SetClipCursur(int ySize);
};
