#ifndef SABRE_ESP32_WAIT_FOR_H
#define SABRE_ESP32_WAIT_FOR_H

#include <esp_timer.h>
#include <freertos/FreeRTOS.h>
#include <sabre/utility/wait_for.hpp>

namespace sabre::esp32
{
    /**
     * @brief A class that waits for a condition to be met within a specified
     * timeout.
     *
     * This class provides a mechanism to repeatedly check a predicate function
     * until it returns true or the timeout is reached. It can be used for
     * waiting for asynchronous operations to complete or conditions to be met.
     */
    class WaitFor : public sabre::WaitFor
    {
    protected:
        uint64_t _get_current_time() const;
        void _sleep() const;

    public:
        /**
         * @brief Constructor for the WaitFor class.
         *
         * @param fn The predicate function to check.
         * @param timeout_in_ms The maximum time to wait in milliseconds.
         * @param sleep_time The time to sleep between checks in milliseconds.
         */
        WaitFor(sabre::WaitForPred fn, uint64_t timeout_in_ms,
                uint64_t sleep_time = 0);
    };
} // namespace sabre::esp32

#endif // SABRE_ESP32_WAIT_FOR_H