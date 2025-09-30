#include "ipv4_address.hpp"
#include <ostream>

namespace sabre
{
    IPv4Address::IPv4Address() : _address(0) {}

    IPv4Address::IPv4Address(uint32_t address) : _address(address) {}

    void IPv4Address::set(uint32_t address)
    {
        _address = address;
    }

    uint16_t IPv4Address::operator[](uint8_t octet) const
    {
        return _address >> ((3 - octet) * 8) & 0xff;
    }

    IPv4Address::operator uint32_t() const
    {
        return _address;
    }

    IPv4Address::operator std::string() const
    {
        std::string result;
        for (int i = 0; i < 4; ++i)
        {
            if (i > 0)
                result += '.';
            result += std::to_string((*this)[i]);
        }
        return result;
    }

    std::ostream &operator<<(std::ostream &os, const sabre::IPv4Address &ipv4)
    {
        os << static_cast<std::string>(ipv4);
        return os;
    }
} // namespace sabre
