file(GLOB SOURCES sabre_esp32/**/*.cpp sabre_esp32/*.cpp)

idf_component_register(
    SRCS
        ${SOURCES}
    INCLUDE_DIRS
        "." 
    PRIV_REQUIRES
        sabre
    REQUIRES
        esp_driver_uart
        esp_driver_gpio
        esp_wifi
        nvs_flash
        esp_timer
        mqtt
)
