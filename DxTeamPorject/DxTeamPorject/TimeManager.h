#pragma once

#define	g_pTimeManager	CTimeManager::GetInstance()

class CTimeManager
{
private:
	SingleTone(CTimeManager);
private:
	DWORD m_dwLastUpdateTime;
	float m_fElapsedTime;

	INT64	m_frequency = 0;
	float	m_ticsPerMs = 0;
	INT64	m_startTime = 0;
	float	m_frameTime = 0;
public:
	void Update();
	float GetElapsedTime();
	float GetLastUpdateTime();

};

