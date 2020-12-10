#pragma once
#include "IListener.h"

#define g_gameManager CGameManager::GetInstance()

const static int ITEMCOUNT = 10;

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

	// Orb Item
	bool Orb[6] = { false };
	bool Item[ITEMCOUNT] = { false };
public:
	static CGameManager* GetInstance();
	virtual ~CGameManager() { }

	bool GetDevMode();
	bool GetUImode();

	void ReceiveEvent(ST_EVENT eventMsg) override;
	string GetName() override;

	void SetClipCursor(int ySize);

	// >> 맵 완료시 삭제
	bool GetGridMapMode();
	// << 맵 완료시 삭제

	void SetOrb(int index);
	bool GetOrb(int index);
	void SetItem(int index);
	bool GetItem(int index);
};
