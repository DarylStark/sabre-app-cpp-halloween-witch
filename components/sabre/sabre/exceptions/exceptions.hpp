#ifndef SABRE_EXCEPTIONS_H
#define SABRE_EXCEPTIONS_H

#include <stdexcept>
#include <string>

namespace sabre
{
    /**
     * @brief Base class for all Sabre exceptions.
     *
     * This class is used as a base for all exceptions that are thrown by the
     * Sabre library. It inherits from `std::runtime_error` to provide a
     * standard way to handle exceptions in C++.
     */
    class SabreException : public std::runtime_error
    {
    public:
        /**
         * @brief Default constructor for SabreException.
         *
         * This constructor initializes the exception with a default message.
         */
        explicit SabreException(const std::string &message)
            : std::runtime_error(message)
        {
        }
    };

    /**
     * @brief Exception thrown by implementation on API errors.
     *
     * This exception is thrown when an operation is attempted on a API that
     * failed.
     */
    class APIError : public SabreException
    {
    protected:
        /**
         * @brief Constructor for APIError with a custom message.
         *
         * This constructor initializes the exception with a specific error
         * message.
         *
         * @param msg The error message to be associated with the exception.
         */
        APIError(const std::string &msg) : SabreException(msg) {}

    public:
        /**
         * @brief Default constructor for APIError.
         *
         * This constructor initializes the exception with a default message
         * indicating an unknown API error.
         */
        APIError() : SabreException("Unknown API error") {}
    };
} // namespace sabre

#endif // SABRE_EXCEPTIONS_H