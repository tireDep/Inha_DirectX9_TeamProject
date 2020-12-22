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

	// >> 맵 완료시 삭제
	bool m_isGridMapIn;
	bool m_isGridMap;

	bool m_Orbcomplete;
	// << 맵 완료시 삭제

	
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
	
	// >> todo : 세이브 파일 로드

	bool GetDevMode();
	bool GetUImode();

	void ReceiveEvent(ST_EVENT eventMsg) override;
	string GetName() override;

	void SetClipCursor(int ySize);

	// >> 맵 완료시 삭제
	bool GetGridMapMode();
	// << 맵 완료시 삭제

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

	//이어하기
	D3DXVECTOR3 SaveData();
	bool SaveOrb();
	bool SaveBook();

};
