#include "service.hpp"

namespace sabre
{
    Service::Service(ServiceHandler fn) : _fn(fn) {}
} // namespace sabre