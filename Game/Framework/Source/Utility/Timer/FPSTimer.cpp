#include"FpsTimer.h"
#include<string>
#include<Framework/Source/Utility/Debug/Log.h>

namespace utility {

FpsTimer::FpsTimer()
    : m_sampleNum(100), m_targetFps(60), m_count(0), m_fps(0) {}


FpsTimer::FpsTimer(int sampleNum, int targetFps)
    : m_sampleNum(sampleNum), m_targetFps(targetFps), m_count(0), m_fps(0) {}

FpsTimer::~FpsTimer() {}

void FpsTimer::update() {
    //最初だけ呼ばれるタイマーのスタート
    if (m_count == 0) m_timer.restart();

    //サンプル数と現在のフレームが同じだったら
    if (m_count == m_sampleNum) {
        m_fps = 1.0f / ((m_timer.elapsed() / (float)m_sampleNum)) * 1000.0f;
        m_count = 0;
        m_timer.restart();
        debug::Log(std::to_string(m_fps));
    }
    m_count += 1;
}

void FpsTimer::wait() {
    double minFrameTime = 1.0f / m_targetFps * 1000.0f;
    std::chrono::milliseconds sleepTime((long long)(minFrameTime * m_count - m_timer.elapsed()));
    if (sleepTime.count() > 0) std::this_thread::sleep_for(sleepTime);
}

float FpsTimer::getFps() {
    return m_fps;
}

}