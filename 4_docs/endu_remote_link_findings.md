# 手机 App ↔ 遥控器 ↔ 船：链路结论（V1.01.42 源码 + 船端 4.2.3 源码 + SITL）
事实（源码）：
- 遥控器 MCU：UART4 115200 ↔ ESP8684（手机 Wi-Fi）；USART3 1.5M ↔ 5.8G 图传/数传 ↔ 船 IO 板 ↔ 主控 SERIAL1（MAVLink chan 1）
- 帧格式：MAVLink **v1**（6 字节头，8 位 msgid）。mavlink_type 默认 1 → STX 0xC3、CRC 初值 0xFF1E；0xFE/0xFFFF 是非加密。船端 SR1_ENC 1 用同一套（pymavlink 补丁 MAVLINK_SELF_MOD_STX1 0xC3 / X25_INIT_CRC_SLLF 0xff1e）
- 遥控器解析器：长度必须等于表内长度，CRC_EXTRA 用表内值 → 表里没有的 msgid 会被丢
- 路由：WiFi→遥控器：sysid 0xA5 本地处理，其它 sysid 原样转发到船；船→遥控器：sysid 0xA5 本地、0xAF 声呐，其它全部原样转发到 App 并解析
- 本测试用到的消息全在遥控器表内且长度一致：HEARTBEAT 0(9) SYS_STATUS 1(31) PARAM_REQUEST_READ 20(20) PARAM_VALUE 22(25) PARAM_SET 23(23) SERVO_OUTPUT_RAW 36(21) COMMAND_LONG 76(33) COMMAND_ACK 77(3) BATTERY_STATUS 147(36) NAMED_VALUE_FLOAT 251(18) STATUSTEXT 253(51)
- ENDU 自定义状态用的是 NAMED_VALUE_FLOAT（ET_*），RT 油门是 COMMAND_LONG MAV_CMD_USER_2 → 都能过；没有自定义 msgid
- 遥控器自己 sysid 255/compid 190；App 用 sysid 200 才能被船区分（ET_APP_SYSID）
推断/未知：
- ESP8684 自己的固件不在 box 上 → 手机连的 SSID/密码、IP、端口、UDP 还是 TCP **未知**；App 做成可填（默认 192.168.4.1:14550 UDP 只是占位）。需要从原厂 App 抓包或问固件负责人
- 结论（推断）：V1.01.42 原版遥控器已能透传本测试的全部消息，遥控器测试版只是加固+标识
- 重要：App 走遥控器时**不能发 REQUEST_DATA_STREAM**（会改 SR1 速率，而 SR1 同时给 IO 板送 SERVO_OUTPUT_RAW 驱动电调）。App v0.3 已在中继模式下禁用
