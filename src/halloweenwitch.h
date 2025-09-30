#ifndef _HALLOWEENWITCH_H_
#define _HALLOWEENWITCH_H_

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <sabre/factory.hpp>
#include <sabre/gpio/input_gpio.hpp>
#include <sabre/service/service.hpp>
#include <string>

class HalloweenWitch
{
public:
    HalloweenWitch(sabre::FactorySharedPtr factory,
                   sabre::InputGPIOSharedPtr button,
                   sabre::OutputGPIOSharedPtr witch);
    void start();

private:
    void _init_button();
    void _init_esp_now();
    void _isr_button(int);
    void _service_activate_witch();
    void _activate_witch();

    sabre::InputGPIOSharedPtr _button;
    sabre::OutputGPIOSharedPtr _witch;
    sabre::FactorySharedPtr _factory;
    sabre::ServiceSharedPtr _service;
    QueueHandle_t _queue;
    int64_t _last_press_time;
};

#endif // _HALLOWEENWITCH_H_