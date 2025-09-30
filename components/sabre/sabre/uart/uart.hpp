#ifndef SABRE_UART_H
#define SABRE_UART_H

#include <cstddef> // For size_t
#include <cstdint> // For uint32_t
#include <memory>

namespace sabre
{
    /**
     * @brief Abstract base class for UART communication.
     *
     * This class defines the interface for UART communication, providing
     * methods to write a byte and flush the output buffer. It is intended to be
     * implemented by specific UART communication classes.
     */
    class UART
    {
    public:
        /**
         * @brief Write a byte to the UART device.
         *
         * This method is used to send a single byte of data over the UART
         * interface.
         *
         * @param data The byte of data to be sent.
         *
         * @return Returns 0 on success, or a negative error code on failure.
         */
        virtual int write_byte(char data) const = 0;

        /**
         * @brief Flush the output buffer of the UART device.
         *
         * This method is used to ensure that all data in the output buffer is
         * sent to the UART device. It is typically called after writing
         * multiple bytes to ensure that they are transmitted.
         */
        virtual void flush() = 0;
    };
    using UARTPtr = UART *;
    using UARTSharedPtr = std::shared_ptr<UART>;
} // namespace sabre

#endif /* SABRE_UART_H */