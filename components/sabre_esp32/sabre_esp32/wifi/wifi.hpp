#ifndef SABRE_ESP32_WIFI_H
#define SABRE_ESP32_WIFI_H

#include <bitset>
#include <esp_wifi.h>
#include <memory>
#include <sabre/logging/logging.hpp>

namespace sabre::esp32
{
    /**
     * @brief Enum class representing the different Wi-Fi modes.
     *
     * This enum class defines the modes in which the Wi-Fi can operate,
     * specifically as a Station (STA) or a Soft Access Point (AP).
     */
    enum class WifiMode
    {
        STATION,
        SOFT_AP
    };

    /**
     * @brief Class for managing Wi-Fi functionality on ESP32.
     *
     * This class provides methods to initialize, start, stop, and deinitialize
     * the Wi-Fi functionality. It supports both Station and Soft Access Point
     * modes and handles events related to Wi-Fi operations.
     *
     * This class should be used by the WifiSoftAP and WifiStation classes
     * to manage the underlying Wi-Fi functionality. It provides a singleton
     * instance that can be accessed throughout the application.
     *
     * @note This class is designed to be a singleton, ensuring that only one
     * instance of the Wi-Fi manager exists at any time. It is responsible for
     * managing the Wi-Fi initialization and configuration, as well as handling
     * events related to Wi-Fi operations.
     */
    class Wifi
    {
    private:
        Wifi();
        Wifi(const Wifi &) = delete;
        Wifi(Wifi &&) = delete;
        Wifi &operator=(const Wifi &) = delete;
        Wifi &operator=(Wifi &&) = delete;

        static std::shared_ptr<Wifi> _instance;

        bool _is_initialized = false;
        bool _wifi_started = false;

        wifi_init_config_t _wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();

        std::bitset<2> _enabled_modes;
        sabre::Logger _logger;

        void _set_mode_to_none();
        void _set_mode_to_both();
        void _set_mode_to_station();
        void _set_mode_to_soft_ap();
        void _set_mode();

    public:
        /**
         * @brief Get the singleton instance of the Wifi class.
         *
         * This method returns a shared pointer to the singleton instance of
         * the Wifi class. If the instance does not exist, it will be created.
         *
         * @return A shared pointer to the Wifi instance.
         */
        static std::shared_ptr<Wifi> get_instance();

        /**
         * @brief Initialize the Wi-Fi manager.
         *
         * This method initializes the Wi-Fi manager with the default
         * configuration. It should be called before starting the Wi-Fi
         * functionality.
         *
         * @throws `sabre::esp32::ESP_IDF_Error` if the initialization fails.
         */
        void init();

        /**
         * @brief Start the Wi-Fi functionality.
         *
         * This method starts the Wi-Fi functionality based on the enabled
         * modes. It should be called after initializing the Wi-Fi manager.
         *
         * @throws `sabre::esp32::ESP_IDF_Error` if starting Wi-Fi fails.
         */
        void start();

        /**
         * @brief Stop the Wi-Fi functionality for a specific mode.
         *
         * This method stops the Wi-Fi functionality for the specified mode.
         * It should be called when the Wi-Fi functionality is no longer needed
         * for that mode.
         *
         * @param mode The Wi-Fi mode to stop (Station or Soft AP).
         */
        void stop(WifiMode mode);

        /**
         * @brief Deinitialize the Wi-Fi manager.
         *
         * This method cleans up resources and stops the Wi-Fi functionality.
         * It should be called when the Wi-Fi manager is no longer needed.
         */
        void deinitialize();

        /**
         * @brief Add a specific mode to the enabled modes.
         *
         * This method adds the specified mode to the set of enabled modes.
         * If the mode is already enabled, it will not be added again.
         *
         * @param mode The Wi-Fi mode to add (Station or Soft AP).
         */
        void add_mode(WifiMode mode);

        /**
         * @brief Remove a specific mode from the enabled modes.
         *
         * This method removes the specified mode from the set of enabled modes.
         * If the mode is not enabled, it will not be removed.
         *
         * @param mode The Wi-Fi mode to remove (Station or Soft AP).
         */
        void remove_mode(WifiMode mode);

        /**
         * @brief Handle Wi-Fi events.
         *
         * This method handles Wi-Fi events and dispatches them to the
         * appropriate event handlers.
         *
         * @param event_base The event base.
         * @param event_id The event ID.
         * @param event_data The event data.
         */
        void handle_event(esp_event_base_t event_base, int32_t event_id,
                          void *event_data);
    };
}; // namespace sabre::esp32

#endif // SABRE_ESP32_WIFI_H