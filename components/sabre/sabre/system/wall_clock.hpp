#ifndef SABRE_WALL_CLOCK_HPP
#define SABRE_WALL_CLOCK_HPP

#include <cstdint>
#include <memory>

namespace sabre
{
    /**
     * @brief Interface for a wall clock.
     *
     * This interface provides methods to get the current time in milliseconds
     * since the epoch (1970-01-01 00:00:00 UTC) and to set the current time.
     * It is used to provide a consistent time source for the application.
     *
     * This interface is intended to be implemented by platform-specific
     * wall clock classes, allowing for different implementations depending on
     * the platform (e.g., ESP32, Linux, etc.).
     */
    class WallClock
    {
    public:
        /**
         * @brief Get the current time in ms since 1970-01-01
         *
         * @return The current time since 1970-01-01 00:00:00 in milliseconds.
         */
        virtual uint64_t now_ms() const = 0;

        /**
         * @brief Set the current time in ms since 1970-01-01
         *
         * @param time_in_ms The time to set in milliseconds since 1970-01-01
         * 00:00:00.
         */
        virtual void set_now_ms(uint64_t time_in_ms) = 0;
    };
    using WallClockPtr = WallClock *;
    using WallClockSharedPtr = std::shared_ptr<WallClock>;
} // namespace sabre

#endif // SABRE_WALL_CLOCK_HPP