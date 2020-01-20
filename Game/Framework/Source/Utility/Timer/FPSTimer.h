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