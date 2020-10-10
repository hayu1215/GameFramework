#include"ChronoTimer.h"

namespace utility {

ChronoTimer::ChronoTimer() {
    restart();
}

void ChronoTimer::restart() {
    m_start = system_clock::now();
}

double ChronoTimer::elapsed() {
    auto end = system_clock::now();
    return duration_cast<milliseconds>(end - m_start).count();
}

}