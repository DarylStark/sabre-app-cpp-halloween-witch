#ifndef SABRE_ESP32_OUTPUT_GPIO_H
#define SABRE_ESP32_OUTPUT_GPIO_H

#include <cstdint>
#include <driver/gpio.h>
#include <memory>
#include <sabre/gpio/output_gpio.hpp>

namespace sabre::esp32
{
    /**
     * @brief Class for an output GPIO pin on ESP32.
     *
     * This class implements the output GPIO functionality using the ESP-IDF
     * GPIO driver. It provides methods to set the pin high, low, or to a
     * specific level, and to reset the pin.
     */
    class OutputGPIO : public sabre::OutputGPIO
    {
    private:
        int32_t _pin_number;
        gpio_num_t _gpio_num;

    public:
        OutputGPIO(int32_t pin_number);
        ~OutputGPIO();

        /**
         * @brief Resets the GPIO pin to its default state.
         *
         * This will reset the pin configuration and release any resources
         * associated with it.
         *
         * @throws `sabre::esp32::ESP_IDF_Error` if the reset operation fails.
         */
        void reset() override;

        /**
         * @brief Set the GPIO pin to high level.
         *
         * @throws `sabre::esp32::ESP_IDF_Error` if the operation fails.
         */
        void set_high() override;

        /**
         * @brief Set the GPIO pin to low level.
         *
         * @throws `sabre::esp32::ESP_IDF_Error` if the operation fails.
         */
        void set_low() override;

        /**
         * @brief Set the GPIO to a specific level.
         *
         * @param level The level to set the GPIO pin to. If true, sets to high;
         *              if false, sets to low.
         *
         * @throws `sabre::esp32::ESP_IDF_Error` if the operation fails.
         */
        void set_level(bool level) override;
    };
} // namespace sabre::esp32

#endif // SABRE_ESP32_OUTPUT_GPIO_H