#pragma once

class ReleaseTimer final
{
private:
	class ReleaseTime
	{
		friend ReleaseTimer;
	private:
		ReleaseTime()
		{
			Reset();
		}
		~ReleaseTime() = default;

		void Reset()
		{
			QueryPerformanceFrequency(&m_CountTime);
			QueryPerformanceCounter(&m_CurTime);
			QueryPerformanceCounter(&m_PrevTime);
		}
		float Update()
		{
			QueryPerformanceCounter(&m_CurTime);

			m_dDeltaTime = (static_cast<double>(m_CurTime.QuadPart) - static_cast<double>(m_PrevTime.QuadPart)) / static_cast<double>(m_CountTime.QuadPart);

			m_fDeltaTime = static_cast<float>(m_dDeltaTime);
			m_PrevTime = m_CurTime;

			return m_fDeltaTime;
		}
	private:
		LARGE_INTEGER m_CountTime;
		LARGE_INTEGER m_CurTime;
		LARGE_INTEGER m_PrevTime;
		double m_dDeltaTime;
		float m_fDeltaTime;
	};
private:
	static ReleaseTime s_MainTimer;
public:
	ReleaseTimer() = delete;
	~ReleaseTimer() = delete;

	static float DeltaTime()
	{
		return s_MainTimer.m_fDeltaTime;
	}
	static void Update()
	{
		s_MainTimer.Update();
	}
	static void Reset()
	{
		s_MainTimer.Reset();
	}
};