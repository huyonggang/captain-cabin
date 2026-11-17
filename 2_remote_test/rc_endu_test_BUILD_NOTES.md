# 遥控器 ENDU 测试版（仅测试，禁止量产）— 基于 V1.01.42 源码
- 源：/workspace/rc_patched（V1.01.42；受控正式版是 1.01.43，box 上没有 43 源码 → 43 相对 42 的改动不在本测试版里）
- 副本：/workspace/roguetest/rc_endu_test（原树未动）；补丁：rc_endu_test_V1.01.42.patch（3 个文件，GBK 编码 + 原换行保持）
- 屏幕版本显示 "V1.01.42-ENDU-TEST"；上报给 App 的 SoftwareVERSION 仍是 10142（不影响原厂 App/OTA 判断）

## 改动（最小）
1. config_param.h：`ENDU_TEST_BUILD 1`，`ENDU_APP_SYSID 200`（= 船端 ET_APP_SYSID）
2. mavlink.c WiFi→船：sysid 200 显式原样转发（V1.01.42 的 default 分支本来就原样转发，这里只是固定下来，防止以后被拦）
3. mavlink.c 船→WiFi：照旧原样转发给 App；只是 MAV_CMD_USER_1/2（31010/31011）的 COMMAND_ACK 不再喂给遥控器自己的命令/应答逻辑
4. menu.c：版本号后缀 -ENDU-TEST
不改：摇杆 RC_CHANNELS 照常发（船端在 ENDU 里忽略，保持链路/失联保护行为不变）；上锁照常可用。

## 编译（box 上编不了：Keil MDK 工程，box 没有 armcc/armclang，也没有 arm-none-eabi-gcc）
1. 在 Windows 用 Keil MDK 打开 Projects/MDK-ARM/CatchXBlack_Pro.uvprojx（与 1.01.42 正式版相同的 MDK/编译器版本与 APM32F4 Pack）
2. 先确认未改的原始 V1.01.42 能编过；再把 rc_endu_test_V1.01.42.patch 打上（git apply --ignore-whitespace 或 patch -p1 --binary；注意 GBK、CRLF）
3. Rebuild（F7），输出在 Output/；按你们原来的方式（ST-Link/J-Link 或遥控器 OTA）烧录，烧前备份 1.01.43
4. 开机看到 "V1.01.42-ENDU-TEST" 即为测试版。测试完刷回 1.01.43
