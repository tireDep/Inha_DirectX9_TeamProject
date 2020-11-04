#include "stdafx.h"
#include "TimeManager.h"


CTimeManager::CTimeManager()
{
	m_dwLastUpdateTime = GetCurrentTime();
}


CTimeManager::~CTimeManager()
{
}

void CTimeManager::Update()
{
	DWORD dwCurrentTime = GetCurrentTime();
	m_fElapsedTime = (dwCurrentTime - m_dwLastUpdateTime) / 1000.f;
	m_dwLastUpdateTime = dwCurrentTime;
}

float CTimeManager::GetElapsedTime()
{
	return m_fElapsedTime;
}

float CTimeManager::GetLastUpdateTime()
{
	return m_dwLastUpdateTime / 1000.f;
}
