#include "ntp.hpp"

#include <esp_sntp.h>

namespace sabre::esp32
{
    NTPClient::NTPClient(const std::string &server) : _server(server) {}

    void NTPClient::start()
    {
        esp_sntp_setservername(0, _server.c_str());
        esp_sntp_init();
    }

    void NTPClient::stop()
    {
        esp_sntp_stop();
    }

    bool NTPClient::is_synchronized() const
    {
        return esp_sntp_get_sync_status() == SNTP_SYNC_STATUS_COMPLETED;
    }
} // namespace sabre::esp32