The Software Project of Xenia Clock
===================================

Intro
-----------------------------------

This software project was developed basicly based on the `pico-sdk`, so if you familarize with it, you could get into the project quick and easy.

Strucure
-----------------------------------
```
.
├── build                       # the build dir you will be working in
├── CMakeLists.txt              # cmake configuraion file of this project
├── common                      # common files used in this project
├── display                     # display handles
├── docs                        # some documentatations
├── font                        # font source files in dot format
├── i2c                         # native i2c implimentation
├── lv_conf.h                   # configuraion file for lvgl
├── lvgl                        # lvgl source, release/v8.2
├── main.c                      # main enty of this project
├── net                         # net work implimentation
├── pico_sdk_import.cmake       # pico-sdk cmake configuratoin file
├── port                        # native port for lvgl
├── README.md
├── references                  # datasheets, manuals, etc.
├── rtc                         # rtc implimentation
├── sensors                     # sensors imlementation
├── spi                         # native spi imlementation
├── tests                       # test files
└── ui -> ../../ui/             # symbol link to ui source code
```

Build & Flash
-----------------------------------

> Build platform is Ubuntu 18.04

1. source the enviroment
```shell
$ cd ..
$ source tools/envsetup.sh
```

2. get back to this folder and make build dir
```shell
$ cd epink-lvgl
$ mkdir build && cd build
```

3. run the build process in the build dir
```shell
$ cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -GNinja
$ ninja
```

4. reset the device in to flash mode and burn

```
1) connect the device to computer
2) push down the `BOOT` button, then push down the `RESET` button
3) a `RPI` disk device will be found on your computer
4) put the uf2 file into device and flash will autostart
5) after flash done, device will auto restart
```

Attention for developers
-----------------------------------

Here some tips you should known before starting develop

1. sleep function like `sleep_ms` should never called in lvgl timer callback so did in interrupt isr, it cause system to crash, considering replace it with `busy_wait_ms`.

2. the period of seconds bit of time updating shouldn't be too fast, it cause display panel going flash, I suggested set it's period to 5s at least.

3. Actually, you didn't have to delete the unused function, beacase most of linkers will do this
automatically

4, Anywhere code block that you didn't want to interrupted by other threads, you should give them a lock. for gpio holding function etc. if this got interruptted, There could caused gpio level holding time be wrong.

More
-----------------------------------
nothing yet
