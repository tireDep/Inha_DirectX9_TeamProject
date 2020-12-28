#include "stdafx.h"
#include "GameManager.h"
#include "SoundManager.h"

D3DXVECTOR3 CGameManager::SaveData()
{
	fstream fin;
	D3DXVECTOR3 SaveData;
	fin.open("SaveData.txt");
	fin >> SaveData.x >> SaveData.y >> SaveData.z;
	fin.close();

	return SaveData;
}

string CGameManager::SaveOrb()
{
	ifstream fin;
	string line;
	string search = "0";
	fin.open("OrbData.txt");
	if (g_pObjectManager->KeepGoing == false) //시작..
	{
		line = "1";
	}
	else //이어하기
	{
		while (getline(fin, line))
		{
			
			fin >> line;
			if (line.find(search, 0) != string::npos)
			{		
				
				return line;
			}
		}

	}
	fin.close();
	return line;
}

bool CGameManager::SaveBook()
{
	bool SaveData;
	//if (g_pObjectManager->KeepGoing == false) //처음시작.
	//	SaveData = true;
	//else
	//{
	//	ifstream fin;

	//	fin.open("OrbData.txt");
	//	fin >> SaveData;
	//	fin.close();
	//}

	return SaveData;

}

CGameManager::CGameManager()
{
	m_strName = "GameManager";

	m_SceneName = SceneType::eMainScene;

	m_isDevMode = false;
	m_isUIMode = false;
	m_isAttMode = false;
	m_Orbcomplete = false;

	SetClipCursor(0);

	m_isDataLoad = false;
}

void CGameManager::SetShowCursor(bool set)
{
	/*
	ShowCursor(true) : + 1
	ShowCursor(false) : - 1

	카운트가 음수여야 화면에서 커서가 사라짐
	*/
	if (set == false)
	{
		SetClipCursor(0);
		while (ShowCursor(false) >= 0);
	}
	else
	{
		SetClipCursor(-15);
		ShowCursor(set);
	}
}

CGameManager* CGameManager::GetInstance()
{
	static CGameManager instance;
	return &instance;
}

void CGameManager::SetLoadData()
{
	// >> todo : 세이브데이터 로드
	// 세이브 데이터 파일이 없으면 초기값 세팅
	pair<string, bool> temp;

	temp.first = "Black";	temp.second = false;	m_mapOrb.insert(temp);
	temp.first = "White";	temp.second = false;	m_mapOrb.insert(temp);
	temp.first = "Yellow";	temp.second = false;	m_mapOrb.insert(temp);
	temp.first = "Green";	temp.second = false;	m_mapOrb.insert(temp);
	temp.first = "Red";		temp.second = false;	m_mapOrb.insert(temp);
	temp.first = "Blue";	temp.second = false;	m_mapOrb.insert(temp);


}

bool CGameManager::GetDevMode()
{
	return m_isDevMode;
}

bool CGameManager::GetUImode()
{
	return m_isUIMode;
}

bool CGameManager::GetAttMode()
{
	return m_isAttMode;
}

void CGameManager::SetGetOrb(string orbType)
{
	// >> 색상 오브 획득
	map<string, bool>::iterator it;
	for (it = m_mapOrb.begin(); it != m_mapOrb.end(); it++)
	{
		if (it->first == orbType)
		{
			it->second = true;
			
			ST_EVENT msg;
			msg.eventType = EventType::eConditionChange;
			msg.conditionName = it->first;
			msg.isCondition = false;
			g_pEventManager->CheckEvent(msg);
		}
	}
	g_pSoundManager->PlaySFX("Orb");
}

void CGameManager::InitializationOrb()
{
	map<string, bool>::iterator it;
	for (it = m_mapOrb.begin(); it != m_mapOrb.end(); it++)
	{
		it->second = false;
	}
}

bool CGameManager::GetIsHasOrb(string orbType)
{
	// >> 색상 오브를 가지고 있는지 판별
	map<string, bool>::iterator it;
	for (it = m_mapOrb.begin(); it != m_mapOrb.end(); it++)
	{
		if (it->first == orbType)
			return it->second;
	}
}

bool CGameManager::CompleteOrb()
{
	if (GetIsHasOrb("Blue") && GetIsHasOrb("Green") && GetIsHasOrb("Red") &&
		GetIsHasOrb("White") && GetIsHasOrb("Yellow") && GetIsHasOrb("Black"))
	{
		m_Orbcomplete = true;
		SetNowScene(SceneType::eEndingScene);
	}

	return m_Orbcomplete;
}

void CGameManager::SetNowScene(SceneType set)
{
	if ((set == SceneType::eLoading || set == SceneType::eLoadStart)&& m_isDataLoad)
		set = SceneType::eGameScene;

	if (set == SceneType::eEndingScene)
	{
		InitializationOrb();
		SetShowCursor(true);
	}
	
	if (set == SceneType::eGameScene)
	{
		SetShowCursor(false);

		m_isUIMode = false;
		m_isUIModeIn = false;
		m_isDevMode = false;
		m_isDevMoveIn = false;
		m_isAttMode = false;
		m_isAttModeIn = false;
	}

	m_SceneName = set;
}

SceneType CGameManager::GetNowScene()
{
	return m_SceneName;
}

void CGameManager::ReceiveEvent(ST_EVENT eventMsg)
{
	RECT rc;
	POINT p1, p2;

	if (eventMsg.eventType == EventType::eInputEvent)
	{
		switch (eventMsg.message)
		{
		case WM_RBUTTONDOWN:
			if (m_SceneName == SceneType::eEndingScene)
			{
				InitializationOrb();
				m_SceneName = SceneType::eMainScene;
				return;
			}
			break;

		case WM_KEYDOWN:
		{
			if (VK_CONTROL == eventMsg.wParam && !m_isUIModeIn)
			{
				m_isUIMode = !m_isUIMode;
				m_isUIModeIn = !m_isUIModeIn;

				if (m_isUIMode)
				{
					SetShowCursor(true);
				}
				else
				{
					SetShowCursor(false);
				}
			}

			if (VK_TAB == eventMsg.wParam && !m_isDevMoveIn)
			{
				m_isDevMode = !m_isDevMode;
				m_isDevMoveIn = !m_isDevMoveIn;
			}

			if (0x4F == eventMsg.wParam && !m_isAttModeIn)
			{
				m_isAttMode = !m_isAttMode;
				m_isAttModeIn = !m_isAttModeIn;
			}
		}
		break;

		case WM_KEYUP:
		{
			if (VK_CONTROL == eventMsg.wParam)
				m_isUIModeIn = false;

			if (VK_TAB == eventMsg.wParam)
				m_isDevMoveIn = false;

			if (0X4F == eventMsg.wParam)
				m_isAttModeIn = false;
		}
		break;
		}
	}
}

string CGameManager::GetName()
{
	return m_strName;
}

void CGameManager::SetClipCursor(int ySize)
{
	RECT rc;
	POINT p1, p2;

	GetClientRect(g_hWnd, &rc);

	p1.x = rc.left;
	p1.y = rc.top + ySize; // x_Btn
	p2.x = rc.right;
	p2.y = rc.bottom;

	ClientToScreen(g_hWnd, &p1);
	ClientToScreen(g_hWnd, &p2);

	rc.left = p1.x;
	rc.top = p1.y;
	rc.right = p2.x;
	rc.bottom = p2.y;

	ClipCursor(&rc);
}