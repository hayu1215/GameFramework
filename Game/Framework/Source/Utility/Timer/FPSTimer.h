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

		//���݂̃t���[��
		int m_Count;

		//���݂�FPS
		float m_Fps;

		//���ς��Ƃ�T���v���̐�
		const int m_sampleNum;

		//�ڕW��FPS�̒l
		const int m_TargetFps;
	};
}