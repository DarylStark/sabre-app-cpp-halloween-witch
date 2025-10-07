#ifndef SABRE_CLIENTS_NTP_HPP
#define SABRE_CLIENTS_NTP_HPP

#include <memory>

namespace sabre
{
    class NTPClient
    {
    public:
        /**
         * @brief Starts the NTP client.
         *
         * This will initialize the NTP client and start synchronizing time
         * with the specified NTP server.
         */
        virtual void start() = 0;

        /**
         * @brief Stops the NTP client.
         *
         * This will stop the NTP client and cease time synchronization.
         */
        virtual void stop() = 0;

        /**
         * @brief Checks if the NTP client is synchronized.
         *
         * @returns true if the NTP client is synchronized, false otherwise.
         */
        virtual bool is_synchronized() const = 0;
    };
    using NTPClientPtr = NTPClient *;
    using NTPClientSharedPtr = std::shared_ptr<sabre::NTPClient>;
} // namespace sabre

#endif // SABRE_CLIENTS_NTP_HPP