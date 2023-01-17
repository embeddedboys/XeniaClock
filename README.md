![]() Xenia Clock
=================


A desktop clock gadget, using a e-paper display and based on RP2040 with network and more functions!


![pico](assets/raspberry-pi-pico.svg)

![lvgl](assets/logo_lvgl.png) ![squareline studio](assets/logo_squareline.png) ![FreeRTOS](assets/logo_freertos.jpg) ![littleFS](assets/logo_littlefs.jpg) 

![GooDisplay](assets/logo_goodisplay.jpg) ![JLC](assets/logo_jlc.png)

Design
==================

Well, **Xenia Clock** is consists of three parts, namely **"Roof"**, **"Middle"**, **"Power"** and
each parts got different works to do.

It's hard to explain by words, let's just take a look at this picture of designing structure


![DesignStructure](assets/XeniaClock.png)

-----------------------

**A preview design of Xenia Clock's roof**
> the middle and bottom part of clock is still building

![roof](assets/roof.jpg)

**`Evaluation Board` of power supply part**

![power supply board](assets/power_supply_board.jpg)

Offical Site :
[`https://embeddedboys.github.io/XeniaClock`](https://embeddedboys.github.io/XeniaClock)

Repository at :
[`https://github.com/embeddedboys/XeniaClock`](https://github.com/embeddedboys/XeniaClock)


Inside
------

* `MCU` - raspberrypi RP2040

* based on `PICO-SDK`

* `sub MCU` - STC8G1K08A

* `Display` - 1.54 inc E-paper fast-flush display

* `sub Dispaly` - 0.91 inc OLED display (yellow for default)

* `Network` - esp01s AT

* `Sensors` - AHT10 temperture humidity sensor

* `RTC` - DS1307/DS3221

* `Charge IC` - IP5306

* `Battery` - 200mAh lithium

LICENSE
----------

This project was pushlished under MIT license, check `About -> License` for more infomation.

Have fun with this!

Cheers,

## [FAQs](FAQs.md)
