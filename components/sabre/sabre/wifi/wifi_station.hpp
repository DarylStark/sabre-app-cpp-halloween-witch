#ifndef SABRE_WIFI_STATION_H
#define SABRE_WIFI_STATION_H

#include <string>

namespace sabre
{
    /**
     * @brief An interface for a Wi-Fi Station.
     *
     * This class provides methods to initialize, connect, disconnect, stop,
     * and deinitialize a Wi-Fi Station. It is designed to be implemented by
     * classes that provide specific functionality for managing a Wi-Fi Station.
     */
    class WifiStation
    {
    public:
        /**
         * @brief Initialize the Wi-Fi Station.
         *
         * This method is called to set up the Wi-Fi Station before any
         * connection attempts are made.
         */
        virtual void init() = 0;

        /**
         * @brief Connect to a Wi-Fi network.
         *
         * @param ssid The SSID of the Wi-Fi network to connect to.
         * @param password The password for the Wi-Fi network.
         */
        virtual void connect(const std::string &ssid,
                             const std::string &password) = 0;

        /**
         * @brief Disconnect from the currently connected Wi-Fi network.
         *
         * This method is called to terminate the connection to the Wi-Fi
         * network.
         */
        virtual void disconnect() = 0;

        /**
         * @brief Stop the Wi-Fi Station.
         *
         * This method is called to stop the Wi-Fi Station, typically when it is
         * no longer needed or before deinitialization.
         */
        virtual void stop() = 0;

        /**
         * @brief Deinitialize the Wi-Fi Station.
         *
         * This method is called to clean up resources and stop the Wi-Fi
         * Station.
         */
        virtual void deinitialize() = 0;

        /**
         * @brief Get the current connection status of the Wi-Fi Station.
         *
         * @return True if the Wi-Fi Station is connected to a network, false
         * otherwise.
         */
        virtual bool is_connected() const = 0;

        /**
         * @brief Check if the Wi-Fi Station has an IPv4 address.
         *
         * @return True if the Wi-Fi Station has an IPv4 address, false
         * otherwise.
         */
        virtual bool has_ipv4_address() const = 0;
    };
    using WifiStationPtr = WifiStation *;
    using WifiStationSharedPtr = std::shared_ptr<WifiStation>;
} // namespace sabre

#endif // SABRE_WIFI_STATION_H