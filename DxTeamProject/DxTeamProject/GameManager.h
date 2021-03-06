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

	bool m_isAttModeIn;
	bool m_isAttMode;

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
	
	// >> todo : 세이브 파일 로드

	bool GetDevMode();
	bool GetUImode();
	bool GetAttMode();

	void ReceiveEvent(ST_EVENT eventMsg) override;
	string GetName() override;

	void SetClipCursor(int ySize);

	void SetGetOrb(string orbType);
	void InitializationOrb();
	bool GetIsHasOrb(string orbType);
	bool CompleteOrb();

	void SetNowScene(SceneType set);
	SceneType GetNowScene();

	//이어하기
	D3DXVECTOR3 SaveData();

	string SaveOrb();
	bool SaveBook();

};

