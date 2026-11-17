> 注：本文件中的 Wi-Fi 密码已删除。v0.2 的船端 Wi-Fi 方案在 v0.3b 已整体去掉。

# Rogue Max 电机耐久测试：测试固件 + 手机 App 方案与原型（v2，2026-11-17）

> v2 更新：Wi-Fi 直连改为默认链路；12 V 稳压电源供电下屏蔽电池保护；转速上限 6000 rpm（`ET_PWM_MAX 1773`）；反转默认 80%；App v0.2（四个页签、无级油门条）；模拟器真截图；烧录指南（§10）。v1 原文备份在 `test_fw_app_plan_v1.md`。

> 只用于测试，不能装到客户船上。所有改动都在副本 `/workspace/roguetest/ap_test`（从 `build_orig/ardupilot_4.2.3` 复制）里做，**生产源码没改动**，**没有烧录任何设备**。
> 标注说明：【事实】是读源码、原理图或在 box 上实测得到的；【推断】是根据事实推出来的；【假设】是还要上实物验证的。

## 0. 结论先说
1. **链路**：v2 起默认**手机 Wi-Fi 直连船上 ESP32**。测试固件开 AP 热点 `RogueMax-ENDU`（密码已删除），走 UDP 14550，挂在空着的 SERIAL3 上，**标准 MAVLink2，不加密**（`SR3_ENC 0`）。**USB-OTG 有线**（CP2102 → UART0/SERIAL0，921600）保留为备用，最稳。两条都不经过遥控器和图传。【假设】Wi-Fi 在真板上的内存和 CPU 占用还没实测，见 P1-6。
2. **固件**：已经在副本里加了一个测试模式 **模式 30「ENDU」**，两种运行方式共用一套代码：
   - **模式1 自动**：App 只负责设参数和点开始，循环由固件自己跑，手机断开也照常跑。
   - **模式2 实时**：App 每 200 ms 发一次油门命令，同时充当心跳。超过 `ET_RT_TMO`（默认 1 s）没收到，电机自动缓停。
   - **转速上限**：所有输出（两种模式、正反转）都被硬限在 `ET_PWM_MAX`（默认 1773 µs ≈ 6000 rpm，**开环、按水槽表**）。油门 100% = 上限；反转默认 80%（`ET_REV_THR`）；App 发多大都会被固件夹住。
   - **稳压电源**：ENDU 模式下电池失联保护只报文字、不动作，由 `ET_VMIN 10.5 V` 和 `ET_IMAX 15 A` 管欠压和过流。mAh 保护默认就是关的（`BATT_LOW_MAH/CRT_MAH 0`）。
   - ESP32 固件（含 Wi-Fi）**编译通过**；用 **SITL 仿真跑通**了自动循环、断开手机后继续跑、实时控制、断链停机、PWM 上限、反转 80%、越界夹紧、电池保护被忽略。
3. **App**：已经做出 **v0.2 调试版 APK**（连接 / 参数 / 监控 / 日志四个页签，正转和反转各一根无级油门条，旁边显示 % 和估算 rpm）。它能接 Wi-Fi 或 USB，读写参数，开始、暂停、继续、急停，能实时看电压、电流、PWM 和测试状态，每秒记一行 CSV，能一键导出到「下载/RogueEndurance」。App 里有**前台服务、CPU 唤醒锁、Wi-Fi 锁和常亮屏幕**，切到后台或手机进 Doze，链路和日志都不断。**在 Android 14 模拟器上跑起来并截了图**（§5），**还没在真手机和真船上试过。**
4. **监测的限制**：主控现在只能测**整船**电压和电流（INA169 加 5 mΩ 采样电阻）。电流低于 1 A 有采样盲区。**单电机的电流和转速主控现在拿不到**。电调其实已经上报（消息 502），但只停在副芯片里，要改副芯片转发（第二阶段）。

## 1. 手机到 Rogue Max 的通信路径

| 方案 | 路径 | 结论 |
|---|---|---|
| A. USB-OTG 直连主控（备用，最稳） | 手机 → OTG 线 → 船端 USB 板 → CP2102 → ESP32 UART0（SERIAL0） | 【事实】主控原理图 `main_raw.txt:132-187`：CP2102-GMR 接 `MCU_USB_UART0_RXD/TXD`，DTR/RTS 经两颗 SS8050 接成自动下载电路，接 EN 和 IO0。`defaults.parm` 设了 `SERIAL0_PROTOCOL 2`（MAVLink2）、`SR0_ENC 0`（不加密），`hwdef_h` 设了 `HAL_SERIAL0_BAUD_DEFAULT 921600`。所以**任何标准 MAVLink 地面站都能直接连**，Mission Planner 或 QGC 都行。【注意】App 必须让 DTR 和 RTS 都保持释放，否则会把 ESP32 复位。App 已经这样处理。 |
| B. 走遥控器 Wi-Fi 透传 | 手机 → ESP8684 Wi-Fi → 遥控器 MCU → USART3 → 图传 → 5.8G → 船 | 【事实】数传口 SERIAL1 用的是 `SR1_ENC 1`：这是**自改的 MAVLink**，起始字节和 CRC 初值都改了（0xFF1E，见 `modules/mavlink/pymavlink/0001-...patch`）。遥控器只透传，并按 sysid 分流（`rc_video_channel_audit.md`）。【推断】能做，但 App 要实现私有帧格式，测试还得依赖遥控器和图传都开着。链路越长越容易断，不适合 24 h 台架测试。 |
| C. 船端图传的以太网或 Wi-Fi | 图传模块是跑 Linux 的 Wi-Fi 板 | 【事实】box 上没有图传固件源码，协议也是私有的。不推荐。 |
| **D. 手机 Wi-Fi 直连 ESP32（v2 默认）** | ESP32 开 AP，UDP 14550 | 【事实】HAL 里已经有 `WiFiDriver`（TCP 5760）和 `WiFiUdpDriver`，由 `HAL_ESP32_WIFI=1/2` 打开（`HAL_ESP32_Class.cpp:44-52`）。但 Rogue Max 的 `hwdef_h` 没开这个宏，而且自己重写了串口表，原来放 Wi-Fi 的 uartC 现在接的是 IO 副芯片。ESP32 用的是 D0WD-V3 芯片，板载 2.4G 陶瓷天线（`main_raw.txt:301,368`）。【推断】可以把 Wi-Fi 驱动挂到空着的 uartB（SERIAL3），电池 ADC 在 ADC1 上，不受 Wi-Fi 影响。但 Wi-Fi 协议栈要多占 50–70 KB 内存，还会和 SPI、IMU 抢 CPU，需要实测。**v2 已在测试副本里实现**：`hwdef_h` 加 `HAL_ESP32_WIFI 2`、`WIFI_SSID "RogueMax-ENDU"`、`WIFI_PWD "[已删除]"`、`HAL_SERIAL3_PROTOCOL MAVLink2`，`uartBDriver` 换成 `WiFiUdpDriver`（AP 地址 192.168.4.1，往 192.168.4.255:14550 广播），`defaults.parm` 里 `SR3_ENC` 改成 0。【事实】编译通过，bin 从 1.01 MB 涨到 1.50 MB（ota_0 是 1792 KB，占 82%）；静态 bss 67.7 KB。【假设】运行时 Wi-Fi 堆内存、和 IMU/SPI 抢 CPU、2.4G 信号距离都还没在真板上测。 |

**推荐 D 为默认、A 为备用**（按 nick 的要求）。Wi-Fi 不通或者丢包多，就插 OTG 线走 A；App 两个入口都有。两条链路可以同时在线，固件对两边都发遥测。

## 2. 电压、电流、转速

- 【事实】`BATT_MONITOR 4`，也就是模拟量电压加电流。
  - 引脚：`HAL_BATT_VOLT_PIN 2` 和 `CURR_PIN 3`，对应 ADC1 CH0 和 CH1。
  - 分压 13.7k/1.5k；电流换算 `HAL_BATT_CURR_SCALE 10` A/V。
  - 电驱板上是 INA169 加 5 mΩ 采样电阻，输出 0.1 V/A，设计量程 0–10 A（`esc_raw.txt:119-160`）。
  - 原理图备注：“ESP32 采样盲区 0~100 mV，1A 内有盲区”（`esc_raw.txt:423`）。
  - 测的是**整船总电流**，包括主控、图传、LED，不是单个电机。
- 【事实】电调 MM32SPIN360C 会通过 MAVLink 502 `ESC_RUNNING_STATUS` 上报每路电机的 `voltage/current/temperature/mrpm`。副芯片收下后只缓存，不往主控转（见 `history_analysis/motor_rpm_audit.md`）。所以现在单电机转速和电流**主控和 App 都看不到**。
- **最少需要的改动**（**不用加硬件**）：
  1. 副芯片把 502 按 2–5 Hz 转给主控。改 `serial_expan_main.c` 和 `esc_control.c`，约 20 行。
  2. 主控在方言里加入 502，收到后转成标准 `ESC_TELEMETRY_1_TO_4` 发给 App，并写进日志。约 100 行。
  3. 请王博确认 502 里 current 和 mrpm 的单位、上报频率，以及 mrpm 是不是已经换算成机械转速。
  - 如果想马上看单电机电流，可以先在两路电机线上各串一个外置电流表或霍尔钳表，App 里的电流只当整船参考。
  - 【推断】IO 固件是嵌在主控固件 ROMFS 里的，`hwdef.dat` 里有 `FORCE_TO_UPGRADE_IOMCU`，开机会自动升级副芯片。所以测试版副芯片会随测试固件刷进去，换回生产固件时应该会自动刷回。**要实物确认。**

## 3. 反转是怎么实现的
- 【事实】`SERVO1/2_FUNCTION 73/74` 是左右油门，`SERVO_MIN/MAX 1100/1900`，`DEAD 50`，中位 1500 = 停。主控把舵机输出用 `SERVO_OUTPUT_RAW` 经 LPUART 发给副芯片，副芯片再转给两路电调（`esc_control.c:63-74`）。
- 【事实】生产版手动模式本来就会输出负油门（倒车，`mode_manual.cpp` 里的 `raw_throttle_in_backward`）。差速混控里，**负油门会乘 1.3**（`AP_MotorsUGV.cpp:753-756`）。电调协议里还有一个 `DIRECT_REVERSE_MASK 0x8000`（`extern_esc_status.xml`，现在的转发路径没用到）。
- 【推断】PWM 低于 1500 就是反转，电调支持双向。但电调源码不在 box 上，**换向时电调有没有保护、要不要先停稳**，要问王博，或者先在台架上低油门试。
- 测试模式**不走差速混控**，所以没有那个 ×1.3，直接用 `output_test_pwm` 出 PWM。
- **v2 的油门到 PWM 映射**（`ModeEndurance::pct_to_pwm`）：
  - 正转：PWM = `ET_PWM_START` + pct × (`ET_PWM_MAX` − `ET_PWM_START`)，即 1% ≈ 1552，100% = 1773。
  - 反转：以中位 1500 镜像，100% = 1500 − 273 = 1227；**默认 80% → 1271 µs**（SITL 实测）。
  - |pct| < 0.5% 输出 1500（停）。`ET_PWM_MAX` 自己也被限在 1500–1900。
  - 反转油门单独用 `ET_REV_THR` 设，默认 80（%，是**上限范围内**的 80%，不是 ×0.8 的 PWM 偏移）。
- 正反转之间固定有一段停机，加上 `ET_RAMP` 斜坡（默认 50%/s），不会硬换向。

### 3.1 转速上限 6000 rpm（开环）
- 【事实】R12 水槽表（12.3 V，左电机，`data.py` 和 `单电机水槽电流转速测试 固件20251123.xlsx` 一致）：1760 µs → 5634 rpm / 2.45 A；1770 → 5900 rpm / 2.78 A；1780 → 6100–6300 rpm / 3.0–3.2 A；1790 → 6400–6600 rpm。
- 【推断】在 1770 和 1780（取中值 6200）之间线性插值，6000 rpm ≈ **1773 µs**（1773 → 约 5990 rpm，约 2.9 A/电机）。用 1780 的下限 6100 算是 1775 µs，所以 1773 偏保守。
- 【事实】`ET_PWM_MAX`（默认 1773）在固件里对**两种模式、两个方向**都生效；App 发 ±250% 也会被夹到 ±100%（SITL 实测：1773 / 1227）。App 端也按同一张表显示估算 rpm。
- 【假设 / 限制】
  1. 这是**开环**限制：只限 PWM，不看实际转速。负载、水温、电压变了，同样的 PWM 转速会变。表是 12.3 V 测的，**12.0 V 电源下同 PWM 转速会略低**（偏安全）。
  2. **反转从来没测过**，现在假设和正转对称。建议台架先用转速计测一下 1271 µs 和 1227 µs 的反转转速。
  3. 要做**闭环限速**，需要电调的实际转速：电调已经在 502 `ESC_RUNNING_STATUS` 里报 mrpm，但副芯片没转给主控。要**王博**改副芯片转发 502（见 §2），主控再按转速做闭环。

## 4. 循环逻辑放在哪里（两种模式都要）

| 方案 | 说明 | 结论 |
|---|---|---|
| **(a) 固件里新增一个模式，参数用 PARAM_SET 设** | 计时和状态机都在船上跑，App 只配置和监视 | **推荐，已经做了原型**。手机断开、App 被杀、手机没电，测试都照常跑，最可靠。 |
| (b) App 自己计时，发 RC override 或 MANUAL 油门 | 固件几乎不用改 | 24 h 测试离不开手机，手机一休眠或断线测试就停，数据也会断。**只适合短时间的实时调试**。 |
| (c) 固件跑循环，App 也能实时接管（a+b 合在一起） | 同一个模式里分「自动」和「实时」两种状态，共用安全检查、日志和遥测 | **按 nick 的要求做的就是这个**。 |

### 已实现（`Rover/mode_endurance.cpp`，加上各文件的接线改动，补丁见 `endu_test_mode.patch`）
- **模式 30「ENDU」**。进入这个模式不会让电机转，必须由 App 发开始命令。
- **命令**（COMMAND_LONG）：
  - `MAV_CMD_USER_1`（31010）：param1 填 0 = 急停并上锁，1 = 开始自动（param2 填 1 表示计数清零），2 = 暂停，3 = 继续，4 = 进入实时。
  - `MAV_CMD_USER_2`（31011）：实时模式用。param1 是左电机 %，param2 是右电机 %（-100..100），param3 是可选的保持时间（ms）。这条同时当心跳用。
- **自动循环**：正转 `ET_FWD_S` → 停 `ET_STOP_S` → 反转 `ET_REV_S` → 停，一直重复。
  - 累计运转满 `ET_BRST_INT` 秒后，插入一组点动：`ET_BRST_N` 次 ×（开 `ET_BRST_ON` 秒、停 `ET_BRST_OFF` 秒）。
  - 连续工作满 `ET_DAY_S` 秒后，休息 `ET_REST_S` 秒。
  - 累计运转满 `ET_TOTAL_H` 小时后自动结束（填 0 表示不限）。
  - 阶段只在边界切换。
- **默认参数**（都能在 App 里改）：
  - 循环：`ET_FWD_S 1800`，`ET_STOP_S 300`，`ET_REV_S 1800`。
  - 点动：`ET_BRST_INT 14400`，`ON 10`，`OFF 5`，`N 50`。
  - 每日休息：`ET_DAY_S 79200`（工作 22 h），`ET_REST_S 7200`（休息 2 h）。
  - 其他：`ET_RAMP 50`，`ET_MOT 3`（两个电机都跑），`ET_RT_TMO 1000`，`ET_IMAX 15`，`ET_VMIN 10.5`。
  - **`ET_THR` 默认 0。不设这个值，测试拒绝开始**，这样不会用一个猜出来的油门去跑。单位是「上限范围的 %」，100 = `ET_PWM_MAX`。
  - `ET_REV_THR 80`（反转为正转上限范围的 80%），`ET_PWM_MAX 1773`，`ET_PWM_START 1550`。
- **安全**：
  - 电压低于 `ET_VMIN` 持续 3 s，或电流高于 `ET_IMAX` 持续 2 s，进入 FAULT 并停机。
  - 在 ENDU 模式下，GCS 和油门失联保护不再切 RTL。原因是台架上没有遥控器，手机一拔就会被切走。这个模式自己管安全。
  - **电池保护（v2 改了）**：台架用 12 V 稳压电源，不是电池。ENDU 模式下 `handle_battery_failsafe` 直接返回，只发一条「ENDU: low/critical battery failsafe ignored (PSU test, ET_VMIN active)」，不切模式、不上锁。欠压由 `ET_VMIN 10.5 V`（持续 3 s）负责，过流由 `ET_IMAX 15 A`（持续 2 s）负责。
    - 【事实】mAh 保护：`BATT_LOW_MAH` 和 `BATT_CRT_MAH` 默认都是 0，也就是关的；`BATT_CAPACITY 3300` 只用来算剩余百分比，不触发动作。电源供电时 mAh 一直累加，**不会误触发**。烧录后要按 §10 检查这两个值是不是 0。
    - SITL 实测：把 `BATT_LOW_VOLT` 设成 20 V 强行触发，ENDU 照常跑，只打印「ignored」。
    - 离开 ENDU 模式后，电池保护恢复正常。
  - 上锁、切到别的模式、遥控器切模式，都会马上暂停。
- **断电续测**：累计运转秒数 `ET_CUM_S` 每 10 分钟存一次 flash。重启以后按「开始(续计)」接着累计。阶段本身不保存，会从正转重新开始。
- **遥测和日志**：
  - 每秒发一次 NAMED_VALUE_FLOAT：`ET_ST/PH/REM/CYC/BRST/CUMH/OUTL/PWML/PWMR/OUTR`（`ET_OUTR` 最后发，App 用它当一帧结束）。
  - 电压和电流走标准的 SYS_STATUS。
  - 板载日志写 `ETST`（每秒一条，含状态、阶段、计数、输出 %、左右 PWM、V、I）和 `ETPH`（每次切阶段一条）。`LOG_DISARMED 1` 已经打开，板上有 SD 卡（`HAL_ESP32_SDCARD 1`）。
  - 手机断开期间，数据靠板载日志补上。
- **固件版本名**改成了 `ArduRover V4.2.3 ENDU-TEST`，地面站一眼就能认出是测试固件。

### 已验证
| 项目 | 结果 |
|---|---|
| 原版 Rogue Max 编译（副本，没改动） | ✅ 在 box 上用 ESP-IDF 和 xtensa esp-2020r3 工具链，约 56 s，`ardupilot.bin` 1,006,112 B。哈希和 `out_orig` 不一样，因为路径和环境不同，符合 HANDOVER 第 0 章的说明。 |
| 测试固件编译（v2，含 Wi-Fi） | ✅ `ardupilot.bin` 1,497,184 B（Wi-Fi 协议栈多了约 490 KB；ota_0 分区 1792 KB，占 82%）。新增代码没有新的编译警告。bin 里能找到 `RogueMax-ENDU` 和 `ENDU-TEST`。 |
| SITL 仿真（同一份 Rover 代码，rover-skid 模型，加 Catchx 参数） | ✅ 用短参数跑了约 120 s，日志见 `sitl_run/sitl_endu_events.log`：①正转 40%（PWM 1690）→ 停 → 反转 30%（1345）→ 停，计数正确。②累计运转满 20 s 后插入 3 次点动。③工作满 70 s 后每日休息 5 s。④**25 s 不发心跳**（比 FS_TIMEOUT 10 s 长）测试照常跑，没有被切 RTL。⑤实时模式下左 35% / 右 -35% 正常。⑥**停发心跳约 1 s 后打印「App link lost」，电机斜坡降到 0**。⑦链路恢复后重新受控。⑧急停后上锁。（这是 v1 代码、加上限之前的结果。） |
| SITL v2：上限、反转、电池（`sitl_run/sitl_cap_check.py`，记录 `sitl_cap_check.log`） | ✅ ①`ET_THR 100` → 1773 µs；②反转 `ET_REV_THR 80` → 1271 µs；③`ET_THR 150` 被夹成 100% → 1773；④实时发 +250 / −250 → 1773 / 1227；⑤实时 50% → 1661；⑥`BATT_LOW_VOLT 20` 强制触发低压，ENDU 继续跑，只打印「ignored」；⑦急停后舵机回 1500 并上锁。SITL 用自己的 hwdef，所以 **Wi-Fi 部分没在仿真里验证**。 |
| App 的 MAVLink 编解码 | ✅ App 发出的 HEARTBEAT、COMMAND_LONG、PARAM_SET、PARAM_REQUEST_READ、REQUEST_DATA_STREAM 都被 pymavlink 正确解析，App 解码 pymavlink 发出的 NAMED_VALUE_FLOAT 也正确。 |
| APK 构建和运行 | ✅ v0.2：Gradle 8.14.3 + AGP 8.13，`compileSdk 35`，`minSdk 24`。在 **Android 14（API 34）x86_64 模拟器**上安装、启动、四个页签都能正常显示（box 没有 KVM，模拟器用纯软件 TCG + swiftshader 跑，很慢）。模拟器里**没有船**，所以截图里的数值是 App 的 demo 模式填的样例。 |
| 真机或实物 | ❌ 没刷机、没上船、没在手机上跑过 |

## 5. App 方案

- **自己开发 APK（已有 v0.2）**。Java 写的，用 usb-serial-for-android 库，自带精简版 MAVLink 编解码。
  - **常亮屏幕和后台存活**（nick 要求）：
    - 界面打开时 `FLAG_KEEP_SCREEN_ON`，屏幕不灭。
    - 链路、实时心跳和 CSV 日志都放在**前台服务** `LinkService` 里（类型 connectedDevice），通知栏常驻，上面有「急停」和「急停并退出」两个按钮。
    - 服务持有 `PARTIAL_WAKE_LOCK`（CPU 不睡）和 `WIFI_MODE_FULL_HIGH_PERF` Wi-Fi 锁（给 UDP 用）。切到后台、锁屏或进 Doze 都不断链。
    - 实时模式在后台也会继续发心跳，因为前台服务还活着。只有 App 被杀、服务停止、线拔掉，船端才会因为断链自动停。
    - 小米、华为、OPPO 这些手机还要**手动设置**：电池优化选「不限制」，打开「自启动」，在多任务里锁定 App。否则厂商系统可能直接杀掉进程。这一步 App 代码做不到。
  - **界面（v0.2）**：顶部四个页签，底部红色「急停 + 上锁」一直可见。
    - **连接**：①Wi-Fi 直连（默认，提示热点名和密码）；②USB-OTG（备用）；状态卡显示链路、模式、是否解锁、最后一条消息；「进入测试模式(30)」。
    - **参数**：**正转、反转两根无级油门条**（0–100.0%，0.1% 一档）。每根旁边实时显示「% ≈ rpm ≈ A/电机（PWM 偏移）」，换算用 App 内的 R12 水槽表，按船上读回来的 `ET_PWM_MAX` / `ET_PWM_START` 算，100% = 上限 ≈ 6000 rpm。反转默认 80%。下面是 17 个循环参数，「读取」和「应用(写入)」；还有模式1 的开始（清零）/ 开始（续计）/ 暂停 / 继续。
    - **监控**：大字号电压和电流；状态、阶段、剩余时间、左右 PWM 和估算 rpm、输出 %、循环数、点动组数、累计小时。模式2 实时控制：进入 / 退出实时，◀反转 / ■停 / 正转▶。
    - **日志**：当前 CSV 文件、历史文件列表、「一键导出」、「新建日志」、「急停并退出 App」。
  - **油门条的行为**（nick 要求）：
    - **自动模式**：松手就把 `ET_THR` / `ET_REV_THR` 写进船（PARAM_SET），「应用」按钮也会一起写。
    - **实时模式**：选了方向以后，拖动油门条**马上生效**，App 每 200 ms 发一次 `MAV_CMD_USER_2`，固件按 `ET_RAMP` 斜坡限速，再按 `ET_PWM_MAX` 限幅。
    - App 端把值限在 0–100%，固件端再夹一次，App 发什么都超不过上限。
  - **实时显示**：电压、整船电流、左右 PWM、输出 %、状态、阶段、本阶段剩余时间、循环次数、点动组数、累计运转小时、最后一条消息。
  - **日志**：每秒一行 CSV，字段有时间、状态、阶段、剩余、计数、输出、PWM、V、I、模式、是否解锁；事件（固件文字消息和命令应答）也单独记行。
  - **一键导出**：所有 CSV 复制到「下载/RogueEndurance」，并弹出分享菜单（微信、邮件等）。
- **截图**（`/workspace/roguetest/screenshots/`）：
  - 方法：**Android 模拟器**（Android 14 / API 34，x86_64，`-gpu swiftshader_indirect`，无 KVM 所以用 `-accel off` 纯软件跑），装的就是 v0.2 APK，**真实代码真实渲染，不是效果图**。
  - `00_connect_emulator_screencap.png` 是 `adb exec-out screencap` 直接截的屏。之后模拟器的显示合成器出了问题（软件 GPU 报 ColorBuffer 错误，之后 screencap 全黑），所以 01–04 改成让 App 在模拟器里用 `View.draw()` 把**自己正在运行的界面**画成 PNG（`--ez demo true --ez snap true`），再 `adb pull` 出来。界面和控件是同一份代码，只是少了 Android 顶部状态栏。
  - 船不在模拟器里，界面上的电压、电流、循环数这些都是 demo 模式的**样例值**，不是测量值。
  - 文件：`01_connect.png`（连接）、`02_params_sliders.png`（参数 + 油门条）、`02b_params_full.png`（参数页全长）、`03_monitor.png`（实时监控 + 实时控制）、`04_log_export.png`（日志导出）。
- **现成工具可以补位**：用 Mission Planner 或 QGC（手机版 QGC 支持 USB-OTG）连 SERIAL0，就能看 NAMED_VALUE_FLOAT 和电池数据，也能下载板载 `.BIN` 日志（含 ETST）。可以用来和自研 App 对照，或者在 App 出问题时临时顶上。

## 6. 产物路径
- 测试固件（v2，含 Wi-Fi）：`/workspace/roguetest/ardupilot_rogue_max_ENDU_TEST.bin`（1,497,184 B，sha256 `c8bab3ed…1e07443`）。
- 整套烧录文件：`/workspace/roguetest/build_endu_test/`，包含 bootloader、partition-table、ota_data、ardupilot.bin/.elf、`flash_args`（原始路径）和 `flash_args_flat`（本目录平铺）。烧录偏移：0x1000 bootloader，0xa000 分区表，0xf000 ota_data，0x20000 app。
- 原版对照固件：`/workspace/roguetest/build_baseline/ardupilot.bin`。
- 源码补丁：`/workspace/roguetest/endu_test_mode.patch`，包括 Rover 目录和 `hwdef/esp32catchx_rogue_max/`（Wi-Fi、SERIAL3、`SR3_ENC 0`）。`GCS_Mavlink.cpp` 那个 include 加了 ESP32 条件编译，是为了 SITL 能编过，对 ESP32 没有影响。
- 只给 SITL 用的编译修正：`/workspace/roguetest/sitl_only_buildfix.patch`，不用于固件。
- 测试副本源码树：`/workspace/roguetest/ap_test`。ESP32 编译目录在 `build/`，SITL 编译目录在 `build_sitl/`。
- SITL 脚本和记录：`/workspace/roguetest/sitl_run/`（`sitl_endu_test.py` 和 `sitl_endu_events.log` 是 v1；`sitl_cap_check.py` 和 `sitl_cap_check.log` 是 v2）。
- APK：`/workspace/roguetest/RogueEnduranceTest_v0.2-test.apk`（debug 签名，sha256 `cd46a15c…e2b1757`）；旧版 `RogueEnduranceTest_v0.1-test.apk`；源码在 `/workspace/roguetest/endu_app/`。
- 截图：`/workspace/roguetest/screenshots/`（见 §5）。
- 编译日志：`build_unmodified.log`、`build_test.log`、`build_test2.log`、`build_test3.log`（v2 Wi-Fi）、`build_sitl.log`、`build_sitl2.log`。

## 7. 要 nick 确认的问题
1. **怎么刷机**：用船上 USB（CP2102 加 esptool 921600，按上面的偏移写），还是你们平时用的 OTA 或上位机？刷测试版之前，先备份现在的固件和参数。
2. **测试油门**：`ET_THR` 填多少？现在 100% = 上限 ≈ 6000 rpm（约 2.9 A/电机），反转默认 80%（≈4750 rpm）。
   - 正转是跑 100% 满上限，还是某个巡航点？
   - 建议先在台架上用低油门（比如 20%）确认方向和 PWM，再一步步加上去。
   - 能不能在台架上用转速计测一下**反转**的实际转速？现在假设和正转对称。
3. Wi-Fi 热点名 `RogueMax-ENDU`、密码（已删除） 可以吗？多台船同时测要不要每台不同的名字？
4. 单电机转速和电流是不是必须要？要的话，需要王博提供 502 的单位，并同意改副芯片（第二阶段）。
5. 每日休息 2 h：是按「连续工作 22 h 后休息」，还是要按固定时段，比如每天凌晨 2 点到 4 点？现在是按前者做的，固件没有可靠的墙钟时间。
6. 船上有没有插 SD 卡？板载日志要靠它。
7. 已按 12 V 稳压电源处理。`ET_IMAX 15 A`（整船）合适吗？电源限流打算设多少？
8. 闭环限速要不要做？要的话得先请王博把 502 转发出来（第二阶段）。

## 8. 工作量估计（从 nick 确认上面几点开始算）
| 项 | 工作量 |
|---|---|
| 测试固件上实物联调（方向、PWM、失联、日志、续计） | 1–2 天 |
| App 真机联调（USB 权限、DTR/RTS、后台存活、导出） | 1–2 天 |
| App 完善（曲线图、参数预设、中文提示、权限引导） | 2–3 天 |
| 第二阶段：单电机转速和电流（副芯片 + 主控 + App） | 2–3 天，还要等王博的单位说明 |
| ESP32 Wi-Fi 直连真板验证（内存、CPU、距离、丢包） | 0.5–1 天（代码已经做完） |
| 第二阶段：闭环限速（依赖 502 转发） | 1–2 天 |
| **能开始台架测试** | **约 3–5 个工作日** |

## 9. 风险分级
- **P0**
  1. 测试固件流到客户船上。要用版本名 `ENDU-TEST` 和单独的文件名区分，测完必须刷回生产版。
  2. 电调换向和长时间运行的保护没有实物验证。必须先低油门试方向，再在有人看着的情况下跑满功率，`ET_IMAX` 和 `ET_VMIN` 一定要设。
  3. 无人值守跑 24 h 的发热和进水风险。要有人定时巡检，或者加一个温度测量。
- **P1**
  1. 整船电流有小于 1 A 的盲区，而且包含电子设备的耗电，不能当作单电机电流。
  2. 单电机转速和电流还没打通。
  3. USB 的 DTR/RTS 可能复位 ESP32。App 已经处理，但要实物验证。
  4. 在 ENDU 模式下屏蔽了 GCS、油门失联和**电池**保护，**测试固件绝对不能上水跑航线**，也不能接电池无人值守跑。
  5. **转速上限是开环的**，只按 12.3 V 的正转水槽表；反转没测过。实际转速可能偏离 6000 rpm，要用转速计抽查。
  6. **Wi-Fi 只编译过，没在真板上跑过**：Wi-Fi 协议栈运行时要几十 KB 堆内存，还会和 IMU、SPI 抢 CPU。真板上要看 `MEMINFO`/`PM` 和 IMU 有没有报错。如果不稳，退回 USB（把 hwdef 的 Wi-Fi 改动去掉就行）。
  7. 电源供电时，电源本身的限流或过流保护可能先于 `ET_IMAX` 动作，导致整船掉电重启。电源要 **≥15 A**。
  8. 小米、华为这类手机的后台杀进程。
  9. Wi-Fi 热点密码写死在固件里（已删除），只适合实验室。
- **P2**
  1. `ET_CUM_S` 每 10 分钟写一次 flash，每天 144 次，在可接受范围内。
  2. 重启后阶段会重新开始。
  3. 每日休息按累计工作时间算，不按墙钟时间。
  4. App v0.2 只在模拟器上跑过，没有在真手机上跑过。
  5. 在 box 上编出来的 bin 和你们 Docker 环境编的哈希不一样，正式要用的测试版建议在你们的标准容器里重新编一次。
- **P3**
  1. App 界面比较简陋，没有曲线图。
  2. 参数名、模式号 30 和以后的生产功能可能冲突（只在测试分支里用）。
  3. SITL 编译需要额外修正（只影响仿真）。
  4. 急停后 `ET_PWML/ET_PWMR` 遥测会停在最后一个值，但实际舵机输出已经回到 1500（SITL 看到的），只是显示问题。
  5. 原版树的 `.vscode/c_cpp_properties.json` 因为硬链接被误改过一次，已把 `compileCommands` 改回 `build/esp32catchx_rogue_max/compile_commands.json`，原始值无法确认。它没进 git，只影响编辑器。

## 10. 烧录和台架准备指南（测试固件专用）
> 只在台架上用，测完必须刷回生产固件。下面的命令**我没有执行**，box 上没烧任何东西。

**电源**
1. 用 **12 V 稳压电源，能输出 ≥15 A**（两个电机满上限约 2×3 A，加上启动冲击和电子设备，留余量；`ET_IMAX` 是 15 A）。电源限流设在 15–20 A。
2. 电源线和接头要按 15 A 选，正负极别接反。

**烧录（USB，CP2102）**
1. 先备份：`esptool.py --chip esp32 --port <COM口> --baud 921600 read_flash 0 0x400000 backup_<船号>.bin`，再用 Mission Planner 或 QGC 导出一份参数。
2. 写入（在 `build_endu_test/` 目录里）：
   `esptool.py --chip esp32 --port <COM口> --baud 921600 write_flash --flash_mode dio --flash_freq 80m --flash_size 4MB 0x1000 bootloader.bin 0xa000 partition-table.bin 0xf000 ota_data_initial.bin 0x20000 ardupilot.bin`
3. 【推断】副芯片会按 `FORCE_TO_UPGRADE_IOMCU` 开机自动升级，要实物确认。

**烧录后检查（连上 App 或地面站看参数）**
- 版本是 `ArduRover V4.2.3 ENDU-TEST`。
- `SERIAL3_PROTOCOL 2`、**`SR3_ENC 0`**。参数存储分区不会被这次烧录擦掉，如果船上原来存过 `SR3_ENC 1`，要手动改成 0 再重启，否则 Wi-Fi 上看不到数据。
- 手机能搜到热点 `RogueMax-ENDU`（密码已删除）。
- **`BATT_LOW_MAH 0`、`BATT_CRT_MAH 0`**（mAh 保护关）；`BATT_FS_LOW_ACT` 留着也行，ENDU 里会被忽略。
- `ET_VMIN 10.5`、`ET_IMAX 15`、`ET_PWM_MAX 1773`、`ET_REV_THR 80`；`ET_THR` 按测试计划填（不填测试不会开始）。
- 先用 20% 正转和反转各跑 10 s，确认方向、PWM（约 1594 / 1406）和电流正常，再上目标油门。

**测完**：按同样的偏移刷回生产固件（或写回备份），再把参数恢复成导出的那份。

---
## v0.3b（11:36 CST）— 全链路走遥控器
- 更正：前文“模拟器 Android 14/API 34”有误，实测是 pixel35 = Android 15/API 35；API 33/34 镜像未安装，只测了 API 35。
- 船端：去掉 Wi-Fi；新增 ET_APP_SYSID(200)，ET_APP_CH 默认 3。见 build_endu_test_v0.3b/、endu_test_mode_v0.3b.patch
- SITL（sitl_run/sitl_remote_relay_v03b.log，App 与遥控器同在 chan1、靠 sysid 区分）：遥控器(255)/其他(201) 进 30 被拒；App(200) 进 30+启动 PWM 1661；遥控器切模式/摇杆/暂停/RT 全部无效；遥控器上锁有效；遥控器在 ENDU 里解锁被拒；App 恢复/停止/退回 MANUAL 正常；ENDU 外遥控器照旧
- 链路结论：endu_remote_link_findings.md；遥控器测试版：rc_endu_test/、rc_endu_test_V1.01.42.patch、rc_endu_test_BUILD_NOTES.md
- App：默认“遥控器 Wi-Fi 中继”（v1 0xC3/0xFF1E，sysid 200，UDP/TCP 和地址可填，中继下不发 REQUEST_DATA_STREAM），USB-OTG 备用
- APK 崩溃修复证据：apk_test_logs/（通知拒绝下 FGS isForeground=true types=0x10、无 FATAL；crashtest 写出 Download/RogueEndurance/crash_*.txt 并在下次启动显示）
