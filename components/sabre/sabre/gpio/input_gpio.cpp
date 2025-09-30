#include "input_gpio.hpp"

namespace sabre
{
    bool InputGPIO::get_level() const
    {
        return _get_level() == !_inverse_level;
    }

    void InputGPIO::set_inverse_level(bool level)
    {
        _inverse_level = level;
    }

    bool InputGPIO::get_inverse_level() const
    {
        return _inverse_level;
    }
} // namespace sabre