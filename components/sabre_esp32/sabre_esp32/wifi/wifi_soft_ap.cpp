#include "wifi_soft_ap.hpp"
#include <cstring>
#include <nvs_flash.h>

extern "C"
{
    void _wifi_event_handler_two(void *arg, esp_event_base_t event_base,
                                 int32_t event_id, void *event_data)
    {
        using sabre::esp32::WifiSoftAP;
        WifiSoftAP *obj = static_cast<WifiSoftAP *>(arg);
        obj->wifi_event_handler(event_base, event_id, event_data);
    }
}

namespace sabre::esp32
{
    WifiSoftAP::WifiSoftAP()
        : _wifi_instance(Wifi::get_instance()), _logger("WifiSoftAP")
    {
    }

    WifiSoftAP::~WifiSoftAP()
    {
        deinitialize();
    }

    void WifiSoftAP::wifi_event_handler(esp_event_base_t event_base,
                                        int32_t event_id, void *event_data)
    {
        if (event_id == WIFI_EVENT_AP_STACONNECTED)
            _logger.info("Client connected");
        else if (event_id == WIFI_EVENT_AP_STADISCONNECTED)
            _logger.info("Client disconnected");
    }

    void WifiSoftAP::init()
    {
        if (_initialized)
            return;

        _wifi_instance->init();

        esp_netif_create_default_wifi_ap();
        esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID,
                                   &_wifi_event_handler_two, this);
        _initialized = true;
    }

    void WifiSoftAP::start(std::string ssid, std::string password)
    {
        std::strcpy((char *)_wifi_config.ap.ssid, ssid.c_str());
        std::strcpy((char *)_wifi_config.ap.password, password.c_str());
        _wifi_config.ap.channel = 1;
        _wifi_config.ap.max_connection = 4;
        _wifi_config.ap.authmode = WIFI_AUTH_WPA2_PSK;

        _wifi_instance->add_mode(WifiMode::SOFT_AP);
        esp_wifi_set_config(WIFI_IF_AP, &_wifi_config);
        _wifi_instance->start();
    }

    void WifiSoftAP::stop()
    {
        _wifi_instance->remove_mode(WifiMode::SOFT_AP);
    }

    void WifiSoftAP::deinitialize()
    {
        stop();
        _wifi_instance->deinitialize();
        esp_event_handler_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID,
                                     &_wifi_event_handler_two);
    }
} // namespace sabre::esp32