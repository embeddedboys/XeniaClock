<!--
 Copyright (c) 2023 IotaHydrae(writeforever@foxmail.com)
 
 This software is released under the MIT License.
 https://opensource.org/licenses/MIT
-->

<h1 align="center">
    <span>FreeRTOS for Rp2040<span>
</h1>

Table of Contents
-------------------------------------------------
- [Porting](#porting)
- [How to Use this kernel in your project?](#how-to-use-this-kernel-in-your-project)
- [More](#more)

Porting
-------------------------------------------------
Using mainline `Third party GCC RP2040` port

I wrote a `CMakeLists.txt` which contains all the things in need.

How to use this kernel in your project?
-------------------------------------------------

1. copy the `kernel` dir under your project

2. modify your project `CMakeLists.txt`, here are some examples, you could also take a look at the cmakelists file of this project.

```
# For example, project is "xenia_clock"

# set values for freertos
set(FREERTOS_KERNEL_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/kernel)
set(PICO_SDK_FREERTOS_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/kernel)

# include freertos kernel dir
add_subdirectory(kernel)

# append library `freertos-kernel` to your project
target_link_libraries(xenia_clock freertos-kernel
                            pico_stdlib
                            hardware_clocks
                            hardware_spi
                            hardware_rtc
                            hardware_i2c
                            hardware_uart)
```

Isn't it easy for using? nahaha

More
-------------------------------------------------

I'm not a pro user of FreeRTOS, so the `FreeRTOSConfig.h` may have some problem, better review this file when you are using this kernel in your project.

Have fun with this!

Cheers,
