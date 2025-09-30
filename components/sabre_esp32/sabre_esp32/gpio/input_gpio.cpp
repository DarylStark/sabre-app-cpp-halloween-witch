#include "input_gpio.hpp"
#include "../exceptions/exceptions.hpp"
#include <driver/gpio.h>

namespace sabre::esp32
{
    std::unordered_map<sabre::ISRTrigger, gpio_int_type_t>
        InputGPIO::_trigger_map = {
            {sabre::ISRTrigger::RISING, GPIO_INTR_POSEDGE},
            {sabre::ISRTrigger::FALLING, GPIO_INTR_NEGEDGE},
            {sabre::ISRTrigger::BOTH, GPIO_INTR_ANYEDGE},
            {sabre::ISRTrigger::LOW, GPIO_INTR_LOW_LEVEL},
            {sabre::ISRTrigger::HIGH, GPIO_INTR_HIGH_LEVEL}};
    bool InputGPIO::_isr_service_installed = false;

    InputGPIO::InputGPIO(int32_t pin_number)
        : _pin_number(pin_number),
          _gpio_num(static_cast<gpio_num_t>(pin_number))
    {
        throw_if_esp_err(gpio_set_direction(_gpio_num, GPIO_MODE_INPUT),
                         "Failed to set GPIO direction");
    }

    InputGPIO::~InputGPIO()
    {
        reset();
    }

    void InputGPIO::reset()
    {
        throw_if_esp_err(gpio_reset_pin(_gpio_num), "Failed to reset GPIO");
    }

    bool InputGPIO::_get_level() const
    {
        return gpio_get_level(_gpio_num) == 1;
    }

    void InputGPIO::enable_pullup()
    {
        throw_if_esp_err(gpio_pullup_en(_gpio_num), "Failed to enable pull-up");
    }

    void InputGPIO::enable_pulldown()
    {
        throw_if_esp_err(gpio_pulldown_en(_gpio_num),
                         "Failed to enable pull-down");
    }

    void InputGPIO::disable_pullup()
    {
        throw_if_esp_err(gpio_pullup_dis(_gpio_num),
                         "Failed to disable pull-up");
    }

    void InputGPIO::disable_pulldown()
    {
        throw_if_esp_err(gpio_pulldown_dis(_gpio_num),
                         "Failed to disable pull-down");
    }

    void InputGPIO::add_interrupt_handler(sabre::ISRHandler handler,
                                          sabre::ISRTrigger trigger)
    {
        _config = std::make_shared<sabre::ISRConfig>();
        _config->handler = handler;
        _config->gpio = static_cast<int32_t>(_gpio_num);

        if (!_isr_service_installed)
        {
            throw_if_esp_err(gpio_install_isr_service(0),
                             "Failed to install ISR service");
            _isr_service_installed = true;
        }

        throw_if_esp_err(
            gpio_set_intr_type(_gpio_num, _trigger_map.at(trigger)),
            "Failed to set GPIO interrupt type");

        throw_if_esp_err(gpio_isr_handler_add(
                             _gpio_num,
                             [](void *config)
                             {
                                 auto cfg =
                                     static_cast<sabre::ISRConfig *>(config);
                                 auto func = cfg->handler;
                                 func(cfg->gpio);
                             },
                             static_cast<void *>(_config.get())),
                         "Failed to add GPIO ISR handler");
    }
} // namespace sabre::esp32