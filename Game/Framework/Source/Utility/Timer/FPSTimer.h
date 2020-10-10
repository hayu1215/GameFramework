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

    //現在のフレーム
    int m_count;

    //現在のFPS
    float m_fps;

    //平均をとるサンプルの数
    const int m_sampleNum;

    //目標のFPSの値
    const int m_targetFps;
};

}