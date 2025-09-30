#ifndef SABRE_ESP32_WALL_CLOCK_HPP
#define SABRE_ESP32_WALL_CLOCK_HPP

#include <sabre/system/wall_clock.hpp>

namespace sabre::esp32
{
    /**
     * @brief Class that represents a wall clock.
     *
     * This class provides to get the current time in milliseconds
     * since the epoch (1970-01-01 00:00:00 UTC) and to set the current time.
     * It is used to provide a consistent time source for the application.
     */
    class WallClock : public sabre::WallClock
    {
    public:
        /**
         * @brief Get the current time in ms since 1970-01-01
         *
         * @return The current time since 1970-01-01 00:00:00 in milliseconds.
         */
        uint64_t now_ms() override;

        /**
         * @brief Set the current time in ms since 1970-01-01
         *
         * @param time_in_ms The time to set in milliseconds since 1970-01-01
         * 00:00:00.
         */
        void set_now_ms(uint64_t time_in_ms) override;
    };
} // namespace sabre::esp32

#endif // SABRE_ESP32_WALL_CLOCK_HPP