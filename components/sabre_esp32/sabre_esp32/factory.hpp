#ifndef SABRE_ESP32_FACTORY_H
#define SABRE_ESP32_FACTORY_H

#include "clients/mqtt.hpp"
#include "clients/ntp.hpp"
#include "gpio/input_gpio.hpp"
#include "gpio/output_gpio.hpp"
#include "uart/uart.hpp"
#include "utility/wait_for.hpp"
#include "wifi/wifi_soft_ap.hpp"
#include "wifi/wifi_station.hpp"
#include <map>
#include <memory>
#include <sabre/factory.hpp>

namespace sabre::esp32
{
    /**
     * @brief Factory class for creating ESP32-specific objects.
     *
     * This class implements the sabre::Factory interface and provides methods
     * to create various ESP32-specific objects such as UART, GPIO, Wi-Fi
     * Station, Wi-Fi Soft AP, MQTT Client, and WaitFor.
     */
    class Factory : public sabre::Factory
    {
    private:
        std::map<uint16_t, std::unique_ptr<std::ostream>> _output_streams;

    public:
        /**
         * @brief Create a UART object for the specified UART number.
         *
         * @param uart_number The UART number to configure the object with.
         * @param baud_rate The baud rate for the serial interface.
         * @param tx_pin Transmit pin.
         * @param rx_pin Receive pin.
         *
         * @returns A UARTSharedPtr shared pointer to a UART object.
         */
        sabre::UARTSharedPtr create_uart_object(uint32_t uart_number,
                                                int32_t baud_rate,
                                                int32_t tx_pin,
                                                int32_t rx_pin) const override;

        /**
         * @brief Create a a InputGPIO object.
         *
         * @param pin the pin number for the GPIO.
         *
         * @returns A InputGPIOSharedPtr shared pointer to a InputGPIO object.
         */
        sabre::InputGPIOSharedPtr create_input_gpio(int32_t pin) const;

        /**
         * @brief Create a OutputGPIO object.
         *
         * @param pin the pin number for the GPIO.
         *
         * @returns A OutputGPIOSharedPtr shared pointer to a OutputGPIO object.
         */
        sabre::OutputGPIOSharedPtr create_output_gpio(int32_t pin) const;

        /**
         * @brief Create a Wi-Fi Station object.
         *
         * @returns A WifiStationSharedPtr shared pointer to a WifiStation
         * object.
         */
        sabre::WifiStationSharedPtr create_wifi_station() const;

        /**
         * @brief Create a Wi-Fi Soft AP object.
         *
         * @returns A WifiSoftAPSharedPtr shared pointer to a WifiSoftAP object.
         */
        sabre::WifiSoftAPSharedPtr create_wifi_soft_ap() const;

        /**
         * @brief Create a MQTT Client object.
         *
         * @returns A MQTTClientSharedPtr shared pointer to a MQTTClient object.
         */
        sabre::MQTTClientSharedPtr create_mqtt_client() const;

        /**
         * @brief Create a WaitFor object.
         *
         * @param fn The predicate function to check.
         * @param timeout_in_ms The maximum time to wait in milliseconds.
         * @param sleep_time The time to sleep between checks in milliseconds.
         *
         * @returns A WaitForSharedPtr shared pointer to a WaitFor object.
         */
        sabre::WaitForSharedPtr create_wait_for(WaitForPred fn,
                                                uint64_t timeout_in_ms,
                                                uint64_t sleep_time) const;

        /**
         * @brief Create a `NTPClient` object.
         *
         * @param server the NTP server to use.
         *
         * @returns A `NTPClientSharedPtr` shared pointer to a `NTPClient`.
         */
        NTPClientSharedPtr create_ntp_client(const std::string &server) const;
    };
} // namespace sabre::esp32

#endif /* SABRE_ESP32_FACTORY_H */