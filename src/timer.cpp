#include "timer.hpp"

using namespace utilities;

/*
 * @params:
 *    unsigned long count: how long to wait, in seconds
 */
Timer::Timer(unsigned long interval) { m_interval = interval; }

/* has that amount of time passed? */
bool Timer::ready() {
    if ((millis() - m_count) > (m_interval * 1000)) {
        m_count = millis();
        return true;
    }
    return false;
}
