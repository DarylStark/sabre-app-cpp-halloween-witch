#include "factory.hpp"

namespace sabre
{
    UARTStreamBufSharedPtr Factory::create_uart_output_stream_buffer(
        uint32_t uart_number, int32_t baud_rate, int32_t tx_pin, int32_t rx_pin,
        size_t buffer_size) const
    {
        const auto uart =
            create_uart_object(uart_number, baud_rate, tx_pin, rx_pin);
        if (!uart)
            return nullptr;
        return std::make_shared<UARTStreamBuf>(uart, buffer_size);
    }
} // namespace sabre