#include "stdafx.h"
#include "GameManager.h"

CGameManager::CGameManager()
{
	m_strName = "GameManager";

	m_isDevMode = false;
	m_isUIMode = false;

	SetClipCursur(0);
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
	RECT rc;
	POINT p1, p2;

	switch (message)
	{
	case WM_KEYDOWN:
	{
		if (VK_CONTROL == wParam && !m_isUIModeIn)
		{
			m_isUIMode = !m_isUIMode;
			m_isUIModeIn = !m_isUIModeIn;

			if (m_isUIMode)
			{
				SetClipCursur(-15);
				ShowCursor(true);
			}
			else
			{
				SetClipCursur(0);
				ShowCursor(false);
			}
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

void CGameManager::SetClipCursur(int ySize)
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
