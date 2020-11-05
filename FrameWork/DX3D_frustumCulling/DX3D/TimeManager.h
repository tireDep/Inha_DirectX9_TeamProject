#pragma once

#define g_pTimeManager CTimeManager::GetInstance()

class CTimeManager
{
private:
	Singletone(CTimeManager);

	DWORD m_dwLastUpdateTime;
	float m_fElapsedTime;

public:
	void Update();
	float GetElapsedTime();
	float GetLastUpdateTime();
};

