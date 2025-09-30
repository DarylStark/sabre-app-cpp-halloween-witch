#ifndef SABRE_WIFI_SOFT_AP_H
#define SABRE_WIFI_SOFT_AP_H

namespace sabre
{
    /**
     * @brief An interface for a Wi-Fi Soft Access Point (AP).
     *
     * This class provides methods to initialize, start, stop, and deinitialize
     * a Wi-Fi Soft AP. It is designed to be implemented by classes that provide
     * specific functionality for managing a Wi-Fi Soft AP.
     */
    class WifiSoftAP
    {
    public:
        /**
         * @brief Initialize the Wi-Fi Soft AP.
         */
        virtual void init() = 0;

        /**
         * @brief Start the Wi-Fi Soft AP with the specified SSID and password.
         *
         * @param ssid The SSID of the Wi-Fi network.
         * @param password The password for the Wi-Fi network.
         */
        virtual void start(std::string ssid, std::string password) = 0;

        /**
         * @brief Stop the Wi-Fi Soft AP.
         */
        virtual void stop() = 0;

        /**
         * @brief Deinitialize the Wi-Fi Soft AP.
         *
         * This method is called to clean up resources and stop the Soft AP.
         */
        virtual void deinitialize() = 0;
    };
    using WifiSoftAPPtr = WifiSoftAP *;
    using WifiSoftAPSharedPtr = std::shared_ptr<WifiSoftAP>;
}; // namespace sabre

#endif // SABRE_WIFI_SOFT_AP_H