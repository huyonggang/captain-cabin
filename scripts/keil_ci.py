"""Shared Keil CI build, logging and legacy deployment helpers.

Windows performs the actual build. Archive/configuration and watchdog helpers
can also be checked on macOS. The self-hosted workflow does not call setup().
No activation keys or license patches are used.
"""

import argparse
import configparser
import hashlib
import io
import json
import os
from pathlib import Path, PurePosixPath
import re
import shutil
import signal
import struct
import subprocess
import sys
import time
import zipfile


MDK_URL = "https://www.keil.com/files/eval/mdk525.exe"
MDK_SHA256 = "9e3d2becf10626f4d43a6da98764fe5ac0e71b745ccc379bea148899ae1dd39a"
PACK_URL = "https://global.geehy.com/uploads/tool/Geehy.APM32F4xx_DFP.1.0.11.pack"
PACK_SHA256 = "fe57a676a379f11699b3be3e956f57542c0d09134cabbeb529bc6aa135981c2f"


def say(message):
    print(message, flush=True)


def sha256(path):
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def extract_archive(archive, destination, timeout=240):
    """zipfile understands the ZIP appended to Keil's self-extracting EXE."""
    destination.mkdir(parents=True, exist_ok=True)
    started = last_report = time.monotonic()
    with zipfile.ZipFile(archive) as package:
        entries = package.infolist()
        say(f"Extracting {archive.name}: {len(entries)} entries (installer is not executed)")
        for index, entry in enumerate(entries, 1):
            relative = PurePosixPath(entry.filename.replace("\\", "/"))
            if relative.is_absolute() or ".." in relative.parts or ":" in str(relative):
                raise RuntimeError(f"Unsafe archive path: {entry.filename}")
            target = destination.joinpath(*relative.parts)
            if entry.is_dir() or entry.filename.endswith("\\"):
                target.mkdir(parents=True, exist_ok=True)
            else:
                target.parent.mkdir(parents=True, exist_ok=True)
                with package.open(entry) as source, target.open("wb") as output:
                    shutil.copyfileobj(source, output)
            elapsed = time.monotonic() - started
            if elapsed > timeout:
                raise RuntimeError(f"Extraction exceeded {timeout}s at {entry.filename}")
            if time.monotonic() - last_report >= 15:
                say(f"Extracted {index}/{len(entries)} entries, elapsed {elapsed:.0f}s")
                last_report = time.monotonic()
    say(f"Extraction completed in {time.monotonic() - started:.1f}s")


def license_settings(server, variant):
    if not server:
        return {"TOOL_VARIANT": "mdk_lite"}
    if variant not in ("mdk_pro", "mdk_std", "mdk_cm_std"):
        raise RuntimeError("KEIL_LICENSE_VARIANT must be mdk_pro, mdk_std or mdk_cm_std")
    match = re.fullmatch(r"([0-9]{1,5})@([A-Za-z0-9_.-]+)", server)
    if not match or not 1 <= int(match[1]) <= 65535:
        raise RuntimeError("KEIL_LICENSE_SERVER must contain one port@hostname address")
    return {"TOOL_VARIANT": f"{variant}_flex", "FLEX_VARIANT": variant,
            "FLEX": server, "FLEX_USE": "1"}


def redact_text(text, server=None):
    server = os.environ.get("KEIL_LICENSE_SERVER", "").strip() if server is None else server
    if server:
        # Tool diagnostics may print either the complete location or just its host.
        for value in (server, server.partition("@")[2]):
            if value:
                text = text.replace(value, "[REDACTED_LICENSE_SERVER]")
    if os.environ.get("KEIL_REDACTIONS_FILE"):
        values = json.loads(Path(os.environ["KEIL_REDACTIONS_FILE"]).read_text(encoding="utf-8"))
        for value in sorted(set(values), key=len, reverse=True):
            if value:
                text = text.replace(value, "[REDACTED_LICENSE_DETAIL]")
    return text


def redact_logs(logs, root):
    paths = list(logs.rglob("*"))
    output = root / "Output"
    if output.exists():
        paths.extend(p for p in output.iterdir() if p.suffix.lower() in (".map", ".htm"))
    for path in paths:
        if path.is_file():
            raw = path.read_bytes()
            # Also cover the UTF-16 output used by some Windows tools.
            encoding = "utf-16" if raw.startswith((b"\xff\xfe", b"\xfe\xff")) else "utf-8"
            text = raw.decode(encoding, errors="replace")
            cleaned = redact_text(text)
            if cleaned != text:
                path.write_text(cleaned, encoding=encoding)


def tools_ini_text(setup_text, keil_root, pack_root, license_server="", license_variant="mdk_pro"):
    source = configparser.RawConfigParser(strict=False)
    source.optionxform = str
    source.read_string(setup_text)
    if source.get("UV2", "TOOL_VARIANT") != "mdk_lite":
        raise RuntimeError("Unexpected vendor tool variant; expected unchanged mdk_lite evaluation mode")
    output = configparser.RawConfigParser()
    output.optionxform = str
    for section in ("UV2", "ARM", "ARMADS"):
        output[section] = dict(source.items(section))
    root = keil_root.rstrip("\\/")
    output["UV2"]["RTEPATH"] = f'"{pack_root}"'
    output["UV2"]["NAME"] = '"GitHub", "Actions"'
    output["UV2"]["ORGANIZATION"] = "Rippton"
    output["UV2"].update(license_settings(license_server, license_variant))
    for section in ("ARM", "ARMADS"):
        output[section]["PATH"] = f'"{root}\\ARM\\"'
    stream = io.StringIO()
    output.write(stream, space_around_delimiters=False)
    # Keep the vendor's ARMCCPATH0 registration and all compiler/debugger settings.
    return stream.getvalue(), source.get("REGISTRY1", "DATA0")


def install_pack(archive, pack_root, vendor, name, version):
    pack_dir = pack_root / vendor / name / version
    extract_archive(archive, pack_dir)
    pdsc = pack_dir / f"{vendor}.{name}.pdsc"
    if not pdsc.is_file():
        raise RuntimeError(f"{pdsc.name} missing after pack extraction")
    (pack_root / ".Web").mkdir(parents=True, exist_ok=True)
    shutil.copy2(pdsc, pack_root / ".Web" / pdsc.name)


def save_process_diagnostics(log_dir):
    if os.name != "nt":
        return
    script = (
        "Get-Process | Where-Object { $_.ProcessName -match "
        "'UV4|armcc|armasm|armlink|fromelf|setup|mdk|WerFault' } | "
        "Select-Object Id,ProcessName,CPU,Responding,MainWindowTitle,Path | "
        "Format-List | Out-String -Width 240"
    )
    try:
        result = subprocess.run(
            ["powershell.exe", "-NoProfile", "-NonInteractive", "-Command", script],
            capture_output=True, timeout=15,
        )
        (log_dir / "timeout-processes.txt").write_bytes(result.stdout + result.stderr)
    except (OSError, subprocess.TimeoutExpired) as error:
        say(f"Could not capture process diagnostics: {error}")


def stop_process_tree(process):
    if os.name == "nt":
        try:
            subprocess.run(
                ["taskkill.exe", "/PID", str(process.pid), "/T", "/F"],
                stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, timeout=15,
            )
        except (OSError, subprocess.TimeoutExpired):
            pass
    else:
        try:
            os.killpg(process.pid, signal.SIGKILL)
        except ProcessLookupError:
            pass
    if process.poll() is None:
        process.kill()
    process.wait(timeout=10)


def run_logged(command, log, timeout, cwd=None, watch_log=None, allowed=(0,), heartbeat=15):
    """Bound every executable; stream its output or uVision's separate build log."""
    log.parent.mkdir(parents=True, exist_ok=True)
    watched = watch_log or log
    offset = 0

    def emit_output():
        nonlocal offset
        try:
            with watched.open("rb") as stream:
                if watched.stat().st_size < offset:
                    offset = 0
                stream.seek(offset)
                data = stream.read()
                offset = stream.tell()
            if data:
                print(redact_text(data.decode("utf-8-sig", errors="replace")), end="", flush=True)
        except (FileNotFoundError, PermissionError):
            # uVision may not have created the log yet, or may briefly hold an
            # exclusive Windows file handle. Log access must not abort compilation.
            pass

    name = Path(command[0]).name
    say(f"Starting {name}; timeout {timeout}s; log: {watched}")
    started = last_report = time.monotonic()
    with log.open("wb") as output:
        process = subprocess.Popen(
            [str(part) for part in command], cwd=cwd,
            stdin=subprocess.DEVNULL, stdout=output, stderr=subprocess.STDOUT,
            start_new_session=(os.name != "nt"),
        )
        try:
            while process.poll() is None:
                elapsed = time.monotonic() - started
                if elapsed >= timeout:
                    save_process_diagnostics(log.parent)
                    stop_process_tree(process)
                    message = f"{name} timed out after {timeout}s; process tree terminated"
                    output.write(("\n" + message + "\n").encode())
                    output.flush()
                    emit_output()
                    raise RuntimeError(message)
                if time.monotonic() - last_report >= heartbeat:
                    emit_output()
                    say(f"{name} still running: {elapsed:.0f}s elapsed (limit {timeout}s)")
                    last_report = time.monotonic()
                time.sleep(min(0.25, heartbeat))
        except BaseException:
            if process.poll() is None:
                stop_process_tree(process)
            raise
    emit_output()
    say(f"{name} exited with code {process.returncode} in {time.monotonic() - started:.1f}s")
    if process.returncode not in allowed:
        raise RuntimeError(f"{name} failed with exit code {process.returncode}; inspect {watched}")
    return process.returncode


def download(url, path, expected_hash, logs):
    run_logged(
        ["curl.exe", "--fail", "--location", "--retry", "2", "--retry-max-time", "600",
         "--connect-timeout", "30", "--max-time", "600", "--speed-limit", "1024",
         "--speed-time", "60", "--output", path, url],
        logs / f"download-{path.name}.log", timeout=660,
    )
    actual = sha256(path)
    say(f"SHA256 {path.name}: {actual}")
    if actual != expected_hash:
        raise RuntimeError(f"SHA256 mismatch for {path.name}; expected {expected_hash}, got {actual}")


def setup(keil, logs):
    if os.name != "nt":
        raise RuntimeError("Actual Keil deployment requires Windows")
    import winreg

    pack_root = keil / "ARM/PACK"
    temporary = Path(os.environ["RUNNER_TEMP"])
    archive = temporary / "mdk525.exe"
    download(MDK_URL, archive, MDK_SHA256, logs)
    extract_archive(archive, keil)
    setup_text = (keil / "SETUP.INI").read_text(encoding="cp1252")
    server = os.environ.get("KEIL_LICENSE_SERVER", "").strip()
    variant = os.environ.get("KEIL_LICENSE_VARIANT", "mdk_pro").strip()
    settings = license_settings(server, variant)
    text, version = tools_ini_text(setup_text, str(keil), str(pack_root), server, variant)
    (keil / "TOOLS.INI").write_text(text, encoding="cp1252")
    (logs / "keil-tools.ini").write_text(redact_text(text), encoding="cp1252")

    # SETUP.INI [REGISTRY1], matching the vendor's documented 32-bit MDK product key.
    key_name = r"SOFTWARE\Keil\Products\MDK"
    with winreg.CreateKeyEx(winreg.HKEY_LOCAL_MACHINE, key_name, 0,
                            winreg.KEY_WRITE | winreg.KEY_WOW64_32KEY) as key:
        winreg.SetValueEx(key, "Path", 0, winreg.REG_SZ, str(keil / "ARM"))
        winreg.SetValueEx(key, "Version", 0, winreg.REG_SZ, version)
    (logs / "deployment.json").write_text(json.dumps({
        "method": "extract vendor ZIP; no installer, drivers or activation executed",
        "product_key_32bit": key_name, "product_path": str(keil / "ARM"),
        "version": version, "tool_variant": settings["TOOL_VARIANT"], "installer_sha256": MDK_SHA256,
        "license_source": "KEIL_LICENSE_SERVER secret" if server else "unlicensed evaluation",
    }, indent=2))

    # The EXE carries these base packs as nested archives. The GUI installer
    # normally expands them; extracting only the outer ZIP leaves them inactive.
    for vendor, name, version in (("ARM", "CMSIS", "5.3.0"), ("Keil", "ARM_Compiler", "1.4.0")):
        bundled = pack_root / ".Download" / f"{vendor}.{name}.{version}.pack"
        install_pack(bundled, pack_root, vendor, name, version)

    pack = temporary / "Geehy.APM32F4xx_DFP.1.0.11.pack"
    download(PACK_URL, pack, PACK_SHA256, logs)
    install_pack(pack, pack_root, "Geehy", "APM32F4xx_DFP", "1.0.11")

    for relative in ("UV4/UV4.exe", "ARM/ARMCC/bin/armcc.exe", "ARM/ARMCC/bin/fromelf.exe"):
        if not (keil / relative).is_file():
            raise RuntimeError(f"Missing extracted tool: {relative}")
    compiler = keil / "ARM/ARMCC/bin/armcc.exe"
    version_log = logs / "compiler-version.txt"
    run_logged([compiler, "--vsn"], version_log, timeout=30)
    actual_version = version_log.read_text(errors="replace")
    if "5.06" not in actual_version or "750" not in actual_version:
        raise RuntimeError("Expected ARM Compiler 5.06 update 6 build 750")
    probe = temporary / "keil-probe.c"
    probe.write_text("int main(void) { return 0; }\n", encoding="ascii")
    run_logged([compiler, "--cpu=Cortex-M4", "-c", probe, "-o", temporary / "keil-probe.o"],
               logs / "compiler-probe.log", timeout=60)
    with Path(os.environ["GITHUB_ENV"]).open("a", encoding="utf-8") as output:
        output.write(f"RTEPATH={pack_root}\nCMSIS_PACK_ROOT={pack_root}\n")
    with Path(os.environ["GITHUB_PATH"]).open("a", encoding="utf-8") as output:
        output.write(f"{keil / 'ARM/ARMCC/bin'}\n")
    say(f"Keil deployment and compiler probe completed. Tool variant: {settings['TOOL_VARIANT']}.")


def validate_bin(path):
    data = path.read_bytes()
    if not 8 <= len(data) <= 0xF0000:
        raise RuntimeError("Application BIN size is outside the 960 KiB application partition")
    reset = struct.unpack_from("<I", data, 4)[0]
    if reset & 1 == 0 or not 0x08010000 <= reset < 0x08100000:
        raise RuntimeError("BIN reset vector is outside the application flash region")


def explain_build_failure(text):
    match = re.search(r"L6050U:.*?\(([0-9]+) bytes\)", text)
    if match:
        size = int(match[1])
        return {
            "kind": "keil_license_code_size_limit", "code_size_bytes": size,
            "message": f"Keil L6050U: the linker reports {size} bytes of code, exceeding the current license limit.",
            "reason_zh": f"Keil 授权容量限制：链接器报告代码大小为 {size} 字节，超过当前授权允许的大小。",
            "solution_zh": "配置有效的 Keil FlexNet 浮动授权，或使用已有授权的 Windows 构建机；没有授权则需迁移到 GCC。增加 Flash 配置或超时时间不能解除此限制。",
        }
    return None


def save_failure(failure, logs):
    (logs / "failure.json").write_text(json.dumps(failure, ensure_ascii=False, indent=2), encoding="utf-8")
    (logs / "failure.txt").write_text(failure["reason_zh"] + "\n" + failure["solution_zh"] + "\n", encoding="utf-8")
    if os.environ.get("GITHUB_STEP_SUMMARY"):
        with Path(os.environ["GITHUB_STEP_SUMMARY"]).open("a", encoding="utf-8") as summary:
            summary.write("\n### Build failure reason\n" + failure["message"] + "\n")


def build(keil, root, logs):
    project_dir = root / "Projects/MDK-ARM"
    build_log = logs / "keil-build.log"
    try:
        code = run_logged(
            [keil / "UV4/UV4.exe", "-r", "CatchXBlack_Pro.ci.uvprojx", "-t", "Primary",
             "-j0", "-o", build_log],
            logs / "keil-launch.log", timeout=480, cwd=project_dir, watch_log=build_log,
            allowed=(0, 1),
        )
    except RuntimeError:
        failure = explain_build_failure(build_log.read_text(errors="replace") if build_log.exists() else "")
        if failure:
            save_failure(failure, logs)
            raise RuntimeError(failure["message"]) from None
        raise
    (logs / "build-result.txt").write_text(f"UV4 exit code: {code}\n")
    axf = root / "Output/apm32f407.axf"
    if not axf.is_file():
        raise RuntimeError("Keil returned without producing the application AXF")
    binary = root / "Output/BIN/Remote_V1.01.42_ENDU_TEST_app_0x08010000.bin"
    compiler_bin = Path(os.environ.get("KEIL_COMPILER_BIN", str(keil / "ARM/ARMCC/bin")))
    run_logged([compiler_bin / "fromelf.exe", "--bin", "--output", binary, axf],
               logs / "fromelf.log", timeout=30)
    validate_bin(binary)
    (logs / "firmware-sha256.txt").write_text(f"{sha256(binary)}  {binary.name}\n")
    say(f"Validated application BIN: {binary}, base 0x08010000, {binary.stat().st_size} bytes")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("stage", choices=("setup", "build", "redact"))
    parser.add_argument("--keil-root", type=Path, default=Path(os.environ.get("KEIL_ROOT", r"C:\Keil_v5")))
    parser.add_argument("--remote-root", type=Path, default=Path("2_remote_test/rc_endu_test"))
    parser.add_argument("--log-dir", type=Path, default=Path("ci-logs"))
    args = parser.parse_args()
    logs = args.log_dir.resolve()
    logs.mkdir(parents=True, exist_ok=True)
    if args.stage == "redact":
        redact_logs(logs, args.remote_root.resolve())
        return 0
    # Persist setup output as well as individual process logs, without a GUI transcript.
    class Tee:
        def __init__(self, console, file):
            self.console, self.file = console, file
        def write(self, text):
            self.console.write(text)
            self.file.write(text)
        def flush(self):
            self.console.flush()
            self.file.flush()
    original = sys.stdout
    with (logs / f"{args.stage}.log").open("w", encoding="utf-8") as stream:
        sys.stdout = Tee(original, stream)
        try:
            server = os.environ.get("KEIL_LICENSE_SERVER", "").strip()
            if server and os.environ.get("KEIL_USE_EXISTING") != "1":
                settings = license_settings(server, os.environ.get("KEIL_LICENSE_VARIANT", "mdk_pro").strip())
                os.environ["ARMLMD_LICENSE_FILE"] = server
                os.environ["ARM_TOOL_VARIANT"] = settings["TOOL_VARIANT"]
            if args.stage == "setup":
                setup(args.keil_root.resolve(), logs)
            else:
                build(args.keil_root.resolve(), args.remote_root.resolve(), logs)
        except (OSError, RuntimeError, zipfile.BadZipFile, configparser.Error) as error:
            say(redact_text(f"ERROR: {error}"))
            return 1
        finally:
            sys.stdout = original
    return 0


if __name__ == "__main__":
    sys.exit(main())
