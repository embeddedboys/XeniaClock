<h1 align="center">
    <span>Xenia Clock</span>
</h1>

<!-- <div style="text-align: center;">

<a href="https://iotahydrae.github.io/XeniaClock/">![Docs](https://img.shields.io/badge/docs-iotahydrae.github.io%2FXeniaClock%2F-green)</a> <a>![](https://img.shields.io/github/license/iotahydrae/xeniaclock)</a> <a>![](https://img.shields.io/github/forks/IotaHydrae/XeniaClock)</a> <a>![](https://img.shields.io/github/stars/iotahydrae/XeniaClock)</a> <a>![](https://img.shields.io/github/last-commit/iotahydrae/XeniaClock)</a> <a>  [![HitCount](https://hits.dwyl.com/IotaHydrae/XeniaClock.svg?style=flat-square)](http://hits.dwyl.com/IotaHydrae/XeniaClock)</a>

</div> -->

![Docs](https://img.shields.io/badge/docs-iotahydrae.github.io%2FXeniaClock%2F-green) ![](https://img.shields.io/github/license/iotahydrae/xeniaclock) ![](https://img.shields.io/github/forks/IotaHydrae/XeniaClock) ![](https://img.shields.io/github/stars/iotahydrae/XeniaClock) ![](https://img.shields.io/github/last-commit/iotahydrae/XeniaClock) [![HitCount](https://hits.dwyl.com/IotaHydrae/XeniaClock.svg?style=flat-square)](http://hits.dwyl.com/IotaHydrae/XeniaClock)

[[中文]](index.md) [[English]](index-en.md)

Table of Contents
------------------

- [Introduction](#Introduction)
- [Design](#Design)
- [Inside](#Inside)
- [License](#License)

Introduction
------------------

A fully open-sourced desktop clock gadget, including software, hardware, and more. Using an e-paper display, support network, and more functions! the platform is based on RP2040.

![pico](assets/raspberry-pi-pico.svg)

![lvgl](assets/logo_lvgl.png) ![squareline studio](assets/logo_squareline.png) ![FreeRTOS](assets/logo_freertos.jpg) ![littleFS](assets/logo_littlefs.jpg) 

![GooDisplay](assets/logo_goodisplay.jpg) ![JLC](assets/logo_jlc.png)

Design
------------------

Well, **Xenia Clock** is consists of three parts, namely **"Roof"**, **"Middle"**, **"Power"** and
each part got different work to do.

It's hard to explain in words, let's just take a look at this picture of designing structure


![DesignStructure](assets/XeniaClock.png)

-----------------------

**A preview design of Xenia Clock's roof**
> the other parts of the clock are still building

![roof](assets/roof.jpg)

**`Evaluation Board` of power supply part**

![power supply board](assets/power_supply_board.jpg)

Offical Site :
[`https://embeddedboys.github.io/XeniaClock`](https://embeddedboys.github.io/XeniaClock)

Repository at :
[`https://github.com/embeddedboys/XeniaClock`](https://github.com/embeddedboys/XeniaClock)


Inside
------------------

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
------------------

This project was published under an MIT license, check `About -> License` for more information.

Have fun with this!

Cheers,
