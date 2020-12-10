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

	// >> �� �Ϸ�� ����
	bool m_isGridMapIn;
	bool m_isGridMap;
	// << �� �Ϸ�� ����

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

	// >> �� �Ϸ�� ����
	bool GetGridMapMode();
	// << �� �Ϸ�� ����

	void SetOrb(int index);
	bool GetOrb(int index);
	void SetItem(int index);
	bool GetItem(int index);
};
