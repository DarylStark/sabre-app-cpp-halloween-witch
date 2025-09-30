#include "wall_clock.hpp"

#include <sys/time.h>

namespace sabre::esp32
{
    uint64_t WallClock::now_ms()
    {
        timeval tv;
        gettimeofday(&tv, nullptr);
        return (uint64_t)tv.tv_sec * 1000 + (uint64_t)tv.tv_usec / 1000;
    }

    void WallClock::set_now_ms(uint64_t time_in_ms)
    {
        struct timeval tv;
        tv.tv_sec = time_in_ms / 1000;
        tv.tv_usec = (time_in_ms % 1000) * 1000;
        settimeofday(&tv, nullptr);
    }
} // namespace sabre::esp32