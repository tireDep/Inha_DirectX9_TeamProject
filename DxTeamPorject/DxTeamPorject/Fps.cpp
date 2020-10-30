#include "stdafx.h"
#include "Fps.h"


CFps::CFps()
{
}

CFps::CFps(const CFps &)
{
}


CFps::~CFps()
{
}

void CFps::Setup()
{
	m_fps = 0;
	m_count = 0;
	//m_startTime = timeGetTime();
	m_startTime = GetTickCount();
}

void CFps::Frame()
{
	m_count++;

	//if (timeGetTime() >= (m_startTime + 1000))
	//{
	//	m_fps = m_count;
	//	m_count = 0;
	//	m_startTime = timeGetTime();
	//}

	if (GetTickCount() >= (m_startTime + 1000))
	{
		m_fps = m_count;
		m_count = 0;
		m_startTime = GetTickCount();
	}
}

int CFps::GetFps()
{
	return m_fps;
}