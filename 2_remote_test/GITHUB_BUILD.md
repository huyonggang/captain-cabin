# GitHub 遥控器固件试编译

本流程用于先验证这份源码在 GitHub Windows 构建机上能否编译。Mac 无需安装 Keil。
仓库中未发现 Keil 授权信息；流程默认使用未激活的评估环境，可配置已有的有效 FlexNet 授权。
因此首次构建可能因 32KB 评估限制、授权、安装或源码问题失败，失败日志仍会上传。

## 最新失败原因：Keil 授权容量限制

运行 [44043719956](https://github.com/taogan1985-cmd/captain-cabin/actions/runs/44043719956)
已经成功部署工具链并完成源文件编译，在链接阶段报错：

```text
L6050U: The code size of this image (237820 bytes) exceeds the maximum allowed for this version of the linker.
```

日志中的工具版本为 `MDK-ARM Lite 5.25`。其 32KB 限制来自 Keil 授权，
237820 字节是链接器报告的代码大小，不是已生成 BIN 的大小。
这不同于 MCU Flash 不够；扩大 scatter 区域、增加超时时间或重复运行不能解除授权限制。
GitHub 托管 Windows 只提供计算环境，不包含 Keil 商业授权。
之前的小文件探测只验证编译器可以工作，未验证超出评估限制的完整镜像能否链接；
因此探测成功后，本工程仍会在完整链接阶段失败。

可行路线：

| 路线 | 所需条件 | 改动与原因 |
|---|---|---|
| GitHub 托管 Windows + 有效 Keil FlexNet 授权 | 已有支持 ARM Compiler 5、允许 CI 使用且构建机可访问的授权服务器 | 保留现有编译链，使用授权允许的容量进行链接 |
| GitHub 自托管 Windows runner | 已有安装和授权有效的 Windows Keil 构建机 | 在已有环境构建，需另外配置 runner 和匹配编译器版本，不能把当前部署步骤原样搬过去覆盖授权 |
| 免费 ARM GCC + GitHub Linux | 无 Keil 授权 | 需移植启动汇编、FreeRTOS RVDS 层、链接脚本及标准库适配；不是直接切换编译器字段，产物还需实机验证 |

本轮脚本新增了下面的 FlexNet 入口和 `L6050U` 的针对性诊断；尚未进行 GCC 移植，
也没有配置任何实际授权。没有有效授权时，默认评估模式仍会受限。

### 在 GitHub 配置已有 FlexNet 授权

1. 仓库 **Settings → Secrets and variables → Actions → Secrets** 添加
   `KEIL_LICENSE_SERVER`，值为授权管理员提供的 `端口@主机名`。
2. 如需指定授权产品，在 **Variables** 添加 `KEIL_LICENSE_VARIANT`：
   默认 `mdk_pro`，也支持 `mdk_std`、`mdk_cm_std`，应与实际授权一致。
3. 用正常的 `build.command` 命令上传配置修改并创建新任务。

配置入口只告诉编译器从哪里申请授权，不会产生或激活新的授权。
若服务器仅在公司内网可达，应使用能访问该网络的构建机；给 GitHub 填入内网地址本身不能建立网络连接。
当前代码同时配置 `TOOLS.INI` 的 FlexNet 字段和编译工具进程环境，配置后先执行小文件编译探测。
完整授权能否成功签出仍须以新任务结果为准。

服务器地址及主机名在控制台和上传诊断附件中会脱敏；真实值只用于临时构建机的工具配置。
附件脱敏步骤失败时不会上传诊断附件。

参考：[Keil 评估版限制](https://www2.keil.com/limits)、
[官方 FlexNet 配置说明](https://support.arm.com/documentation/101407/latest/About-uVision/Installation)。

## Mac 一键执行

双击仓库根目录的 `build.command`，或在终端执行：

```bash
bash "/Users/huyg/Project/rippton/embedded/captain-cabin/build.command"
```

脚本自动检查 GitHub CLI 与登录状态，将编译配置和遥控器源码的修改提交并推送到
`origin` 对应仓库的默认分支，触发编译、等待完成，并将附件和运行日志下载到
`build-artifacts/remote/<运行ID>/`。首次未登录时会引导浏览器登录；缺少 `gh` 且已有
Homebrew 时会安装 GitHub CLI。不会自动安装 Homebrew。

默认分支上已有的本地提交也会一起推送；不会强制推送或自动合并。
暂存区已有其他修改、无推送权限或当前不在默认分支时，脚本会报出具体原因。
仅提交列出的构建文件和 `2_remote_test/rc_endu_test/` 中的变更，船端和 App 的未提交改动不在自动暂存范围内。
默认执行会创建一次新编译；关闭终端不会取消已经启动的 GitHub 任务。
查询中出现 EOF 等连接错误时，脚本会保留网络错误日志并继续查询，不会重发编译请求。

继续等待和下载已有任务（将数字替换为运行页面末尾的运行 ID）：

```bash
bash "/Users/huyg/Project/rippton/embedded/captain-cabin/build.command" --resume 44038921177
```

`--resume` 不提交、不推送、不触发新任务；也可用于补下已完成任务的附件。
普通查询和下载最多重试三次；等待编译期间每十秒查询一次，最多等待 45 分钟。

只检查环境、不上传或编译：

```bash
bash "/Users/huyg/Project/rippton/embedded/captain-cabin/build.command" --check
```

## 上传和运行

1. 将当前仓库文件提交并推送到你的 GitHub 仓库默认分支。必须包含根目录的隐藏文件夹
   `.github/workflows/`、`scripts/` 和完整的 `2_remote_test/`，保持目录结构。
   只上传 `2_remote_test` 文件夹不会出现本构建流程。
2. 在 GitHub 打开仓库的 **Actions**，如有提示，启用该仓库的 Actions。
3. 选择 **Remote firmware - Keil build test**，点击 **Run workflow**，选择分支并运行。
   本流程只有手动触发，不会在每次 push 时自动构建。
4. 在该次运行页面底部的 **Artifacts** 下载结果：
   - 成功时：`remote-firmware-app`，包含应用 BIN、HEX 和 BIN 的 SHA256。
   - 成功或失败时：`remote-keil-diagnostics`，包含准备、安装和编译阶段产生的日志。
   - 构建在安装前失败时，可能没有 `keil-build.log`，请查看对应步骤和 `setup.log`。

无需先填写 GitHub Secrets 即可尝试源码编译检查，但已确认默认评估模式不能链接本项目的完整镜像。
此流程不会自动获得完整 Keil 授权；
若日志出现 code size limit、license checkout 或 L60xx 等信息，应结合具体错误判断，
不要把所有 L60xx 链接错误都当成授权问题。

## 使用的环境

- GitHub `windows-2022`。
- Keil 官方 MDK 5.25 安装包，使用 ARM Compiler 5.06 update 6 build 750。
  原工程要求 update 5 build 528；此次是同一 Compiler 5 系列的兼容性试编译，
  不能视为原工具链精确复现。部署后检查版本，不会切换到 ARM Compiler 6。
- Geehy 官方 `APM32F4xx_DFP.1.0.11`，驱动源码仍使用本仓库的版本。
- 安装包与设备包在构建时从官方 HTTPS 地址下载，核对固定 SHA256 后再解压。
- 使用 `scripts/keil_ci.py` 直接读取官方自解压 EXE 中的 ZIP，不启动安装程序，
  不运行驱动安装器。按包内 `SETUP.INI` 生成 `TOOLS.INI`，保留原有 ARMCC 注册项
  和默认 `mdk_lite` 评估模式，写入该文件声明的 32 位 MDK 产品注册表路径与版本。
  配置有效 FlexNet 服务器时，改用相应的 `*_flex` 产品模式。
  不加入序列号或修改许可证机制。
- 展开安装包自带的 `ARM.CMSIS.5.3.0`、`Keil.ARM_Compiler.1.4.0` 基础包，
  再部署工程要求的 Geehy 设备包，避免只解开外层 EXE 却没有启用内部基础包。
- 部署后先检查编译器版本并编译一个最小 C 文件，环境或授权错误会在正式固件编译前报告。
- 下载、编译器探测、编译、BIN 转换都有独立超时；运行时每 15 秒输出日志和进度。
  正式编译限时 8 分钟；超时先保存相关进程和窗口标题，再结束进程树。
- 当前已在 Mac 核对实际安装包结构、SHA256、配置转换和回归测试；Windows 注册与
  固件编译仍须以更新后 Actions 运行结果为准。

## 20 分钟安装超时的修复

运行 `44038921177` 已确认下载只耗时约 27 秒，随后等待安装程序退出直至超时。
旧的 `Start-Process ... --batch-install -Wait` 已移除，改为上述直接解压部署。
这解决的是安装器交互/进程等待这一环节，不会自动获得完整 Keil 授权。

更新后执行正常构建命令，脚本会提交并推送新的 workflow、部署助手及测试，并启动新任务：

```bash
bash "/Users/huyg/Project/rippton/embedded/captain-cabin/build.command"
```

不要用旧任务的 **Re-run jobs** 测试此修复；旧任务仍对应旧提交。
`--resume 44038921177` 只会下载旧任务结果，也不会使用修改后的部署代码。

诊断附件中的 `setup.log` 记录完整部署过程，`download-*.log` 记录下载，
`compiler-version.txt` 和 `compiler-probe.log` 记录工具检查，`keil-build.log` 记录
固件编译，`timeout-processes.txt` 仅在进程超时时生成。

参考：[Keil 安装说明](https://support.arm.com/documentation/101407/latest/About-uVision/Installation)、
[Keil 命令行构建](https://www.keil.com/support/man/docs/uv4/uv4_commandline.asp)、
[评估版限制](https://www2.keil.com/limits)、
[无人值守安装讨论](https://community.arm.com/forums/f/keil-forum/34592/keil-uv4-silent-install)、
[MDK 注册表路径说明](https://support.arm.com/documentation/ka003041/1-0/)。

## CI 工程的临时处理

流程生成 `CatchXBlack_Pro.ci.uvprojx`，原始 `.uvprojx` 和固件源文件保持不变：

- 原工程引用的 `Drivers/img/ROGUE_MAX.c` 不在源码包内。仅当该文件缺失且 C/H 中没有
  区分大小写的 `ROGUE_MAX` 符号引用时，从 CI 工程中移除这个条目；不会生成占位图片。
  现有船型枚举 `Rogue_MAX` 是不同符号，保留。
- 跳过原来的两个 AfterMake 命令，构建成功后由 workflow 明确调用 `fromelf`。
  不运行依赖仓库外 `boot.hex` 和 `srec_cat.exe` 的 Bootloader 合并步骤。
- 不重复应用 `rc_endu_test_V1.01.42.patch`，测试改动已经存在于源码内。
- CI 工程选择 ARMCC 5.06 update 6 build 750，原工程的 update 5 选择保持不变。

## 输出含义

BIN 文件名为 `Remote_V1.01.42_ENDU_TEST_app_0x08010000.bin`，是应用程序镜像，
对应 Flash 地址 **0x08010000**，不包含 Bootloader。不要当成从 0x08000000 开始的整包。
原 scatter 文件从该偏移起仍声明了 1MB 长度；workflow 额外检查 BIN 不超过剩余
960KiB，并检查复位向量位于应用区，未修改原链接布局。

成功生成 BIN 只证明本次构建通过，不代表实机功能、升级路径或烧录已经验证。

后续若需完整 Keil 授权，需先确认授权类型能否用于临时 GitHub 构建机；
现有电脑上的授权不能假定直接复制到另一台机器就可用。
