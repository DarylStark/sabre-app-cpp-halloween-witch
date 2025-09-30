#ifndef SABRE_IPV4_ADDRESS_H
#define SABRE_IPV4_ADDRESS_H

#include <cstdint>
#include <memory>
#include <string>

namespace sabre
{
    /**
     * @brief Class that represents an IPv4 address.
     *
     * This class can be used to represent an IPv4 address in a more
     * convenient way than using a simple `uint32_t`.
     */
    class IPv4Address
    {
        uint32_t _address;

    public:
        /**
         * @brief Default constructor; initializes the address to 0.
         */
        IPv4Address();

        /**
         * @brief Constructor that initializes the address with a specific
         * value.
         *
         * @param address The IPv4 address as a uint32_t.
         */
        IPv4Address(uint32_t address);

        /**
         * @brief Sets the IPv4 address to a specific value.
         *
         * @param address The IPv4 address as a uint32_t.
         */
        void set(uint32_t address);

        /**
         * @brief Gets the octet at the specified index.
         *
         * @param octet The index of the octet (0-3).
         * @return The value of the octet as a uint16_t.
         */
        uint16_t operator[](uint8_t octet) const;

        /**
         * @brief Converts the IPv4 address to a uint32_t.
         *
         * @return The IPv4 address as a uint32_t.
         */
        operator uint32_t() const;

        /**
         * @brief Converts the IPv4 address to a string.
         *
         * @return The IPv4 address as a string (e.g., "192.168.1.1").
         */
        operator std::string() const;
    };
    using IPv4AddressPtr = IPv4Address *;
    using IPv4AddressSharedPtr = std::shared_ptr<IPv4Address>;

    std::ostream &operator<<(std::ostream &os, const sabre::IPv4Address &ipv4);
}; // namespace sabre

#endif // SABRE_IPV4_ADDRESS_H