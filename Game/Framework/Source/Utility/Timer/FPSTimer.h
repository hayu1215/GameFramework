#pragma once

#include"ChronoTimer.h"
#include<thread>

namespace utility {

class FpsTimer {
public:
    FpsTimer();
    FpsTimer(int sampleNum, int targetFps);
    ~FpsTimer();

    void update();
    void wait();
    float getFps();

private:
    ChronoTimer m_timer;

    //���݂̃t���[��
    int m_count;

    //���݂�FPS
    float m_fps;

    //���ς��Ƃ�T���v���̐�
    const int m_sampleNum;

    //�ڕW��FPS�̒l
    const int m_targetFps;
};

}