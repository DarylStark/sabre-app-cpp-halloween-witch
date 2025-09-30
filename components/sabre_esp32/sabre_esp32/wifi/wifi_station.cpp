#include "wifi_station.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <esp_event.h>
#include <esp_log.h>
#include <esp_netif.h>
#include <lwip/inet.h>
#include <nvs_flash.h>
#include <sabre/generic/ipv4_address.hpp>
#include <sstream>

#define WIFI_MAX_RETRY 5

extern "C"
{
    void _wifi_event_handler(void *arg, esp_event_base_t event_base,
                             int32_t event_id, void *event_data)
    {
        using sabre::esp32::WifiStation;
        WifiStation *obj = static_cast<WifiStation *>(arg);
        obj->wifi_event_handler(event_base, event_id, event_data);
    }

    void _ip_event_handler(void *arg, esp_event_base_t event_base,
                           int32_t event_id, void *event_data)
    {
        using sabre::esp32::WifiStation;
        WifiStation *obj = static_cast<WifiStation *>(arg);
        obj->ip_event_handler(event_base, event_id, event_data);
    }
}

namespace sabre::esp32
{
    WifiStation::WifiStation()
        : _wifi_instance(Wifi::get_instance()), _logger("WifiStation")
    {
    }

    WifiStation::~WifiStation()
    {
        deinitialize();
    }

    void WifiStation::wifi_event_handler(esp_event_base_t event_base,
                                         int32_t event_id, void *event_data)
    {
        if (event_id == WIFI_EVENT_STA_CONNECTED)
        {
            _logger.debug("Connected");
            _connected = true;
        }
        else if (event_id == WIFI_EVENT_STA_DISCONNECTED)
        {
            _logger.debug("Disconnected!");
            _connected = false;
        }
    }

    void WifiStation::ip_event_handler(esp_event_base_t event_base,
                                       int32_t event_id, void *event_data)
    {
        if (event_id == IP_EVENT_STA_GOT_IP)
        {
            ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;

            _ipv4_address.set(ntohl(event->ip_info.ip.addr));
            _ipv4_mask.set(ntohl(event->ip_info.netmask.addr));
            _ipv4_gateway.set(ntohl(event->ip_info.gw.addr));

            _logger.debug("Got IPv4 address");
            std::stringstream log;
            log << "IP address: " << std::string(_ipv4_address) << ", "
                << "mask: " << std::string(_ipv4_mask) << ", "
                << "gateway: " << std::string(_ipv4_gateway);
            _logger.info(log.str());
        }
        else if (event_id == IP_EVENT_STA_LOST_IP)
        {
            _ipv4_address.set(0);
            _ipv4_mask.set(0);
            _ipv4_gateway.set(0);
            _logger.info("Lost IP address");
        }
    }

    void WifiStation::init()
    {
        if (_initialized)
            return;

        _wifi_instance->init();

        esp_netif_create_default_wifi_sta();
        esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID,
                                   &_wifi_event_handler, this);
        esp_event_handler_register(IP_EVENT, IP_EVENT_ETH_GOT_IP,
                                   &_ip_event_handler, this);
        esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP,
                                   &_ip_event_handler, this);
        _initialized = true;
    }

    void WifiStation::connect(const std::string &ssid,
                              const std::string &password)
    {
        if (!_initialized)
            init();

        std::memset(&_wifi_config, 0, sizeof(_wifi_config));
        std::strcpy((char *)_wifi_config.sta.ssid, ssid.c_str());
        std::strcpy((char *)_wifi_config.sta.password, password.c_str());

        _wifi_instance->add_mode(WifiMode::STATION);
        esp_wifi_set_config(WIFI_IF_STA, &_wifi_config);

        _wifi_instance->start();

        esp_wifi_connect();
    }

    void WifiStation::disconnect()
    {
        esp_wifi_disconnect();
        _connected = false;
    }

    void WifiStation::stop()
    {
        _wifi_instance->remove_mode(WifiMode::STATION);
    }

    void WifiStation::deinitialize()
    {
        stop();
        _wifi_instance->deinitialize();
        esp_event_handler_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID,
                                     &_wifi_event_handler);
        esp_event_handler_unregister(IP_EVENT, ESP_EVENT_ANY_ID,
                                     &_ip_event_handler);
    }

    bool WifiStation::is_connected() const
    {
        return this->_connected;
    }

    bool WifiStation::has_ipv4_address() const
    {
        return _ipv4_address != IPv4Address(0);
    }
} // namespace sabre::esp32