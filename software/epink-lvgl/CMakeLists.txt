cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(xenia_clock)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# add include and src files
file(GLOB_RECURSE INCLUDES "include/*.h"
                            "port/*.h"
                            "ui/*.h"
                            "net/*.h"
                            "drivers/video/*.h"
                            "drivers/sensors/*.h"
                            "drivers/i2c/*.h"
                            "drivers/clk/*.h"
                            "drivers/spi/*.h"
                            "drivers/power/*.h"
                            "drivers/input/*.h"
                            "drivers/rtc/*.h")

file(GLOB_RECURSE SOURCES "lvgl/src/*.c"
                            "font/*.c"
                            "port/*.c"
                            "ui/*.c"
                            "net/*.c"
                            "misc/*.c"
                            "fs/*.c"
                            "drivers/gpio/*.c"
                            "drivers/video/*.c"
                            "drivers/sensors/*.c"
                            "drivers/i2c/*.c"
                            "drivers/clk/*.c"
                            "drivers/spi/*.c"
                            "drivers/uart/*.c"
                            "drivers/power/*.c"
                            "drivers/input/*.c"
                            "drivers/leds/*.c"
                            "drivers/iio/*.c"
                            "drivers/mtd/spi-nor/*.c"
                            "drivers/rtc/*.c")

set(FREERTOS_KERNEL_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/kernel)
set(PICO_SDK_FREERTOS_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/kernel)
add_subdirectory(kernel)

add_subdirectory(lib)

# rest of your project
add_executable(xenia_clock init/crt1.S init/main.c ${INCLUDES} ${SOURCES})

set(LINK_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/memmap_default.ld")

## Note: uncomment this flag to avoid WARNING: LOAD segment with RWX permissions
## because it's a feature since binutils 2.39 and we don't need it.
# target_link_options(xenia_clock PRIVATE -Wl,--no-warn-rwx-segments)
pico_set_linker_script(xenia_clock ${LINK_SCRIPT})

target_include_directories(xenia_clock PUBLIC . "include" "lvgl")
target_link_libraries(xenia_clock freertos-kernel
                            common_lib
                            pico_stdlib
                            pico_bootsel_via_double_reset
                            hardware_clocks
                            hardware_spi
                            hardware_dma
                            hardware_rtc
                            hardware_i2c
                            hardware_pwm
                            hardware_uart)

pico_enable_stdio_usb(xenia_clock 1)
pico_enable_stdio_uart(xenia_clock 1)

pico_add_extra_outputs(xenia_clock)

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

add_dependencies(xenia_clock build_index)
