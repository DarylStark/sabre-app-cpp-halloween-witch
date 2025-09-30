file(GLOB SOURCES sabre/**/*.cpp sabre/*.cpp)

idf_component_register(
    SRCS
        ${SOURCES}
    INCLUDE_DIRS
        "."
)
