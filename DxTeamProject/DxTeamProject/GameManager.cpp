#include "stdafx.h"
#include "GameManager.h"

CGameManager::CGameManager()
{
	m_strName = "GameManager";

	m_isDevMode = false;
	m_isUIMode = false;

	ShowCursor(false);
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
	return m_isUIMode;
}

void CGameManager::ReceiveInput(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
	{
		if (VK_CONTROL == wParam && !m_isUIModeIn)
		{
			m_isUIMode = !m_isUIMode;
			m_isUIModeIn = !m_isUIModeIn;

			if (m_isUIMode)
				ShowCursor(true);
			else
				ShowCursor(false);
		}

		if (VK_TAB == wParam && !m_isDevMoveIn)
		{
			m_isDevMode = !m_isDevMode;
			m_isDevMoveIn = !m_isDevMoveIn;
		}
	}
	break;

	case WM_KEYUP:
	{
		if (VK_CONTROL == wParam)
			m_isUIModeIn = false;

		if (VK_TAB == wParam)
			m_isDevMoveIn = false;
	}
	break;
	}
}

string CGameManager::GetName()
{
	return m_strName;
}
