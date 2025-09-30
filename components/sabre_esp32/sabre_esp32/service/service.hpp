#ifndef SABRE_ESP32_SERVICE_H
#define SABRE_ESP32_SERVICE_H

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <functional>
#include <sabre/service/service.hpp>

namespace sabre::esp32
{
    /**
     * @brief Class for a service that runs on FreeRTOS.
     *
     * This class implements the service functionality using FreeRTOS tasks. It
     * provides methods to start and stop the service, and runs the service
     * logic in a separate task.
     */
    class Service : public sabre::Service
    {
    private:
        TaskHandle_t _freertos_handle = nullptr;
        static void _runner(void *b);

    public:
        /**
         * @brief Constructor for the Service class.
         *
         * This constructor initializes the service with a handler function that
         * will be called when the service is started.
         *
         * @param function The function to be called when the service starts.
         */
        Service(ServiceHandler function);

        /**
         * @brief Destructor for the Service class.
         *
         * This destructor stops the service and cleans up any resources used by
         * the service.
         */
        ~Service();

        /**
         * @brief Starts the service by creating a FreeRTOS task.
         *
         * This method creates a FreeRTOS task that runs the service logic in a
         * separate thread.
         */
        void start() override;

        /**
         * @brief Stops the service by deleting the FreeRTOS task.
         *
         * This method stops the service by deleting the FreeRTOS task that was
         * created when the service was started.
         */
        void stop() override;
    };
} // namespace sabre::esp32

#endif // SABRE_ESP32_SERVICE_H