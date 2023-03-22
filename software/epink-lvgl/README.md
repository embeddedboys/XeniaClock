The Software Project of Xenia Clock
===================================

Intro (out-dated)
-----------------------------------

This software project was developed basicly based on the `pico-sdk`, so if you familarize with it, you could get into the project quick and easy.

Strucure (out-dated)
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
======================================

Building
--------------------------------------

### Install requirements

Ubuntu like:
```shell
# Basic
sudo apt install git build-essential cmake ninja-build libncurses5-dev -y

# Toolchain
sudo apt install gcc-arm-none-eabi -y
```

Fedora like:
```shell
# Basic
sudo dnf install git gcc g++ make cmake ninja-build ncurses-devel -y

# Toolchain
sudo dnf install arm-none-eabi-gcc-cs arm-none-eabi-gcc-cs-c++ arm-none-eabi-binutils-cs arm-none-eabi-newlib -y
```

### Fetch and update

```shell
# Fetch first
git clone https://github.com/embeddedboys/XeniaClock.git

# update submodule of this project
cd XeniaClock
git submodule update --init

# Then update submodule of pico-sdk
cd software/pico-sdk
git submodule update --init
```

Build
-----------------------------------------

**First**, go to the project dir.
```shell
cd XeniaClock/software/epink-lvgl
```

**Then** made a config first, you could use menuconfig like blow:
```shell
./build.sh menuconfig
```
or just use a default config
```shell
make xeniaclock_defconfig
```

Finally, start building
```shell
./build.sh

# you should see files like blow
arch                   include    Makefile               scripts
build.sh               init       memmap_default.ld      tests
CMakeLists.txt         Kbuild     misc                   TODO.md
compile_commands.json  Kconfig    net                    ui
dir_build              kernel     pico_sdk_import.cmake  xenia_clock.elf
Documentation          lib        port
drivers                lv_conf.h  README.md
fs                     lvgl       references
```

`dir_build` is the dir where store building files

`xenia_clock.elf` is a symbol link where program file be generated.

Flashing
--------------------------------------
### Though debugger
if you are using a CMSIS-DAP and openocd installed on your computer, just type like
```
./build.sh -p
```

### Though USB


```
1) connect the device to computer though USB
2) push down the `BOOT` button, then push down the `RESET` button
3) a `RPI` disk device will be found on your computer
4) put the uf2 file into device and flash cycle will be start
5) after flash done, device will restart automatically
```

Hints for developers
-----------------------------------

Here some tips you should known before starting develop

1. sleep function like `sleep_ms` should never called in lvgl timer callback so did in interrupt isr, it cause system to crash, considering replace it with `busy_wait_ms`.

2. the period of seconds bit of time updating shouldn't be too fast, it cause display panel going flash, I suggested set it's period to 5s at least.

3. Actually, you didn't have to delete the unused function, beacase most of linkers will do this
automatically

4, Anywhere code block that you didn't want to interrupted by other threads, you should give them a lock. for gpio holding function etc. if this got interruptted, There could caused gpio level holding time be wrong.
