#ifndef SABRE_UART_OUTPUT_STREAM_BUFFER_H
#define SABRE_UART_OUTPUT_STREAM_BUFFER_H

#include "uart.hpp"
#include <memory>
#include <streambuf>

namespace sabre
{
    /**
     * @brief A stream buffer for UART output.
     *
     * This class provides a stream buffer that can be used with UART devices
     * for output operations. It allows for buffered writing to UART, which can
     * improve performance by reducing the number of write operations.
     */
    class UARTStreamBuf : public std::streambuf
    {
        using int_type = std::streambuf::traits_type::int_type;

    private:
        UARTSharedPtr _uart;
        char *_buffer;
        size_t _buffer_size;

        void _reset_put_buffer();

    protected:
        /**
         * @brief Write a character to the UART device.
         *
         * This method is called when the connected `std::ostream` object tries
         * to write a character to the stream buffer but when the stream buffer
         * is full.
         *
         * @param c The character to write.
         *
         * @return Returns the character written, or `traits_type::eof()` if an
         * error occurs.
         */
        int_type overflow(int_type c) override;

        /**
         * @brief Write a sequence of characters to the UART device.
         *
         * This method is called when the connected `std::ostream` object tries
         * to write a sequence of characters to the stream buffer.
         *
         * @return Zero at all times.
         */
        int sync() override;

    public:
        /**
         * @brief Constructor for the UARTStreamBuf class.
         *
         * This constructor initializes the stream buffer with a UART device
         * and a specified buffer size.
         *
         * @param uart The UART device to use for output operations.
         * @param buffer_size The size of the internal buffer (default is 512).
         */
        UARTStreamBuf(UARTSharedPtr uart, size_t buffer_size = 512);

        /**
         * @brief Destructor for the UARTStreamBuf class.
         *
         * This destructor flushes the buffer and releases any allocated
         * resources.
         */
        ~UARTStreamBuf();
    };
    using UARTStreamBufPtr = UARTStreamBuf *;
    using UARTStreamBufSharedPtr = std::shared_ptr<UARTStreamBuf>;
} // namespace sabre

#endif // SABRE_UART_OUTPUT_STREAM_BUFFER_H