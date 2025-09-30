#ifndef SABRE_GPIO_H
#define SABRE_GPIO_H

#include <memory>

namespace sabre
{
    /**
     * @brief Base class for GPIO operations.
     *
     * This class provides a base interface for GPIO operations. It can be
     * extended to implement specific GPIO functionalities.
     */
    class GPIO
    {
    protected:
        bool _inverse_level = false;

    public:
        /**
         * @brief Default constructor for GPIO.
         *
         * This constructor initializes the GPIO object with default settings.
         */
        virtual void reset() = 0;
    };
    using GPIOOPtr = GPIO *;
    using GPIOOSharedPtr = std::shared_ptr<GPIO>;
}; // namespace sabre

#endif // SABRE_GPIO_H