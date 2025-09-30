#ifndef SABRE_OUTPUT_GPIO_H
#define SABRE_OUTPUT_GPIO_H

#include "gpio.hpp"

namespace sabre
{
    class OutputGPIO : public GPIO
    {
    public:
        /**
         * @brief Set the GPIO pin to high level.
         */
        virtual void set_high() = 0;

        /**
         * @brief Set the GPIO pin to low level.
         */
        virtual void set_low() = 0;

        /**
         * @brief Set the GPIO to a specific level.
         *
         * @param level The level to set the GPIO pin to. If true, sets to high;
         */
        virtual void set_level(bool level) = 0;
    };
    using OutputGPIOPtr = OutputGPIO *;
    using OutputGPIOSharedPtr = std::shared_ptr<OutputGPIO>;
}; // namespace sabre

#endif // SABRE_OUTPUT_GPIO_H