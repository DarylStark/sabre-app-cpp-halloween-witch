#ifndef SABRE_INPUT_GPIO_H
#define SABRE_INPUT_GPIO_H

#include "gpio.hpp"
#include <functional>
#include <memory>

namespace sabre
{
    using ISRHandler = std::function<void(int)>;

    /**
     * @brief Structure to hold the configuration for an ISR handler.
     *
     * This structure contains the handler function and the GPIO pin number
     * associated with the interrupt.
     */
    struct ISRConfig
    {
        ISRHandler handler;
        int gpio;
    };
    using ISRConfigPtr = ISRConfig *;
    using ISRConfigSharedPtr = std::shared_ptr<ISRConfig>;

    /**
     * @brief Enumeration for the trigger types of an ISR.
     *
     * This enumeration defines the different types of triggers that can be used
     * for an interrupt service routine (ISR).
     */
    enum class ISRTrigger : int
    {
        RISING,
        FALLING,
        BOTH,
        LOW,
        HIGH
    };

    /**
     * @brief Base class for input GPIO operations.
     *
     * This class provides an interface for input GPIO operations, including
     * reading levels, setting pull-up/pull-down resistors, and handling
     * interrupts.
     */
    class InputGPIO : public GPIO
    {
    protected:
        bool _inverse_level = false;
        virtual bool _get_level() const = 0;

    public:
        /**
         * @brief Default constructor for InputGPIO.
         *
         * This constructor initializes the InputGPIO object with default
         * settings.
         */
        virtual bool get_level() const;

        /**
         * @brief Sets the level inversion for the GPIO pin.
         *
         * This method allows the user to set whether the GPIO pin's level is
         * inverted. If set to true, a logical high will be interpreted as low,
         * and vice versa.
         *
         * @param level A boolean value indicating whether to invert the level.
         *              Default is false, meaning no inversion.
         */
        virtual void set_inverse_level(bool level = false);

        /**
         * @brief Gets the current level inversion setting.
         *
         * This method returns the current setting for level inversion. If
         * inversion is enabled, it will return true; otherwise, it will return
         * false.
         *
         * @return A boolean indicating whether the level is inverted.
         */
        virtual bool get_inverse_level() const;

        /**
         * @brief Enable pull up resistor for the GPIO pin.
         */
        virtual void enable_pullup() = 0;

        /**
         * @brief Enable pull down resistor for the GPIO pin.
         */
        virtual void enable_pulldown() = 0;

        /**
         * @brief Disable pull up resistor for the GPIO pin.
         */
        virtual void disable_pullup() = 0;

        /**
         * @brief Disable pull down resistor for the GPIO pin.
         */
        virtual void disable_pulldown() = 0;

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
        virtual void add_interrupt_handler(ISRHandler, ISRTrigger) = 0;
    };
    using InputGPIOPtr = InputGPIO *;
    using InputGPIOSharedPtr = std::shared_ptr<InputGPIO>;
}; // namespace sabre

#endif // SABRE_INPUT_GPIO_H