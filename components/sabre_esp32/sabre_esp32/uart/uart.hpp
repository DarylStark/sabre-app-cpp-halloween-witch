#ifndef SABRE_ESP32_UART_H
#define SABRE_ESP32_UART_H

#include <cstddef> // For size_t
#include <cstdint> // For uint32_t

#include <driver/uart.h>
#include <sabre/uart/uart.hpp>

#define BUF_SIZE 1024

namespace sabre::esp32
{
    /**
     * @brief Class for a UART interface on ESP32.
     *
     * This class implements the UART functionality using the ESP-IDF UART
     * driver. It provides methods to write bytes, flush the output, and read
     * bytes from the UART interface.
     */
    class UART : public sabre::UART
    {
    private:
        uart_port_t _port;
        int32_t _baud_rate;
        int _tx_pin;
        int _rx_pin;
        bool _is_initialized;

        void _initialize();

    public:
        /**
         * @brief Constructs a UART object for a specific UART port.
         *
         * @param port The UART port to be used (e.g., UART_NUM_0, UART_NUM_1).
         * @param baud_rate The baud rate for the UART communication.
         * @param tx_pin The GPIO pin number for the TX line (default is 1).
         * @param rx_pin The GPIO pin number for the RX line (default is 3).
         *
         * @throws `sabre::esp32::ESP_IDF_Error` if the UART driver fails to
         * initialize.
         */
        UART(uart_port_t port, int32_t baud_rate, int tx_pin = 1,
             int rx_pin = 3);

        /**
         * @brief Write bytes to the UART interface.
         *
         * @param data The byte to be written to the UART interface.
         *
         * @return The number of bytes written, or -1 on error.
         */
        int write_byte(char data) const override;

        /**
         * @brief Flush the UART output buffer.
         *
         * This method ensures that all data written to the UART is sent out
         * immediately.
         */
        void flush() override;
    };
} // namespace sabre::esp32

#endif // SABRE_ESP32_UART_H