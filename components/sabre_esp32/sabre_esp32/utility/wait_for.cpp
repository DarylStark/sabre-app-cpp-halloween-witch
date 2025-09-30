#include "wait_for.hpp"

namespace sabre::esp32
{
    uint64_t WaitFor::_get_current_time() const
    {
        return esp_timer_get_time() / 1000;
    }

    void WaitFor::_sleep() const
    {
        vTaskDelay(_sleep_time / portTICK_PERIOD_MS);
    }

    WaitFor::WaitFor(sabre::WaitForPred fn, uint64_t timeout_in_ms,
                     uint64_t sleep_time)
        : sabre::WaitFor(fn, timeout_in_ms, sleep_time)
    {
    }
} // namespace sabre::esp32