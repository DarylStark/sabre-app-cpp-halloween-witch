#ifndef SABRE_ESP32_CLIENTS_MQTT_H
#define SABRE_ESP32_CLIENTS_MQTT_H

#include <mqtt_client.h>
#include <sabre/clients/mqtt.hpp>
#include <string>

namespace sabre::esp32
{
    /**
     * @brief Class for a MQTT client
     *
     * This class implements the MQTT client using the ESP-IDF MQTT client
     * library. It provides methods to connect, disconnect, publish messages,
     * and subscribe to topics. It also handles incoming MQTT events and
     * processes received messages.
     */
    class MQTTClient : public sabre::MQTTClient
    {
    private:
        bool _connected = false;
        esp_mqtt_client_handle_t _client = nullptr;

        void _run_subscription(esp_mqtt_event_handle_t event_data);
        sabre::MQTTEvent
        _create_event(esp_mqtt_event_handle_t event_data) const;

    public:
        /**
         * @brief Destructs the MQTTClient object.
         *
         * This will close the connection to the MQTT broker if it is still
         * open, and clean up any resources used by the client.
         */
        ~MQTTClient();

        /**
         * @brief Connect to a specific MQTT broker.
         *
         * @param hostname the hostname for the MQTT broker.
         * @param client_id the client_id for the connection.
         * @param username the username for the connection.
         * @param password the password for the connection.
         */
        void connect(const std::string &hostname, const std::string &client_id,
                     const std::string &username,
                     const std::string &password) override;

        /**
         * @brief Disconnect the client.
         */
        void disconnect() override;

        /**
         * @brief Stop the client.
         */
        void stop() override;

        /**
         * @brief Check if the client is connected.
         *
         * @return `true` if the client is connected, `false` otherwise.
         */
        bool is_connected() const override;

        /**
         * @brief Publish a message to a specific topic.
         *
         * @param topic the topic to publish the message to.
         * @param message the message to publish.
         * @param qos the Quality of Service level to use.
         * @param retain whether to retain the message.
         */
        void publish(const std::string &topic, const std::string &message,
                     sabre::MQTTQoS qos, sabre::MQTTRetain retain) override;

        /**
         * @brief Subscribe to a specific topic.
         *
         * @param topic the topic to subscribe to.
         * @param fn the callback function to call when a message is received.
         * @param qos the Quality of Service level to use.
         */
        void subscribe(const std::string &topic, sabre::MQTTCallback fn,
                       sabre::MQTTQoS qos = sabre::MQTTQoS::UNDEFINED) override;

        /**
         * @brief Handle incoming MQTT events.
         *
         * @param event_base the event base.
         * @param event_id the event ID.
         * @param event_data the event data.
         */
        void handle_event(esp_event_base_t event_base, int32_t event_id,
                          void *event_data);
    };
} // namespace sabre::esp32

#endif // SABRE_ESP32_CLIENTS_MQTT_H