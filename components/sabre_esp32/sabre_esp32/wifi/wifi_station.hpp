#ifndef SABRE_ESP32_WIFI_STATION_H
#define SABRE_ESP32_WIFI_STATION_H

#include "wifi.hpp"
#include <esp_wifi.h>
#include <sabre/generic/ipv4_address.hpp>
#include <sabre/logging/logging.hpp>
#include <sabre/wifi/wifi_station.hpp>
#include <string>

namespace sabre::esp32
{
    /**
     * @brief Class for a Wi-Fi Station on ESP32.
     *
     * This class implements the Wi-Fi Station functionality using the ESP-IDF
     * Wi-Fi driver. It provides methods to initialize, connect, disconnect,
     * stop, and deinitialize a Wi-Fi Station.
     */
    class WifiStation : public sabre::WifiStation
    {
    private:
        wifi_init_config_t _wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();
        wifi_config_t _wifi_config = {};
        std::shared_ptr<Wifi> _wifi_instance;

    protected:
        bool _wifi_started = false;
        bool _connected = false;
        bool _initialized = false;

        sabre::Logger _logger;

        sabre::IPv4Address _ipv4_address;
        sabre::IPv4Address _ipv4_mask;
        sabre::IPv4Address _ipv4_gateway;

    public:
        /**
         * @brief Constructor for the WifiStation class.
         *
         * Initializes the logger and sets the Wi-Fi instance.
         */
        WifiStation();

        /**
         * @brief Destructor for the WifiStation class.
         *
         * Cleans up resources and stops the Wi-Fi Station if it is running.
         */
        ~WifiStation();

        /**
         * @brief Initialize the Wi-Fi Station.
         *
         * This method initializes the Wi-Fi Station with the default
         * configuration. It should be called before connecting to a network.
         */
        void init() override;

        /**
         * @brief Connect to a Wi-Fi network.
         *
         * @param ssid The SSID of the Wi-Fi network to connect to.
         * @param password The password for the Wi-Fi network.
         *
         * This method attempts to connect to the specified Wi-Fi network using
         * the provided SSID and password.
         */
        void connect(const std::string &ssid,
                     const std::string &password) override;

        /**
         * @brief Disconnect from the currently connected Wi-Fi network.
         */
        void disconnect() override;

        /**
         * @brief Stop the Wi-Fi Station.
         *
         * This method stops the Wi-Fi Station, typically when it is no longer
         * needed or before deinitialization.
         */
        void stop() override;

        /**
         * @brief Deinitialize the Wi-Fi Station.
         *
         * This method cleans up resources and stops the Wi-Fi Station.
         * It should be called when the Wi-Fi Station is no longer needed.
         */
        void deinitialize() override;

        /**
         * @brief Get the current connection status of the Wi-Fi Station.
         *
         * @return True if the Wi-Fi Station is connected to a network, false
         * otherwise.
         */
        bool is_connected() const;

        /**
         * @brief Check if the Wi-Fi Station has an IPv4 address.
         *
         * @return True if the Wi-Fi Station has an IPv4 address, false
         * otherwise.
         */
        bool has_ipv4_address() const;

        /**
         * @brief Event handler for Wi-Fi events.
         */
        void wifi_event_handler(esp_event_base_t event_base, int32_t event_id,
                                void *event_data);

        /**
         * @brief Event handler for IP events.
         */
        void ip_event_handler(esp_event_base_t event_base, int32_t event_id,
                              void *event_data);
    };
} // namespace sabre::esp32

#endif // SABRE_ESP32_WIFI_STATION_H