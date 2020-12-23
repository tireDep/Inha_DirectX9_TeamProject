#pragma once
#include "IListener.h"

enum class SceneType;
#define g_pGameManager CGameManager::GetInstance()

class CGameManager : public IListener 
{
private:
	bool m_isDevMoveIn;
	bool m_isDevMode;

	bool m_isUIModeIn;
	bool m_isUIMode;

	bool m_Orbcomplete;

	SceneType m_SceneName;
	Synthesize(bool, m_isDataLoad, IsDataLoad);

	map<string, bool> m_mapOrb; // >> orbType, isGet
	
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

	void SetGetOrb(string orbType);
	void InitializationOrb();
	bool GetIsHasOrb(string orbType);
	bool CompleteOrb();

	void SetNowScene(SceneType set);
	SceneType GetNowScene();

	//�̾��ϱ�
	D3DXVECTOR3 SaveData();

	string SaveOrb();
	bool SaveBook();

};

