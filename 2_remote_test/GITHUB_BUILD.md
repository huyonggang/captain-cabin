# 遥控器固件：Windows 自托管 GitHub Actions 构建

当前测试工程：`/Users/huyg/Downloads/captain-cabin`。
当前仓库：[huyonggang/captain-cabin](https://github.com/huyonggang/captain-cabin)。

## 当前运行方式

Mac 的 `build.command` 上传源码并触发 GitHub Actions；GitHub 将任务交给
**PAILIKEN** Windows runner，使用它已有的 Keil 安装与授权编译，结果再由 Mac 下载。
workflow 使用 `[self-hosted, Windows, X64]` 标签，并检查 `RUNNER_NAME` 为 `PAILIKEN`。
当前流程不再使用 GitHub 托管的 `windows-2022`，也不调用旧的 `keil_ci.py setup` 部署步骤。

本流程只读取现有 Keil 配置。不会下载或安装 Keil、设备包，不重写 `TOOLS.INI`、
注册表或授权配置，也不会读取仓库的 `KEIL_LICENSE_SERVER` Secret 来覆盖电脑现有环境。
现有授权是否能使用，取决于 runner 运行账号及该电脑的实际授权状态。

## 直接执行

保持 Windows 电脑开机联网，runner 的 `run.cmd` 正在运行，再在 Mac 执行：

```bash
bash "/Users/huyg/Downloads/captain-cabin/build.command"
```

脚本会：

1. 从 `origin` 推送地址确定目标仓库，检查权限和 `PAILIKEN` 在线状态。
2. 提交并推送构建配置、辅助脚本、说明及遥控器源码目录中的修改。
3. 触发新的手动构建任务，等待并下载固件或失败日志。

不会自动暂存船端和 App 的未提交修改；默认分支已有的本地提交也会随普通 push 上传。
不强制推送，不自动合并；暂存区已有其他内容时会先报错。

只检查 Mac 侧配置和 runner 在线状态：

```bash
bash "/Users/huyg/Downloads/captain-cabin/build.command" --check
```

继续已有任务（示例数字需替换为当前仓库运行页面末尾的 ID）：

```bash
bash "/Users/huyg/Downloads/captain-cabin/build.command" --resume 123456789
```

`--resume` 不提交、不上传、不创建新任务。修改 workflow 后应使用正常构建命令创建新任务，
旧任务的 Re-run jobs 和 `--resume` 仍对应旧提交。

## Windows 电脑需要具备的环境

- Git 和 **Python 3.10 或以上**在 runner 账号的 PATH 中；安装后需重新启动 runner。
- workflow 使用 Windows 自带的 **Windows PowerShell**，无需额外依赖 `pwsh`。
- 有效授权的 Keil MDK，且已安装 ARM Compiler **5.06**（`armcc.exe`）。
  ARM Compiler 6 的 `armclang.exe` 不能直接替代它。
- 已在 Keil 的实际设备包目录安装 `Geehy.APM32F4xx_DFP.1.0.11`。
- runner 应由平时能够正常使用 Keil 授权的 Windows 用户启动。首次建议直接运行 `run.cmd`；
  改为服务时，应确认服务账号仍能使用同一授权与环境。

注册 runner 的入口是仓库 Settings → Actions → Runners → New self-hosted runner，
选 Windows / x64，按页面生成的命令操作。当前已注册的名称为 `PAILIKEN`。

## Keil 路径和编译器的自动识别

`scripts/keil_existing.py` 按以下顺序寻找现有安装：

1. 仓库 Variable `KEIL_ROOT`（可选），通过 `KEIL_INSTALL_DIR` 传入；或电脑已有的 `KEIL_ROOT` 环境变量。
2. 现有 Windows MDK 产品注册表路径，只读访问。
3. PATH 中的 `UV4.exe` 及常见安装目录。

通常不需要填路径。若报 `Existing Keil not found`，在仓库
Settings → Secrets and variables → Actions → **Variables** 添加：

```text
名称：KEIL_ROOT
值：实际 Keil 根目录，例如 D:\Keil_v5
```

此根目录应包含 `UV4\UV4.exe`、`TOOLS.INI` 和 `ARM` 子目录。
显式指定的路径不正确时会报错，不会悄悄切换到另一份 Keil。

脚本从现有 `TOOLS.INI` 中读取编译器注册路径，检查实际版本，并优先选择原工程的
**5.06 update 5 build 528**；没有该版本时，选择已注册的其他 5.06 版本。
仅在临时 `.ci.uvprojx` 中设置检测到的版本，原工程和原安装保持不变。
BIN 转换使用同一编译器目录中的 `fromelf.exe`。

设备包位置优先遵循现有 `TOOLS.INI` 的 `RTEPATH`。缺少所需版本时会明确报错，
需在 Windows Keil Pack Installer 中补齐；脚本不会自动安装或修改设备包。

## 编译前的授权检查

旧的小 C 文件编译检查不能验证 MDK-Lite 的 32KB 链接限制。
新流程先在临时目录中汇编并链接 **超过 32KiB 的 Thumb 指令**，不执行该探测镜像，
也不接触硬件。该检查通过后才开始准备和编译遥控器固件。

若该探测仍报 `L6050U`，说明当前 runner 账号使用的授权仍存在容量限制，或选中的
安装不是日常有效授权的安装。应检查 `compiler-version.txt`、实际安装路径和 runner 账号，
不应扩大 Flash 区域或延长超时来处理授权问题。

## 输出与失败日志

运行页面的 Artifacts：

- `remote-firmware-app`：仅在编译、BIN 转换和地址检查成功后上传。
- `remote-keil-diagnostics`：失败时也上传日志；授权信息脱敏失败则不上传该附件。

Mac 下载目录：`build-artifacts/remote/<运行ID>/`。

| 日志 | 用途 |
|---|---|
| `helper-tests.log` | CI 辅助脚本回归测试 |
| `existing-keil-check.log` | 实际 runner、安装路径、环境检查错误 |
| `existing-keil.json` | 检测到的根目录、编译器、设备包路径和检查结果 |
| `compiler-version.txt` | 实际使用的编译器版本 |
| `license-probe-assemble.log` / `license-probe-link.log` | 超过 32KiB 的授权探测 |
| `prepare.log` | 临时工程调整 |
| `keil-build.log` / `build.log` | 固件编译与链接 |
| `failure.txt` / `failure.json` | 已识别的失败原因及处理建议 |
| `timeout-processes.txt` | 工具超时时的相关进程信息 |

不会把 Windows 的原始 `TOOLS.INI` 或授权文件放入附件。
用于日志脱敏的临时授权值文件仅位于 runner 的临时目录，不在上传路径内。

## 固件含义及已有修复

输出 `Remote_V1.01.42_ENDU_TEST_app_0x08010000.bin` 是 **0x08010000** 起始的应用镜像，
不含 Bootloader。不得作为从 0x08000000 开始的整包使用。
生成后检查应用不超过剩余 960KiB，复位向量位于应用区，并记录 SHA256。
成功构建不代表遥控器实机功能或升级路径已经验证。

临时工程保留已做的两项处理：移除缺失且未被引用的 `ROGUE_MAX.c` 图片条目；
关闭原 AfterMake 命令，由构建助手生成应用 BIN，跳过依赖仓库外 `boot.hex` 的整包合并。
源码中已经包含 ENDU 测试改动，不重复应用补丁。

此前已修复 Windows CP1252 误读 UTF-8 中文 JSON 的测试错误。
此前 GitHub 托管任务的 `L6050U` 已确认来自其未授权 MDK-Lite；此次改为使用现有
Windows 授权，并在固件编译前检查链接容量。

参考：[GitHub 自托管 runner 配置](https://docs.github.com/en/actions/how-tos/manage-runners/self-hosted-runners/add-runners)、
[Keil 命令行构建](https://www.keil.com/support/man/docs/uv4/uv4_commandline.asp)、
[Keil 评估版限制](https://www2.keil.com/limits)。
