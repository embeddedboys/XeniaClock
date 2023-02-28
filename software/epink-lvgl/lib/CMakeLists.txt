# Copyright (c) 2023 IotaHydrae(writeforever@foxmail.com)
# 
# This software is released under the MIT License.
# https://opensource.org/licenses/MIT



add_library(common_lib printk.c ringbuffer.c ringbuffer_any.c)
target_include_directories(common_lib PUBLIC "../include")