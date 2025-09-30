#ifndef SABRE_ESP32_EXCEPTIONS_H
#define SABRE_ESP32_EXCEPTIONS_H

#include <sabre/exceptions/exceptions.hpp>

namespace sabre::esp32
{
    /**
     * @brief Exception class for ESP-IDF specific errors.
     *
     * This class inherits from `sabre::APIError` and is used to throw
     * exceptions for errors that occur in the ESP-IDF context.
     */
    class ESP_IDF_Error : public sabre::APIError
    {
    public:
        /**
         * @brief Default constructor for `ESP_IDF_Error`.
         *
         * Initializes the error with a default message.
         */
        ESP_IDF_Error(const std::string &s) : APIError(s) {}
    };

    /**
     * @brief Throws an ESP_IDF_Error if the provided esp_err_t value is not
     * ESP_OK.
     *
     * @param err The esp_err_t value to check.
     * @param msg The error message to include in the exception if thrown.
     *
     * @throws `ESP_IDF_Error` if err is not `ESP_OK`.
     */
    inline void throw_if_esp_err(esp_err_t err, const std::string &msg)
    {
        if (err != ESP_OK)
            throw ESP_IDF_Error(msg);
    }

    /**
     * @brief Throws an ESP_IDF_Error if the provided value is negative.
     *
     * @param value The integer value to check.
     * @param msg The error message to include in the exception if thrown.
     *
     * @throws ESP_IDF_Error if value is less than 0.
     */
    inline void throw_if_negative_value(int32_t value, const std::string &msg)
    {
        if (value < 0)
            throw ESP_IDF_Error(msg);
    }
} // namespace sabre::esp32

#endif // SABRE_ESP32_EXCEPTIONS_H