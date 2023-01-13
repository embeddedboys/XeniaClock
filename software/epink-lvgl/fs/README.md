File System
================================

Design
--------------------------------
This filesystem is based on [littlefs](https://github.com/littlefs-project/littlefs)

A little fail-safe filesystem designed for microcontrollers 

Version info : [v2.5.1](https://github.com/littlefs-project/littlefs/releases/tag/v2.5.1) [6a53d76e90af33f0656333c1db09bd337fa75d23](https://github.com/littlefs-project/littlefs/commit/6a53d76e90af33f0656333c1db09bd337fa75d23)

```
                    littlefs
                        |
                        |
                        ^
                       HAL
                    /   |    \
                Flash  RAM  Micro SD
```

Porting
---------------------------------

we are going to port this filesystem on flash, maybe will using w25qxx series.

the ram and micro sdcard port just for testing.

- for flash like w25qxx

- for ram usually in mcu

- for micro sdcard