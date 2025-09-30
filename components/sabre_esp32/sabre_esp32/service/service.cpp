#include "service.hpp"

namespace sabre::esp32
{
    void Service::_runner(void *obj)
    {
        auto *_obj = static_cast<Service *>(obj);
        _obj->_fn();
    }

    Service::Service(sabre::ServiceHandler function)
        : sabre::Service(function), _freertos_handle(nullptr)
    {
    }

    Service::~Service()
    {
        stop();
    }

    void Service::start()
    {
        xTaskCreate(&Service::_runner, "ServiceTask", 2048, this, 5,
                    &_freertos_handle);
    }

    void Service::stop()
    {
        if (_freertos_handle)
        {
            TaskHandle_t handle = _freertos_handle;
            _freertos_handle = nullptr;
            vTaskDelete(handle);
        }
    }
} // namespace sabre::esp32