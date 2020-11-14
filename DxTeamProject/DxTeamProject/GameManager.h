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

	// >> 맵 완료시 삭제
	bool m_isGridMapIn;
	bool m_isGridMap;
	// << 맵 완료시 삭제

	CGameManager();

public:
	static CGameManager* GetInstance();
	virtual ~CGameManager() { }

	bool GetDevMode();
	bool GetUImode();

	void ReceiveEvent(ST_EVENT eventMsg) override;
	string GetName() override;

	void SetClipCursur(int ySize);

	// >> 맵 완료시 삭제
	bool GetGridMapMode();
	// << 맵 완료시 삭제
};
