#include "stdafx.h"
#include "Timer.h"

CTimer::CTimer()
{
}

CTimer::CTimer(const CTimer &)
{
}

CTimer::~CTimer()
{
}

void CTimer::Setup()
{
	// 고성능 타이머
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);

	m_ticsPerMs = (float)(m_frequency / 1000);
	QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);
}

void CTimer::Frame()
{
	INT64	currentTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	float timeDifference = (float)(currentTime - m_startTime);
	m_frameTime = timeDifference / m_ticsPerMs;
	m_startTime = currentTime;
}

float CTimer::GetTime()
{
	return m_frameTime;
}