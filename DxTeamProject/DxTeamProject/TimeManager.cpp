#include "stdafx.h"
#include "TimeManager.h"

CTimeManager::CTimeManager()
	: m_fFPS_Timer(0)
	, m_FPS(0)
	, m_count(0)
	, m_fElapsedTime(0.0f)
{
	QueryPerformanceCounter(&m_liLastTime);
}

CTimeManager::~CTimeManager()
{
}

void CTimeManager::Update()
{
	LARGE_INTEGER CurTime, frequency, DeltaTime;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&CurTime);
	DeltaTime.QuadPart = (CurTime.QuadPart - m_liLastTime.QuadPart) * 1000000;
	DeltaTime.QuadPart /= frequency.QuadPart;

	m_fElapsedTime = DeltaTime.QuadPart * 0.000001f;

	m_fFPS_Timer += m_fElapsedTime;
	
	m_count++;

	if (m_fFPS_Timer > 1)
	{
		m_fFPS_Timer = 0;
		m_FPS = m_count;
		m_count = 0;
	}

	m_liLastTime = CurTime;
}

float CTimeManager::GetElapsedTime()
{
	if (m_fElapsedTime == 0)
		return 0.0001;
	else
		return m_fElapsedTime;
}

int CTimeManager::GetFPS()
{
	return m_FPS;
}