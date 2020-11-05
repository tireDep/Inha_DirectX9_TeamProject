#include "stdafx.h"
#include "TimeManager.h"


CTimeManager::CTimeManager()
{
	//m_dwLastUpdateTime = GetCurrentTime();

	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);

	m_ticsPerMs = (float)(m_frequency / 1000);
	QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);
}


CTimeManager::~CTimeManager()
{
}

void CTimeManager::Update()
{
	//DWORD dwCurrentTime = GetCurrentTime();
	//m_fElapsedTime = (dwCurrentTime - m_dwLastUpdateTime) / 1000.f;
	//m_dwLastUpdateTime = dwCurrentTime;

	INT64	currentTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	float timeDifference = (float)(currentTime - m_startTime);
	m_frameTime = timeDifference / m_ticsPerMs;
	m_startTime = currentTime;
}

float CTimeManager::GetElapsedTime()
{
	//return m_fElapsedTime;
	return m_frameTime;
}

float CTimeManager::GetLastUpdateTime()
{
	return m_dwLastUpdateTime / 1000.f;
}
