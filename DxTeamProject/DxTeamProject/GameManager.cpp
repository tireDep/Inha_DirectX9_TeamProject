#include "stdafx.h"
#include "GameManager.h"

CGameManager::CGameManager()
{
	m_strName = "GameManager";

	m_isDevMode = false;
	m_isUIMode = false;
	
	// >> �� �Ϸ�� ���� ����
	m_isGridMap = false;
	// << �� �Ϸ�� ���� ����

	SetClipCursor(0);
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

bool CGameManager::GetGridMapMode()
{
	return m_isGridMap;
}

void CGameManager::ReceiveEvent(ST_EVENT eventMsg)
{
	RECT rc;
	POINT p1, p2;

	if (eventMsg.eventType == EventType::eInputEvent)
	{
		switch (eventMsg.message)
		{
		case WM_KEYDOWN:
		{
			if (VK_CONTROL == eventMsg.wParam && !m_isUIModeIn)
			{
				m_isUIMode = !m_isUIMode;
				m_isUIModeIn = !m_isUIModeIn;

				if (m_isUIMode)
				{
					SetClipCursor(-15);
					ShowCursor(true);
				}
				else
				{
					SetClipCursor(0);
					ShowCursor(false);
				}
			}

			if (VK_TAB == eventMsg.wParam && !m_isDevMoveIn)
			{
				m_isDevMode = !m_isDevMode;
				m_isDevMoveIn = !m_isDevMoveIn;
			}

			// >> �� �Ϸ�� ���� ����
			if (VK_SCROLL == eventMsg.wParam && !m_isGridMapIn)
			{
				m_isGridMap = !m_isGridMap;
				m_isGridMapIn = !m_isGridMapIn;
			}
			// << �� �Ϸ�� ���� ����
		}
		break;

		case WM_KEYUP:
		{
			if (VK_CONTROL == eventMsg.wParam)
				m_isUIModeIn = false;

			if (VK_TAB == eventMsg.wParam)
				m_isDevMoveIn = false;

			// >> �� �Ϸ�� ���� ����
			if (VK_SCROLL == eventMsg.wParam)
				m_isGridMapIn = false;
			// << �� �Ϸ�� ���� ����
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
