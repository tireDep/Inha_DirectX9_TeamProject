#include "stdafx.h"
#include "IListener.h"
#include "InputManager.h"

bool CInputManager::AddListener(IListener* listener)
{
	for (int i = 0; i < m_vecListener.size(); i++)
	{
		if (listener->GetName() == m_vecListener[i]->GetName())
		{
			MessageBox(g_hWnd, L"Same Name Existence", L"ERROR", MB_OK);
			return false;
		}
	}

	m_vecListener.push_back(listener);
	return true;
}

bool CInputManager::RemoveListener(IListener * listener)
{
	vector<IListener*>::iterator it;
	for (it = m_vecListener.begin(); it < m_vecListener.end();)
	{
		if ((*it)->GetName() == listener->GetName())
		{
			it = m_vecListener.erase(it);
			return true;
		}
		else
			it++;
	}

	MessageBox(g_hWnd, L"Fail Remove Listener", L"ERROR", MB_OK);
	return false;
}

void CInputManager::Setup()
{
	m_vecInputNum.push_back('W');
	m_vecInputNum.push_back('S');
	m_vecInputNum.push_back('A');
	m_vecInputNum.push_back('D');
}

void CInputManager::Update()
{
	for (int i = 0; i < m_vecInputNum.size(); i++)
	{
		if (GetKeyState(m_vecInputNum[i]) & 0x8000 && m_IsInScreen)
			CheckInput(m_vecInputNum[i], 0, 0);
	}
}

void CInputManager::CheckInput(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_ACTIVATE)
	{
		if (LOWORD(wParam) == WA_INACTIVE)
			m_IsInScreen = false;
		else
			m_IsInScreen = true;
	}

	if (m_IsInScreen)
	{
		for (int i = 0; i < m_vecListener.size(); i++)
			m_vecListener[i]->ReceiveInput(message, wParam, lParam);
	}
}
