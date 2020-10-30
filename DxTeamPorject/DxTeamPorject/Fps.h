#pragma once

class CFps
{
public:
	CFps();
	CFps(const CFps&);
	~CFps();
private:
	int m_fps;
	int m_count;
	DWORD m_startTime;
public:
	void Setup();
	void Frame();
	int GetFps();
};