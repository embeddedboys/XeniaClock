<h1 align="center">
    <span>Xenia Clock</span>
</h1>

<!-- <div style="text-align: center;">

<a href="https://iotahydrae.github.io/XeniaClock/">![Docs](https://img.shields.io/badge/docs-iotahydrae.github.io%2FXeniaClock%2F-green)</a> <a>![](https://img.shields.io/github/license/iotahydrae/xeniaclock)</a> <a>![](https://img.shields.io/github/forks/IotaHydrae/XeniaClock)</a> <a>![](https://img.shields.io/github/stars/iotahydrae/XeniaClock)</a> <a>![](https://img.shields.io/github/last-commit/iotahydrae/XeniaClock)</a> <a>  [![HitCount](https://hits.dwyl.com/IotaHydrae/XeniaClock.svg?style=flat-square)](http://hits.dwyl.com/IotaHydrae/XeniaClock)</a>

</div> -->



![Docs](https://img.shields.io/badge/docs-iotahydrae.github.io%2FXeniaClock%2F-green) ![](https://img.shields.io/github/license/iotahydrae/xeniaclock) ![](https://img.shields.io/github/forks/IotaHydrae/XeniaClock) ![](https://img.shields.io/github/stars/iotahydrae/XeniaClock) ![](https://img.shields.io/github/last-commit/iotahydrae/XeniaClock) [![HitCount](https://hits.dwyl.com/IotaHydrae/XeniaClock.svg?style=flat-square)](http://hits.dwyl.com/IotaHydrae/XeniaClock)

![Xenia Clock Tower](assets/Clock-Tower.jpg)


[[中文]](README.md) [[English]](README.en.md)

Table of Contents
------------------

- [介绍](#Introduction)
- [设计](#Design)
- [内部](#Inside)
- [许可证](#License)

[Gallery](gallery.md)
------------------

![Xenia Clock](assets/index.jpg)

<h2 align="center">
    <span>Introduction</span>
</h2>

![lvgl](assets/logo_lvgl.png) ![FreeRTOS](assets/logo_freertos.jpg) ![littleFS](assets/logo_littlefs.jpg) ![JLC](assets/logo_jlc.png)

![squareline studio](assets/logo_squareline.png)  ![GooDisplay](assets/logo_goodisplay.jpg)


一个完全开源的桌面时钟小工具，包括软件、硬件等。

使用电子纸显示器，支持网络和更多功能！

官方网站 : [`https://embeddedboys.github.io/XeniaClock`](https://embeddedboys.github.io/XeniaClock)

仓库位于 : [`https://github.com/embeddedboys/XeniaClock`](https://github.com/embeddedboys/XeniaClock)



<h2 align="center">
    <span>Design</span>
</h2>

(这里放一张完整结构3D模型渲染图)

Xenia Clock的外形设计，很大程度上的参考了如下建筑

![Xenia Clock, Ohio, USA](assets/Greene_County_Courthouse_Xenia.jpg) ![Erbil Clock Tower](assets/360px-Clock_of_Erbil.jpeg)

> left : Xenia Clock, Ohio, USA
> right : Erbil Clock Tower

Huh，**Xenia Clock** 由三部分组成，**楼顶**、**中间**、**电源**，每个部分都有不同的工作要做。

<p align="center">对设计框图感兴趣吗？</p>
![DesignStructure](assets/XeniaClock.png)

-----------------------

**Xenia Clock屋顶的预览设计**
> 时钟的其他部分还在建造

![roof](assets/roof.jpg)

**`Evaluation Board` 供电板**

![power supply board](assets/power_supply_board.jpg)

<h2 align="center">
    <span>Inside</span>
</h2>

| 零件 | 型号 |
| ---- | ----- |
| `主 MCU`      | RaspberryPi RP2040 双核 `133MHz` `288K SRAM`|
| `闪存`         | `4MB` 2x W25Q16
| `Power MCU`   | STC8G1K08A |
| `主屏幕`       | `1.54`寸墨水屏 |
| `副屏幕`       | `0.91`寸OLED                        |
| `网络`         | esp-01s AT|
| `传感器`       | AHT10 |
| `实时钟`       | DS1307 / DS3231 |
| `充放电管理`    | IP5306 |
| `照明` | 1x `1W` LED灯珠 或 4x `0.3W` 陶瓷灯丝
| `电池`         |  `400mAh` 锂电 |
有关这部分的详细信息，可以到官网硬件文档查看

<h2 align="center">LICENSE</h2>

此项目是在MIT许可证下发布的，有关详细信息，请查看`关于->许可证`。

玩得开心！

Cheers,
