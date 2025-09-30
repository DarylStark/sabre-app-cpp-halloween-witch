#include "mqtt.hpp"

#include <string>

void _esp32_mqtt_event_handler(void *handler_args, esp_event_base_t base,
                               int32_t event_id, void *event_data)
{
    using sabre::esp32::MQTTClient;
    MQTTClient *obj = static_cast<MQTTClient *>(handler_args);
    obj->handle_event(base, event_id, event_data);
}

namespace sabre::esp32
{
    MQTTClient::~MQTTClient()
    {
        stop();
    }

    void MQTTClient::connect(const std::string &hostname,
                             const std::string &client_id,
                             const std::string &username,
                             const std::string &password)
    {
        std::string uri = "mqtt://" + hostname;

        esp_mqtt_client_config_t mqtt_cfg = {};
        mqtt_cfg.broker.address.uri = uri.c_str();
        mqtt_cfg.credentials.authentication.password = password.c_str();
        mqtt_cfg.credentials.username = username.c_str();
        mqtt_cfg.credentials.client_id = client_id.c_str();
        mqtt_cfg.network.disable_auto_reconnect = true;

        _client = esp_mqtt_client_init(&mqtt_cfg);

        esp_mqtt_client_register_event(_client, MQTT_EVENT_ANY,
                                       _esp32_mqtt_event_handler, this);
        esp_mqtt_client_start(_client);
    }

    void MQTTClient::disconnect()
    {
        if (_client)
            esp_mqtt_client_disconnect(_client);
    }

    void MQTTClient::stop()
    {
        if (_client)
        {
            disconnect();
            esp_mqtt_client_stop(_client);
            esp_mqtt_client_destroy(_client);
            _client = nullptr;
        }
    }

    void MQTTClient::publish(const std::string &topic,
                             const std::string &message, sabre::MQTTQoS qos,
                             sabre::MQTTRetain retain)
    {
        if (qos == sabre::MQTTQoS::UNDEFINED)
            qos = sabre::MQTTQoS::FIRE_AND_FORGET;
        if (retain == sabre::MQTTRetain::UNDEFINED)
            retain = sabre::MQTTRetain::DONT_RETAIN;
        esp_mqtt_client_publish(_client, topic.c_str(), message.c_str(), 0,
                                static_cast<int>(qos),
                                static_cast<int>(retain));
    }

    void MQTTClient::subscribe(const std::string &topic, sabre::MQTTCallback fn,
                               sabre::MQTTQoS qos)
    {
        if (qos == sabre::MQTTQoS::UNDEFINED)
            qos = sabre::MQTTQoS::EXACTLY_ONCE;

        esp_mqtt_client_subscribe(_client, topic.c_str(),
                                  static_cast<int>(qos));

        sabre::MQTTClient::subscribe(topic, fn, qos);
    }

    bool MQTTClient::is_connected() const
    {
        return _connected;
    }

    sabre::MQTTEvent
    MQTTClient::_create_event(esp_mqtt_event_handle_t event_data) const
    {
        std::string topic(event_data->topic, event_data->topic_len);
        std::string data(event_data->data, event_data->data_len);

        return sabre::MQTTEvent(
            {std::string(event_data->topic, event_data->topic_len),
             std::string(event_data->data, event_data->data_len),
             static_cast<sabre::MQTTQoS>(event_data->qos),
             static_cast<sabre::MQTTRetain>(event_data->retain)});
    }

    void MQTTClient::handle_event(esp_event_base_t event_base, int32_t event_id,
                                  void *event_data)
    {
        esp_mqtt_event_handle_t event =
            static_cast<esp_mqtt_event_handle_t>(event_data);

        switch (event_id)
        {
        case MQTT_EVENT_CONNECTED:
            _connected = true;
            break;
        case MQTT_EVENT_DISCONNECTED:
            _connected = false;
            break;
        case MQTT_EVENT_DATA:
            this->process_received(_create_event(event));
            break;
        default:
            break;
        }
    }
} // namespace sabre::esp32