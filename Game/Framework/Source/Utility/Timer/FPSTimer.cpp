#include "FPSTimer.h"

namespace utility
{
	FPSTimer::FPSTimer() :
		m_sampleNum(100), m_TargetFps(60)
	{
	}


	FPSTimer::FPSTimer(int sampleNum, int targetFps) :
		m_sampleNum(sampleNum), m_TargetFps(targetFps)
	{
	}

	FPSTimer::~FPSTimer()
	{
	}

	void FPSTimer::update()
	{
		//最初だけ呼ばれるタイマーのスタート
		if (m_Count == 0)timer.restart();

		//サンプル数と現在のフレームが同じだったら
		if (m_Count == m_sampleNum)
		{
			m_Fps = 1.0f / ((timer.elapsed() / (float)m_sampleNum))*1000.0f;
			m_Count = 0;
			timer.restart();
		}
		m_Count += 1;
	}

	void FPSTimer::wait()
	{
		double minFrameTime = 1.0f / m_TargetFps * 1000.0f;
		std::chrono::milliseconds sleepTime((long long)(minFrameTime*m_Count - timer.elapsed()));
		if (sleepTime.count() > 0)std::this_thread::sleep_for(sleepTime);
	}

	float FPSTimer::getFPS()
	{
		return m_Fps;
	}
}