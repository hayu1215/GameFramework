#pragma once

#include<chrono>

using namespace std::chrono;

namespace utility {

class ChronoTimer {
public:
    ChronoTimer();

    void restart();
    double elapsed();

private:
    system_clock::time_point m_start;
};

}