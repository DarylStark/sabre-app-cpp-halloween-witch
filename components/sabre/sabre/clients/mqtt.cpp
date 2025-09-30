#include "mqtt.hpp"

namespace sabre
{
    MQTTTopic::MQTTTopic(MQTTClient &client, const std::string &topic)
        : _client(client), _topic(topic)
    {
    }

    void MQTTTopic::publish(const std::string &message, MQTTQoS qos,
                            MQTTRetain retain)
    {
        if (qos == MQTTQoS::UNDEFINED)
            qos = _default_qos;
        if (retain == MQTTRetain::UNDEFINED)
            retain = _default_retain;

        _client.publish(_topic, message, qos, retain);
    }

    void MQTTTopic::subscribe(MQTTCallback fn, MQTTQoS qos)
    {
        _client.subscribe(_topic, fn, qos);
    }

    void MQTTTopic::set_default_qos(MQTTQoS qos)
    {
        if (qos == MQTTQoS::UNDEFINED)
            return;
        _default_qos = qos;
    }

    void MQTTTopic::set_default_retain(MQTTRetain retain)
    {
        if (retain == MQTTRetain::UNDEFINED)
            return;
        _default_retain = retain;
    }

    void MQTTClient::subscribe(const std::string &topic, MQTTCallback fn,
                               MQTTQoS qos)
    {
        if (qos == MQTTQoS::UNDEFINED)
            qos = MQTTQoS::EXACTLY_ONCE;

        _subscriptions[topic] = fn;
    }

    MQTTTopicUniquePtr MQTTClient::get_topic(const std::string &topic_name)
    {
        return std::make_unique<MQTTTopic>(*this, topic_name);
    }

    void MQTTClient::process_received(MQTTEvent event)
    {
        if (_subscriptions.find(event.topic) != _subscriptions.end())
            _subscriptions[event.topic](event);
        else if (_default_handler != nullptr)
            _default_handler(event);
    }

    void MQTTClient::set_default_handler(MQTTCallback handler)
    {
        _default_handler = handler;
    }

} // namespace sabre