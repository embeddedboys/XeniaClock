<h1 align="center">PowerMCU</h1>

This project build firmware for "Power" part of Xenia Clock, but it can be also used
in other project,

<h2 align="center">Setup</h2>

<h2>Requirements for developing</h2>

- VScode with PlatformIO extension

<h2 align="center">Building</h2>

1. Run `setup.sh` to prepare develop enviroment
```
$ ./setup.sh
```

should see prints like this
```
Installing tools to ~/.local/bin ...
1. Installing stc8gprog ...
Remember check this target path in you $PATH
```

2. 

<h2>Pin Map</h2>

| Pin | Function            |
|-----|---------------------|
| P32 | I2C SCL             |
| P33 | I2C SDA             |
| P55 | Power Enable        |
| P54 | ADC battery voltage |

<h2>I2C Protocol</h2>

<h3>Register Table</h3>

| Register | Address | Description                  |
|----------|---------|------------------------------|
| Clock    | 0x00    | The runing clock of powermcu |

<h3>Command Table</h3>

The default i2c address of slave mode `0x49`, it could changed in `i2c-slave.c`

The host sends ARG0 ~ ARG3 and CRC8 check code a total of 5 bytes.

After receiving the machine, the CRC8 value of the ARG0 ~ ARG3 is re-calculated, and the comparison between the host is not consistent, if it is not consistent, it is considered to be interfered by the transmission process. This command is invalid.

| Command               | byte0 : Address | byte1 : ID | byte2 : arg0 | byte3 : arg1 | CRC8 | Description                                   |
|-----------------------|------|------|------|------|------|-----------------------------------------------|
| |  | Non -parameter command |
| Power OFF             | 0x49 | 0x01 | 0x00 | 0x00 | 0x56 | 关闭对外供电                                  |
| Sleep                 | 0x49 | 0x03 | 0x00 | 0x00 | 0x80 | 主机休眠，从机接管控制权                       |
| |  | 带参命令 |
| Power OFF alarm       | 0x49 | 0x02 | t_h  | t_l  | xxx  | 定时（秒），关闭对外供电                         |
| Sleep alarm           | 0x49 | 0x04 | t_h  | t_l  | xxx  | 定时（秒），主机休眠，从机接管                    |
| Sleep then alarm wake | 0x49 | 0x05 | t_h  | t_l  | xxx  | 主机休眠，从机接管, 定时（秒），唤醒主机，主机接管 |
| Set Time | 0x49 | 0x06 | hour | minute | xxx | 设置从机的时间 |
| Get Time | 0x49 | 0x07 | hour | minute | xxx | 读取从机的时间 |

<h4>0x01 : Power OFF</h4>

关闭对外部供电`VDD_5V` `VDD_3V3`，自身进入掉电模式

<h4>0x02 : Power OFF Alarm</h4>

<h4>0x03 : Sleep</h4>

<h4>0x04 : Sleep Alarm</h4>


<h2>Key Behavior</h2>

| Action | Behavior | Description |
| ---- | --- | --- |
| Fast short press | 切换运行状态 | 在开机状态下
| 2 seconds Long press | 开/关机 | 需在完全关机 或者 开机状态下 |

