#include "output_gpio.hpp"
#include "../exceptions/exceptions.hpp"
#include <driver/gpio.h>

namespace sabre::esp32
{
    OutputGPIO::OutputGPIO(int32_t pin_number)
        : _pin_number(pin_number),
          _gpio_num(static_cast<gpio_num_t>(pin_number))
    {
        throw_if_esp_err(gpio_set_direction(_gpio_num, GPIO_MODE_OUTPUT),
                         "Failed to set GPIO direction");
    }

    OutputGPIO::~OutputGPIO()
    {
        reset();
    }

    void OutputGPIO::reset()
    {
        throw_if_esp_err(gpio_reset_pin(_gpio_num), "Failed to reset GPIO");
    }

    void OutputGPIO::set_high()
    {
        throw_if_esp_err(gpio_set_level(_gpio_num, 1),
                         "Failed to set GPIO high");
    }

    void OutputGPIO::set_low()
    {
        throw_if_esp_err(gpio_set_level(_gpio_num, 0),
                         "Failed to set GPIO low");
    }

    void OutputGPIO::set_level(bool level)
    {
        throw_if_esp_err(gpio_set_level(_gpio_num, level ? 1 : 0),
                         "Failed to set GPIO level");
    }
} // namespace sabre::esp32