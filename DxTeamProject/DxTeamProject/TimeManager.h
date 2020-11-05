#pragma once

#define	g_pTimeManager	CTimeManager::GetInstance()

class CTimeManager
{
private:
	SingleTone(CTimeManager);
private:
	float m_fElapsedTime;

	LARGE_INTEGER m_liLastTime;

	float m_fFPS_Timer;
	int m_FPS;
	int m_count;
public:
	void Update();
	float GetElapsedTime();
	int GetFPS();

};

