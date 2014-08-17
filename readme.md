# 简介

支持蓝牙 4.0 的辉光管时钟，主控芯片为 STC15F2K60S2，主要特性如下：

- 六位数字显示
- 四个氖灯，可独立控制，用于显示冒号、小数点等
- 每个辉光管下安装有一个全彩 LED，可调节 LED 颜色
- 支持闹钟
- 可通过蓝牙对时钟进行设置
- 采用 SD2405ALPI 实时时钟，掉电后时间不会丢失
- 可通过蓝牙对时钟进行控制
- 带有自定义显示模式，可通过蓝牙显示任意数字（例如温度、网速等）

![辉光管时钟照片](http://blanboom.org/images/2014/08/NixieClock_1.jpg)

# 开发环境

- Keil C51 µVision V4.72.9.0
- Altium Designer 14

# 蓝牙指令

 *  TIMShhmmss    -  设置时间，hhmmss 为 24 时制时间
 *  TIMAhhmmss    -  设置闹钟，hhmmss 为 24 时制时间
 *  TIMLggrrbb    -  设置 LED 颜色，ggrrbb 为 LED 的 RGB 颜色
 *  TIMMx         -  打开/关闭闹钟，x = 0 时打开，x = 1 时关闭
 *  TIMDxxxxxxdd  -  进入自定义显示模式并显示内容，xxxxxx 为要显示的数字，dd控制四个点的显示，范围为 0~ 15，其对应的四位二进制数中的各位分别代表四个点的状态（1 为亮，0 为灭）
 *  TIMT          -  切换回时钟模式
