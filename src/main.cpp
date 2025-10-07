#include "halloweenwitch.h"
#include <iostream>

#include <sabre_esp32/factory.hpp>

HalloweenWitch *app;

extern "C"
{
    void app_main(void)
    {

        // Configure button
        sabre::FactorySharedPtr factory =
            std::make_shared<sabre::esp32::Factory>();

        sabre::InputGPIOSharedPtr button = factory->create_input_gpio(20);
        button->enable_pullup();
        button->set_inverse_level(true);

        sabre::OutputGPIOSharedPtr witch =
            factory->create_output_gpio(8); // Should be 8 in the final version

        // Create the application
        app = new HalloweenWitch(factory, button, witch);

        // Start the application
        app->start();

        // Done!
        return;
    }
}