#pragma once

#include"ChronoTimer.h"
#include<thread>

namespace utility
{
	class FpsTimer
	{
	public:
		FpsTimer();
		FpsTimer(int sampleNum, int targetFps);
		~FpsTimer();

		void update();
		void wait();
		float getFps();

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