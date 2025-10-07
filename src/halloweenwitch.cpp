#include "halloweenwitch.h"
#include "esp_timer.h"
#include <cstring>
#include <esp_now.h>
#include <esp_timer.h>
#include <esp_wifi.h>
#include <freertos/FreeRTOS.h>
#include <functional>
#include <iostream>
#include <nvs_flash.h>
#include <sabre/factory.hpp>
#include <sabre_esp32/service/service.hpp>

namespace
{
    QueueHandle_t global_queue;
    void espnow_recv_cb(const esp_now_recv_info_t *recv_info,
                        const uint8_t *data, int len)
    {
        int value = 1;
        std::cout << "Received ESP-NOW message of length " << len << std::endl;
        xQueueSend(global_queue, &value, portMAX_DELAY);
    }
} // namespace

HalloweenWitch::HalloweenWitch(sabre::FactorySharedPtr factory,
                               sabre::InputGPIOSharedPtr button,
                               sabre::OutputGPIOSharedPtr witch)
    : _button(button), _witch(witch), _factory(factory), _last_press_time(0)
{
    _queue = xQueueCreate(10, sizeof(int));
    global_queue = _queue;
    _service = std::make_shared<sabre::esp32::Service>(
        std::bind(&HalloweenWitch::_service_activate_witch, this));
}

void HalloweenWitch::start()
{
    _init_button();
    _init_esp_now();
    _last_press_time = esp_timer_get_time();
    _service->start();
}

void HalloweenWitch::_init_button()
{
    _button->add_interrupt_handler(
        std::bind(&HalloweenWitch::_isr_button, this, std::placeholders::_1),
        sabre::ISRTrigger::FALLING);
}

void HalloweenWitch::_init_esp_now()
{
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
        ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Initialize WiFi in STA mode
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE));

    // Initialize ESP-NOW after Wi-Fi is started
    ESP_ERROR_CHECK(esp_now_init());

    // Add handler
    ESP_ERROR_CHECK(esp_now_register_recv_cb(espnow_recv_cb));
}

void HalloweenWitch::_isr_button(int)
{
    int value = 1;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xQueueSendFromISR(_queue, &value, &xHigherPriorityTaskWoken);
}

void HalloweenWitch::_activate_witch()
{
    int64_t current_time = esp_timer_get_time();
    if (current_time - _last_press_time < 4000000)
    {
        std::cout << "Skipping: " << _button->get_level() << std::endl;
        return;
    }
    std::cout << "Activated!" << std::endl;

    _witch->set_level(true);
    vTaskDelay(pdMS_TO_TICKS(500)); // 100 ms
    _witch->set_level(false);

    _last_press_time = esp_timer_get_time();
}

void HalloweenWitch::_service_activate_witch()
{
    int msg;
    while (true)
        if (xQueueReceive(_queue, &msg, portMAX_DELAY) == pdTRUE)
            _activate_witch();
}