#ifndef SABRE_FACTORY_H
#define SABRE_FACTORY_H

#include "clients/mqtt.hpp"
#include "clients/ntp.hpp"
#include "gpio/input_gpio.hpp"
#include "gpio/output_gpio.hpp"
#include "uart/uart.hpp"
#include "uart/uart_output_stream_buffer.hpp"
#include "utility/wait_for.hpp"
#include "wifi/wifi_soft_ap.hpp"
#include "wifi/wifi_station.hpp"
#include <memory>
#include <ostream>

namespace sabre
{
    /**
     * @brief Abstract factory for object creation.
     *
     * Creates objects for a specific implementation. The methods of
     * this factory return shared pointers to the real implemented objects. This
     * should be overriden by implementations to return the correct object
     * for the specific implementation.
     */
    class Factory
    {
    public:
        /**
         * @brief Create a `UART` object.
         *
         * @param uart_number the UART number to configure the object with.
         * @param baud_rate the baud rate for the serial interface.
         * @param tx_pin transmit pin.
         * @param rx_pin receive pin.
         *
         * @returns A `UARTSharedPtr` shared pointer to a `UART` object.
         */
        virtual UARTSharedPtr create_uart_object(uint32_t uart_number,
                                                 int32_t baud_rate,
                                                 int32_t tx_pin,
                                                 int32_t rx_pin) const = 0;

        /**
         * @brief Create a `UARTStreamBuf` object.
         *
         * @param uart_number the UART number to configure the object with.
         * @param baud_rate the baud rate for the serial interface.
         * @param tx_pin transmit pin.
         * @param rx_pin receive pin.
         * @param buffer_size the size of the buffer in bytes.
         *
         * @returns A `UARTStreamBufSharedPtr` shared pointer to a
         * `UARTStreamBuf` object.
         */
        virtual UARTStreamBufSharedPtr create_uart_output_stream_buffer(
            uint32_t uart_number, int32_t baud_rate, int32_t tx_pin,
            int32_t rx_pin, size_t buffer_size) const;

        /**
         * @brief Create a `InputGPIO` object.
         *
         * @param pin the pin number for the GPIO.
         *
         * @returns A `InputGPIOSharedPtr` shared pointer to a `InputGPIO`
         * object.
         */
        virtual InputGPIOSharedPtr create_input_gpio(int32_t pin) const = 0;

        /**
         * @brief Create a `OutputGPIO` object.
         *
         * @param pin the pin number for the GPIO.
         *
         * @returns A `OutputGPIOSharedPtr` shared pointer to a `OutputGPIO`
         * object.
         */
        virtual OutputGPIOSharedPtr create_output_gpio(int32_t pin) const = 0;

        /**
         * @brief Create a `WifiStation` object.
         *
         * @returns A `WifiStationSharedPtr` shared pointer to a `WifiStation`
         * object.
         */
        virtual WifiStationSharedPtr create_wifi_station() const = 0;

        /**
         * @brief Create a `WifiSoftAP` object.
         *
         * @returns A `WifiSoftAPSharedPtr` shared pointer to a `WifiSoftAP`
         * object.
         */
        virtual WifiSoftAPSharedPtr create_wifi_soft_ap() const = 0;

        /**
         * @brief Create a `MQTTClient` object.
         *
         * @returns A `MQTTClientSharedPtr` shared pointer to a `MQTTClient`
         * object.
         */
        virtual MQTTClientSharedPtr create_mqtt_client() const = 0;

        /**
         * @brief Create a `WaitFor` object.
         *
         * @param fn the function to run in the WaitFor.
         * @param timeout_in_ms the maximum runtime in ms of the function.
         * @param sleep_time how much time (in ms) to sleep between each
         * iteration.
         *
         * @returns A `WaitForSharedPtr` shared pointer to a `WaitFor`
         * object.
         */
        virtual WaitForSharedPtr create_wait_for(WaitForPred fn,
                                                 uint64_t timeout_in_ms,
                                                 uint64_t sleep_time) const = 0;

        /**
         * @brief Create a `NTPClient` object.
         *
         * @param server the NTP server to use.
         *
         * @returns A `NTPClientSharedPtr` shared pointer to a `NTPClient`.
         */
        virtual NTPClientSharedPtr
        create_ntp_client(const std::string &server) const = 0;
    };
    using FactoryPtr = Factory *;
    using FactorySharedPtr = std::shared_ptr<Factory>;
} // namespace sabre

#endif // SABRE_FACTORY_H