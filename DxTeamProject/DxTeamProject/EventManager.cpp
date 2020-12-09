#include "stdafx.h"
#include "EventManager.h"

bool CEventManager::AddListener(IListener * listener)
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

bool CEventManager::RemoveListener(IListener * listener)
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

void CEventManager::Update()
{
	bool pushW = GetKeyState('W') & 0x8000;
	bool pushS = GetKeyState('S') & 0x8000;
	bool pushA = GetKeyState('A') & 0x8000;
	bool pushD = GetKeyState('D') & 0x8000;
	bool pushF = GetKeyState('F') & 0x8000;

	if (!pushW && !pushS && !pushA && !pushD && !pushF)
		return;

	ST_EVENT msg;
	msg.eventType = EventType::eInputEvent;

	// float duration = g_pTimeManager->GetElapsedTime();
	// msg.ptrMessage = &duration;

	if (pushW && pushA)
		msg.playerInput = PlayerInputType::eLeftUp;
	else if (pushW && pushD)
		msg.playerInput = PlayerInputType::eRightUp;
	else if (pushW)
		msg.playerInput = PlayerInputType::eUp;

	else if (pushS && pushA)
		msg.playerInput = PlayerInputType::eLeftDown;
	else if (pushS && pushD)
		msg.playerInput = PlayerInputType::eRightDown;
	else if (pushS)
		msg.playerInput = PlayerInputType::eDown;

	else if (pushA)
		msg.playerInput = PlayerInputType::eLeft;
	else if (pushD)
		msg.playerInput = PlayerInputType::eRight;

	else if (pushF && pushW)
		msg.playerInput = PlayerInputType::eHoldPush;
	else if (pushF && pushS)
		msg.playerInput = PlayerInputType::eHoldPull;

	CheckEvent(msg);
}

void CEventManager::CheckEvent(ST_EVENT eventMsg)
{
	if (eventMsg.message == WM_ACTIVATE)
	{
		if (LOWORD(eventMsg.wParam) == WA_INACTIVE)
			m_IsInScreen = false;
		else
			m_IsInScreen = true;
	}

	if (m_IsInScreen)
	{
		for (int i = 0; i < m_vecListener.size(); i++)
			m_vecListener[i]->ReceiveEvent(eventMsg);
	}
}
