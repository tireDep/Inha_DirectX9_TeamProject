#pragma once
class CTimer
{
public:
	CTimer();
	CTimer(const CTimer&);
	~CTimer();
private:
	INT64	m_frequency = 0;
	float	m_ticsPerMs = 0;
	INT64	m_startTime = 0;
	float	m_frameTime = 0;
public:
	void Setup();
	void Frame();
	float GetTime();
};