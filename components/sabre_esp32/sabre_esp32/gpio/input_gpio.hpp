#ifndef SABRE_ESP32_INPUT_GPIO_H
#define SABRE_ESP32_INPUT_GPIO_H

#include <cstdint>
#include <driver/gpio.h>
#include <map>
#include <memory>
#include <sabre/gpio/input_gpio.hpp>

namespace sabre::esp32
{
    /**
     * @brief Class for an input GPIO pin on ESP32.
     *
     * This class implements the input GPIO functionality using the ESP-IDF
     * GPIO driver. It provides methods to read the pin level, enable pull-up or
     * pull-down resistors, disable them, and add interrupt handlers for various
     * trigger types (rising edge, falling edge, both edges, low level, high
     * level).
     */
    class InputGPIO : public sabre::InputGPIO
    {
    private:
        int32_t _pin_number;
        gpio_num_t _gpio_num;
        ISRConfigSharedPtr _config;

        static std::unordered_map<sabre::ISRTrigger, gpio_int_type_t>
            _trigger_map;
        static bool _isr_service_installed;

        bool _get_level() const override;

    public:
        /**
         * @brief Constructs an InputGPIO object for a specific pin number.
         *
         * @param pin_number The GPIO pin number to be used.
         *
         * @throws `sabre::esp32::ESP_IDF_Error` if the pin number is invalid or
         * if the GPIO driver fails to initialize.
         */
        InputGPIO(int32_t pin_number);

        /**
         * @brief Destructs the InputGPIO object.
         *
         * This will reset the GPIO pin and clean up any resources used by the
         * input GPIO.
         */
        ~InputGPIO();

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
         * @brief Enables the pull-up resistor on the GPIO pin.
         *
         * This will configure the pin to use an internal pull-up resistor.
         *
         * @throws `sabre::esp32::ESP_IDF_Error` if enabling the pull-up fails.
         */
        void enable_pullup() override;

        /**
         * @brief Enables the pull-down resistor on the GPIO pin.
         *
         * This will configure the pin to use an internal pull-down resistor.
         *
         * @throws `sabre::esp32::ESP_IDF_Error` if enabling the pull-down
         * fails.
         */
        void enable_pulldown() override;

        /**
         * @brief Disables the pull-up resistor on the GPIO pin.
         *
         * This will remove the internal pull-up configuration from the pin.
         *
         * @throws `sabre::esp32::ESP_IDF_Error` if disabling the pull-up fails.
         */
        void disable_pullup() override;

        /**
         * @brief Disables the pull-down resistor on the GPIO pin.
         *
         * This will remove the internal pull-down configuration from the pin.
         *
         * @throws `sabre::esp32::ESP_IDF_Error` if disabling the pull-down
         * fails.
         */
        void disable_pulldown() override;

        /**
         * @brief Add an interrupt handler for the GPIO pin.
         *
         * This method allows the user to register an interrupt service routine
         * (ISR) handler for the GPIO pin. The handler will be called when the
         * specified trigger condition is met.
         *
         * @param handler The ISR handler function to be called on interrupt.
         * @param trigger The trigger condition for the interrupt.
         */
        void add_interrupt_handler(sabre::ISRHandler,
                                   sabre::ISRTrigger trigger);
    };
} // namespace sabre::esp32

#endif // SABRE_ESP32_INPUT_GPIO_H