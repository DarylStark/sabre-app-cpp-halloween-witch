#ifndef SABRE_ESP32_WIFI_SOFT_AP_H
#define SABRE_ESP32_WIFI_SOFT_AP_H

#include "wifi.hpp"
#include <esp_wifi.h>
#include <sabre/logging/logging.hpp>
#include <sabre/wifi/wifi_soft_ap.hpp>
#include <string>

namespace sabre::esp32
{
    /**
     * @brief Class for a Wi-Fi Soft Access Point (AP) on ESP32.
     *
     * This class implements the Wi-Fi Soft AP functionality using the ESP-IDF
     * Wi-Fi driver. It provides methods to initialize, start, stop, and
     * deinitialize a Wi-Fi Soft AP.
     */
    class WifiSoftAP : public sabre::WifiSoftAP
    {
    private:
        wifi_init_config_t _wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();
        wifi_config_t _wifi_config = {};
        std::shared_ptr<Wifi> _wifi_instance;

    protected:
        bool _wifi_started = false;
        sabre::Logger _logger;
        bool _initialized = false;

    public:
        /**
         * @brief Constructor for the WifiSoftAP class.
         *
         * Initializes the logger and sets the Wi-Fi instance.
         */
        WifiSoftAP();

        /**
         * @brief Destructor for the WifiSoftAP class.
         *
         * Cleans up resources and stops the Wi-Fi Soft AP if it is running.
         */
        ~WifiSoftAP();

        /**
         * @brief Initialize the Wi-Fi Soft AP.
         *
         * This method initializes the Wi-Fi Soft AP with the default
         * configuration. It should be called before starting the Soft AP.
         */
        void init();

        /**
         * @brief Start the Wi-Fi Soft AP with the specified SSID and password.
         *
         * @param ssid The SSID of the Wi-Fi network.
         * @param password The password for the Wi-Fi network.
         *
         * This method starts the Wi-Fi Soft AP with the given SSID and
         * password. It should be called after initializing the Soft AP.
         */
        void start(std::string ssid, std::string password);

        /**
         * @brief Stop the Wi-Fi Soft AP.
         *
         * This method stops the Wi-Fi Soft AP and cleans up resources.
         * It should be called when the Soft AP is no longer needed.
         */
        void stop();

        /**
         * @brief Deinitialize the Wi-Fi Soft AP.
         *
         * This method cleans up resources and stops the Soft AP.
         * It should be called to release resources when the Soft AP is no
         * longer needed.
         */
        void deinitialize();

        // Handlers for the `main event loop`
        void wifi_event_handler(esp_event_base_t event_base, int32_t event_id,
                                void *event_data);
    };
} // namespace sabre::esp32

#endif // SABRE_ESP32_WIFI_SOFT_AP_H