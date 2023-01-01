cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(epink_desktop)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# add include and src files
file(GLOB_RECURSE INCLUDES "include/*.h"
                            "port/*.h"
                            "ui/*.h"
                            "display/*.h"
                            "sensors/*.h"
                            "i2c/*.h"
                            "net/*.h"
                            "clk/*.h"
                            "spi/*.h"
                            "rtc/*.h")

file(GLOB_RECURSE SOURCES "lvgl/src/*.c"
                            "font/*.c"
                            "port/*.c"
                            "ui/*.c"
                            "display/*.c"
                            "sensors/*.c"
                            "i2c/*.c"
                            "net/*.c"
                            "clk/*.c"
                            "spi/*.c"
                            "rtc/*.c")

# rest of your project
add_executable(epink_desktop main.c ${INCLUDES} ${SOURCES})

target_include_directories(epink_desktop PUBLIC . "lvgl")
target_link_libraries(epink_desktop pico_stdlib
                            hardware_clocks
                            hardware_spi
                            hardware_rtc
                            hardware_i2c
                            hardware_uart)

pico_enable_stdio_usb(epink_desktop 0)
pico_enable_stdio_uart(epink_desktop 1)

pico_add_extra_outputs(epink_desktop)

# build the index html page first
add_custom_target(
    build_index ALL
    COMMAND ${PYTHON_EXECUTABLE}
        ${CMAKE_CURRENT_SOURCE_DIR}/net/html2doth.py
        ${CMAKE_CURRENT_SOURCE_DIR}/net/index.html
        ${CMAKE_CURRENT_SOURCE_DIR}/net/index.h

    BYPRODUCTS ${CMAKE_CURRENT_SOURCE_DIR}/net/index.h
    COMMENT "Generating index.h"
)
add_dependencies(epink_desktop build_index)
