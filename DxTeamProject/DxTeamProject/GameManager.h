#pragma once
#include "IListener.h"

enum class SceneType;
#define g_pGameManager CGameManager::GetInstance()

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

	bool m_Orbcomplete;
	// << �� �Ϸ�� ����

	
	// Synthesize(SceneType, m_SceneName, NowScene);
	SceneType m_SceneName;
	Synthesize(bool, m_isDataLoad, IsDataLoad);

	// Orb Item
	// bool Orb[6] = { false };
	map<string, bool> m_mapOrb; // >> orbType, isGet
	bool Item[ITEMCOUNT] = { false };
	
	CGameManager();
	void SetShowCursor(bool set);

public:
	static CGameManager* GetInstance();
	virtual ~CGameManager() { }

	void SetLoadData();
	
	// >> todo : ���̺� ���� �ε�

	bool GetDevMode();
	bool GetUImode();

	void ReceiveEvent(ST_EVENT eventMsg) override;
	string GetName() override;

	void SetClipCursor(int ySize);

	// >> �� �Ϸ�� ����
	bool GetGridMapMode();
	// << �� �Ϸ�� ����

	// void SetOrb(int index);
	// bool GetOrb(int index);

	void SetItem(int index);
	bool GetItem(int index);

	void SetGetOrb(string orbType);
	void InitializationOrb();
	bool GetIsHasOrb(string orbType);
	bool CompleteOrb();

	void SetNowScene(SceneType set);
	SceneType GetNowScene();

	//�̾��ϱ�
	D3DXVECTOR3 SaveData();
	bool SaveOrb();
	bool SaveBook();

};
