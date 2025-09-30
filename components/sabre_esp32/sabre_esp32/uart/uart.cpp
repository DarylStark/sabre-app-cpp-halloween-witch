#include "uart.hpp"
#include "../exceptions/exceptions.hpp"

namespace sabre::esp32
{
    UART::UART(uart_port_t port, int32_t baud_rate, int tx_pin, int rx_pin)
        : _port(port), _baud_rate(baud_rate), _tx_pin(tx_pin), _rx_pin(rx_pin),
          _is_initialized(false)
    {
        _initialize();
    }

    void UART::_initialize()
    {
        // TODO: Make the variables configurable

        if (_is_initialized)
            return;

        uart_config_t uart_config = {.baud_rate = _baud_rate,
                                     .data_bits = UART_DATA_8_BITS,
                                     .parity = UART_PARITY_DISABLE,
                                     .stop_bits = UART_STOP_BITS_1,
                                     .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
                                     .rx_flow_ctrl_thresh = 122,
                                     .source_clk = UART_SCLK_APB,
                                     .flags = {
                                         .allow_pd = 0,
                                         .backup_before_sleep = 0,
                                     }};

        // Install UART driver
        throw_if_esp_err(
            uart_driver_install(_port, BUF_SIZE * 2, 0, 0, NULL, 0),
            "Failed to install UART driver");

        // Configure UART parameters
        throw_if_esp_err(uart_param_config(_port, &uart_config),
                         "Failed to configure UART parameters");

        // Set UART pins
        throw_if_esp_err(uart_set_pin(_port, _tx_pin, _rx_pin,
                                      UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE),
                         "Failed to set UART pins");
        _is_initialized = true;
    }

    int UART::write_byte(char data) const
    {
        int bytes_written = uart_write_bytes(_port, &data, 1);
        throw_if_negative_value(bytes_written, "Failed to write byte to UART");
        return bytes_written;
    }

    void UART::flush()
    {
        throw_if_esp_err(uart_flush_input(_port), "Failed to flush UART input");
    }
} // namespace sabre::esp32