#include "stdafx.h"
#include "TimeManager.h"

CTimeManager::CTimeManager()
{
	m_dwLastUpdateTime = GetTickCount();
}

CTimeManager::~CTimeManager()
{
}

void CTimeManager::Update()
{
	DWORD dwCurrentTime = GetTickCount();
	m_fElapsedTime = (dwCurrentTime - m_dwLastUpdateTime) / 1000.0f;
	m_dwLastUpdateTime = dwCurrentTime;
}

float CTimeManager::GetElapsedTime()
{
	return m_fElapsedTime;
}

float CTimeManager::GetLastUpdateTime()
{
	return m_dwLastUpdateTime / 1000.0f;
}
