# Copyright (c) 2023 developer
# 
# This software is released under the MIT License.
# https://opensource.org/licenses/MIT

add_library(freertos-kernel-core INTERFACE)
target_sources(freertos-kernel-core INTERFACE
        ${PICO_SDK_FREERTOS_SOURCE}/event_groups.c
        ${PICO_SDK_FREERTOS_SOURCE}/list.c
        ${PICO_SDK_FREERTOS_SOURCE}/queue.c
        ${PICO_SDK_FREERTOS_SOURCE}/stream_buffer.c
        ${PICO_SDK_FREERTOS_SOURCE}/tasks.c
        ${PICO_SDK_FREERTOS_SOURCE}/timers.c
        )

add_library(freertos-kernel INTERFACE)
target_sources(freertos-kernel INTERFACE
    ${PICO_SDK_FREERTOS_SOURCE}/portable/ThirdParty/GCC/RP2040/port.c
)

target_include_directories(freertos-kernel INTERFACE
        ${PICO_SDK_FREERTOS_SOURCE}/
        ${PICO_SDK_FREERTOS_SOURCE}/include
        ${PICO_SDK_FREERTOS_SOURCE}/portable/ThirdParty/GCC/RP2040/include
)

add_library(freertos-kernel-heap3 INTERFACE)
target_sources(freertos-kernel-heap3 INTERFACE ${PICO_SDK_FREERTOS_SOURCE}/portable/MemMang/heap_3.c)

target_link_libraries(freertos-kernel INTERFACE
        freertos-kernel-core
        freertos-kernel-heap3
        pico_base_headers
        hardware_exception
)
