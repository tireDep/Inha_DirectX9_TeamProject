#include "stdafx.h"
#include "GameManager.h"

CGameManager::CGameManager()
{
	m_strName = "GameManager";

	m_isDevMode = false;
	m_UImode = false;
}

CGameManager* CGameManager::GetInstance()
{
	static CGameManager instance;
	return &instance;
}

bool CGameManager::GetDevMode()
{
	return m_isDevMode;
}

bool CGameManager::GetUImode()
{
	return m_UImode;
}

void CGameManager::ReceiveInput(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
	{
		if (VK_CONTROL == wParam && (GetKeyState(wParam) & 0x8000 || GetKeyState(wParam) & 0x0000))
			m_UImode = !m_UImode;

		if (VK_TAB == wParam && (GetKeyState(wParam) & 0x8000 || GetKeyState(wParam) & 0x0000))
			m_isDevMode = !m_isDevMode;
	}
		break;

	}
}

string CGameManager::GetName()
{
	return m_strName;
}
