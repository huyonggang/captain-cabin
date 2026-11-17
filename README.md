# Rogue Max 电机耐久测试固件 v0.3b — 源码包说明

**⚠ 仅用于测试，禁止用于量产 / 出货。**

| 项目 | 内容 |
|---|---|
| 文件 | RogueMax_ENDU_TEST_v0.3b_源码_2026.11.17.zip（sha256 fd125574c6ff87be7cf7d9d74f10aad3e3212ebccd7510c0682665ef0a370c42） |
| 日期 | 2026-11-17（北京时间） |
| 版本 | 船端 ArduRover V4.2.3 ENDU-TEST v0.3b；遥控器 V1.01.42-ENDU-TEST；App RogueEnduranceTest 0.3-test |
| 来源 | 由 Grok Bot 为 nick（Rippton/CatchX 研发）在工作机副本中修改生成；生产源码未改动 |
| 船端基线 | ArduPilot 4.2.3 Rogue Max 生产版（esp32catchx_rogue_max，git 4a58f3e0，ESP-IDF v4.2.4-46）。hwdef 与生产版一致，v0.3b 已去掉船端 Wi-Fi |
| 遥控器基线 | **V1.01.42 源码**（受控正式版是 1.01.43，但手头只有 42 的源码，43 的改动不在本测试版中） |

## 目录
- 1_boat_firmware：完整补丁 endu_test_mode_v0.3b.patch、改动过的 Rover 文件、BASE_VERSION.txt（基线、编译、merge_bin 命令）
- 2_remote_test：遥控器测试版源码 rc_endu_test/（不含 Keil Output/ 旧编译产物）、补丁 rc_endu_test_V1.01.42.patch、编译说明（Keil MDK；box 上未编译）
- 3_app：Android App 源码 endu_app/（不含 build、.gradle、local.properties）
- 4_docs：报告 test_fw_app_plan.md（Wi-Fi 密码已删除）、链路结论、烧录说明
- 5_binaries：v0.3b 固件（app 0x20000 单独包 + esptool merge_bin 0x0 整包 + bootloader/分区表/otadata + SHA256SUMS）和 v0.3 APK

## 要点
- 测试只能由 App 启动；遥控器在测试中只能上锁急停，摇杆/模式切换无效（SITL 已验证）
- App 通过遥控器中继通信时用 sysid 200（船端参数 ET_APP_SYSID）
- 遥控器 Wi-Fi（ESP8684）的 SSID / IP / 端口 / UDP 还是 TCP 不在源码里，需确认
- 测试结束后船端和遥控器都刷回原厂正式固件
