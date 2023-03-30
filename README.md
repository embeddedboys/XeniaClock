<h1 align="center">
    <span>Xenia Clock</span>
</h1>

<!-- <div style="text-align: center;">

<a href="https://iotahydrae.github.io/XeniaClock/">![Docs](https://img.shields.io/badge/docs-iotahydrae.github.io%2FXeniaClock%2F-green)</a> <a>![](https://img.shields.io/github/license/iotahydrae/xeniaclock)</a> <a>![](https://img.shields.io/github/forks/IotaHydrae/XeniaClock)</a> <a>![](https://img.shields.io/github/stars/iotahydrae/XeniaClock)</a> <a>![](https://img.shields.io/github/last-commit/iotahydrae/XeniaClock)</a> <a>  [![HitCount](https://hits.dwyl.com/IotaHydrae/XeniaClock.svg?style=flat-square)](http://hits.dwyl.com/IotaHydrae/XeniaClock)</a>

</div> -->

![Docs](https://img.shields.io/badge/docs-iotahydrae.github.io%2FXeniaClock%2F-green) ![](https://img.shields.io/github/license/iotahydrae/xeniaclock) ![](https://img.shields.io/github/forks/IotaHydrae/XeniaClock) ![](https://img.shields.io/github/stars/iotahydrae/XeniaClock) ![](https://img.shields.io/github/last-commit/iotahydrae/XeniaClock) [![HitCount](https://hits.dwyl.com/IotaHydrae/XeniaClock.svg?style=flat-square)](http://hits.dwyl.com/IotaHydrae/XeniaClock)


[[中文]](README.md) [[English]](README.en.md)

Table of Contents
------------------

- [介绍](#Introduction)
- [设计](#Design)
- [内部](#Inside)
- [许可证](#License)

Gallery
------------------
[[gallery]](gallery.md)

Introduction
------------------

一个完全开源的桌面时钟小工具，包括软件、硬件等。

使用电子纸显示器，支持网络和更多功能！

官方网站 : [`https://embeddedboys.github.io/XeniaClock`](https://embeddedboys.github.io/XeniaClock)

仓库位于 : [`https://github.com/embeddedboys/XeniaClock`](https://github.com/embeddedboys/XeniaClock)


![pico](assets/raspberry-pi-pico.svg)

![lvgl](assets/logo_lvgl.png) ![squareline studio](assets/logo_squareline.png) ![FreeRTOS](assets/logo_freertos.jpg) ![littleFS](assets/logo_littlefs.jpg)

![GooDisplay](assets/logo_goodisplay.jpg) ![JLC](assets/logo_jlc.png)

Design
------------------

嗯，**Xenia Clock** 由三部分组成，即**屋顶**、**中间**、**电源**，每个部分都有不同的工作要做。

很难用语言来解释，让我们看看这张设计结构的图片

![DesignStructure](assets/XeniaClock.png)

-----------------------

**Xenia Clock屋顶的预览设计**
> 时钟的其他部分还在建造

![roof](assets/roof.jpg)

**`Evaluation Board` of power supply part**

![power supply board](assets/power_supply_board.jpg)

Inside
------------------
* `主 MCU`  - raspberrypi RP2040

* `副 MCU`   - STC8G1K08A

* `主屏幕`    - 1.54 寸 电子纸显示屏

* `副屏幕`    - 0.91 寸 OLED (默认黄色)

* `网络`      - esp01s AT

* `传感器`    - AHT10 温湿度传感器

* `实时钟`    - DS1307/DS3221

* `充放电管理` - IP5306

* `电池`      - 200mAh 锂电池


LICENSE
------------------

此项目是在MIT许可证下发布的，有关详细信息，请查看`关于->许可证`。

玩得开心！

Cheers,
