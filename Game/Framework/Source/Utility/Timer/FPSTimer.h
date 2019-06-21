#pragma once

#include"ChronoTimer.h"
#include<thread>

namespace utility
{
	class FPSTimer
	{
	public:
		FPSTimer();
		FPSTimer(int sampleNum, int targetFps);
		~FPSTimer();

		void update();
		void wait();
		float getFPS();

	private:
		ChronoTimer timer;

		//現在のフレーム
		int m_Count;

		//現在のFPS
		float m_Fps;

		//平均をとるサンプルの数
		const int m_sampleNum;

		//目標のFPSの値
		const int m_TargetFps;
	};
}