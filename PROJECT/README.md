# 智能门锁工程（STM32F401RET6）

基于 STM32F401RET6（Cortex-M4，84MHz）+ 标准外设库（StdPeriph）的智能门锁项目，包含密码输入（矩阵键盘）、MG200 光学指纹、CY8CMBR3116 电容触摸、ST7789VM 240×240 OLED 显示、语音播报、L9110S 电机驱动开锁等功能。详见 [实习报告_智能门锁项目.md](实习报告_智能门锁项目.md)。

## 目录结构

```
Smart lock/
├── LIB\          ← 公共标准外设库（CMSIS 除外），所有子工程共享，勿删！
├── PROJECT\
│   ├── 01-led\       点亮 LED（呼吸灯）
│   ├── 02-key\       4×4 矩阵键盘
│   ├── 03-motor\     L9110S 直流电机驱动
│   ├── 04-usart\     USART1 串口 printf（115200）
│   ├── 05-tim\       TIM2 定时器延时
│   ├── 06-voice\     SPI 语音模块
│   ├── 07-lcd\       ST7789VM 240×240 OLED（字库 + 图片）
│   ├── 08-br3116\    CY8CMBR3116 电容触摸（I2C）
│   └── 09-mg200\     MG200 光学指纹（SPI）—— 最终完整版
├── 文档资料\          数据手册、参考资料
├── 1.环境搭建+新建工程-F411.docx   环境搭建教程
└── XYD_SmartLock_V2.pdf           硬件设计文档
```

每个子工程是**递进关系**：后一个工程在前一个的基础上新增一个模块（`USER\src\` 下的 .c 文件从 3 个递增到 13 个），可作为开发过程参考。

## ⚠️ 公共库说明

- 所有 9 个工程的 `.uvprojx` 都引用 `..\..\LIB\` 下的标准外设库源码（相对路径），**不要删除或移动 `Smart lock\LIB\`**；
- 各工程目录内遗留的 `STM32F4xx_StdPeriph_Driver\` 文件夹是历史副本，**不再被工程引用**（已被 .gitignore 排除），可自行清理；
- `CMSIS\`（启动文件、`stm32f4xx.h` 等）仍在各工程目录内，未统一。

## 编译环境

- Keil MDK-ARM v5 + 器件包 `Keil.STM32F4xx_DFP.2.7.0.pack`（安装包在 `Smart lock\` 根目录，不进 git）
- 目标器件：STM32F401RETx
- 烧录：ST-Link / 串口 ISP（工程内无 .hex 输出，用 .axf 直接下载）

## 构建产物

`Objects\`、`Listings\`、`DebugConfig\` 及 `*.uvguix.*`、`*.uvoptx` 等均为本地生成/每用户文件，已被 .gitignore 排除，不入库。
