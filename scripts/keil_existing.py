"""Inspect an existing Windows Keil installation without modifying it."""

import configparser
import json
import locale
import os
from pathlib import Path
import re
import shutil
import sys
import tempfile

import keil_ci as ci


def read_tools_ini(root):
    raw = (root / "TOOLS.INI").read_bytes()
    native_encoding = locale.getencoding() if hasattr(locale, "getencoding") else (
        "mbcs" if os.name == "nt" else locale.getpreferredencoding(False))
    for encoding in ("utf-8-sig", native_encoding, "cp1252"):
        try:
            text = raw.decode(encoding)
            break
        except UnicodeDecodeError:
            continue
    else:
        raise RuntimeError("Cannot decode existing TOOLS.INI")
    config = configparser.RawConfigParser(strict=False)
    config.read_string(text)
    return config


def registry_roots():
    if os.name != "nt":
        return []
    import winreg
    roots = []
    for hive in (winreg.HKEY_LOCAL_MACHINE, winreg.HKEY_CURRENT_USER):
        for view in (winreg.KEY_WOW64_32KEY, winreg.KEY_WOW64_64KEY):
            try:
                with winreg.OpenKey(hive, r"SOFTWARE\Keil\Products\MDK", 0,
                                    winreg.KEY_READ | view) as key:
                    path = Path(winreg.QueryValueEx(key, "Path")[0])
                    roots.append(path.parent if path.name.lower() == "arm" else path)
            except OSError:
                continue
    return roots


def find_keil_root():
    explicit = os.environ.get("KEIL_INSTALL_DIR", "").strip() or os.environ.get("KEIL_ROOT", "").strip()
    if explicit:
        candidates = [Path(explicit)]
    else:
        candidates = registry_roots()
        executable = shutil.which("UV4.exe")
        if executable:
            candidates.append(Path(executable).parent.parent)
        candidates += [Path(path) for path in (r"C:\Keil_v5", r"C:\Keil", r"D:\Keil_v5", r"D:\Keil")]
    for path in candidates:
        if (path / "UV4/UV4.exe").is_file() and (path / "TOOLS.INI").is_file():
            return path.resolve()
    raise RuntimeError("Existing Keil not found. Set repository Variable KEIL_ROOT to its installation root, e.g. C:\\Keil_v5. No software was installed or changed.")


def resolve_setting(value, root, relative_to=None):
    value = value.strip().strip('"').replace("%KEIL_DIR%", str(root))
    value = os.path.expandvars(value).replace("\\", os.sep)
    path = Path(value)
    return path if path.is_absolute() else (relative_to or root) / path


def compiler_candidates(root, config):
    candidates = []
    arm = root / "ARM"
    if config.has_section("ARMADS"):
        for key, value in config.items("ARMADS"):
            if re.fullmatch(r"armccpath\d+", key, re.IGNORECASE):
                match = re.match(r'"([^"]+)"', value)
                if match:
                    candidates.append(resolve_setting(match[1], root, arm) / "bin")
        if config.has_option("ARMADS", "PATH1"):
            candidates.append(resolve_setting(config.get("ARMADS", "PATH1"), root, arm))
    candidates.append(arm / "ARMCC/bin")
    return list(dict.fromkeys(path.resolve() for path in candidates if (path / "armcc.exe").is_file()))


def compiler_tag(text):
    match = re.search(r"(\d+)\.(\d+)\s+update\s+(\d+)\s+\(build\s+(\d+)\)", text)
    if not match or tuple(map(int, match.groups()[:2])) != (5, 6):
        raise RuntimeError("This project requires ARM Compiler 5.06 (armcc); ARM Compiler 6 is not a replacement")
    major, minor, update, build = map(int, match.groups())
    number = major * 1000000 + minor * 10000 + build
    return f"{number}::V{major}.{minor:02d} update {update} (build {build})::ARMCC"


def find_pack_root(root, config):
    setting = config.get("UV2", "RTEPATH", fallback="").strip()
    candidates = [resolve_setting(setting, root)] if setting else []
    candidates += [Path(os.environ[name]) for name in ("RTEPATH", "CMSIS_PACK_ROOT") if os.environ.get(name)]
    candidates += [root / "ARM/PACK"]
    if os.environ.get("LOCALAPPDATA"):
        candidates.append(Path(os.environ["LOCALAPPDATA"]) / "Arm/Packs")
    relative = Path("Geehy/APM32F4xx_DFP/1.0.11/Geehy.APM32F4xx_DFP.pdsc")
    # If uVision has a configured pack root, do not silently select a different one.
    if setting:
        candidates = candidates[:1]
    for path in candidates:
        if (path / relative).is_file():
            return path.resolve()
    raise RuntimeError("Geehy.APM32F4xx_DFP.1.0.11 is missing from the configured Keil pack root. Install that version in Windows Keil Pack Installer; this workflow does not install or alter packs.")


def export_environment(values):
    with Path(os.environ["GITHUB_ENV"]).open("a", encoding="utf-8") as stream:
        for key, value in values.items():
            if "\n" in str(value) or "\r" in str(value):
                raise RuntimeError("Unexpected newline in tool configuration")
            stream.write(f"{key}={value}\n")


def protect_existing_license_details(config):
    values = []
    for section in config.sections():
        for key, value in config.items(section):
            if key.lower() == "flex" or re.fullmatch(r"lic\d+", key, re.IGNORECASE):
                values.append(value.strip().strip('"'))
    values += [os.environ.get(name, "") for name in ("ARMLMD_LICENSE_FILE", "LM_LICENSE_FILE")]
    values = [value for value in values if value and value not in ("0", "1")]
    for value in list(values):
        if "@" in value:
            values.extend(part.partition("@")[2] for part in value.split(";") if "@" in part)
    descriptor, name = tempfile.mkstemp(prefix="keil-log-redactions-", suffix=".json",
                                        dir=os.environ.get("RUNNER_TEMP"))
    with os.fdopen(descriptor, "w", encoding="utf-8") as stream:
        json.dump(values, stream)
    os.environ["KEIL_REDACTIONS_FILE"] = name
    export_environment({"KEIL_REDACTIONS_FILE": name})


def check_existing(root, logs):
    config = read_tools_ini(root)
    protect_existing_license_details(config)
    ci.say(f"Runner: {os.environ.get('RUNNER_NAME', 'unknown')}; existing Keil: {root}")
    ci.say("Using existing tool and license settings; no installation/configuration writes will be performed")
    available = []
    for index, directory in enumerate(compiler_candidates(root, config)):
        log = logs / f"compiler-version-{index}.txt"
        ci.run_logged([directory / "armcc.exe", "--vsn"], log, timeout=30)
        try:
            tag = compiler_tag(log.read_text(encoding="utf-8", errors="replace"))
        except RuntimeError:
            continue
        available.append((tag, directory, log))
    if not available:
        raise RuntimeError("ARM Compiler 5.06 not found among the existing Keil compiler registrations")
    # Prefer the original project version if installed; otherwise use a registered 5.06.
    available.sort(key=lambda item: not item[0].startswith("5060528::"))
    tag, directory, version_log = available[0]
    for name in ("armasm.exe", "armlink.exe", "fromelf.exe"):
        if not (directory / name).is_file():
            raise RuntimeError(f"Missing existing compiler tool: {directory / name}")
    shutil.copy2(version_log, logs / "compiler-version.txt")
    pack_root = find_pack_root(root, config)

    # A small C compilation cannot detect MDK-Lite's linker capacity limit.
    # Link >32 KiB of actual Thumb instructions using the existing license.
    with tempfile.TemporaryDirectory(prefix="keil-license-check-", dir=os.environ.get("RUNNER_TEMP")) as temp:
        probe_dir = Path(temp)
        source = probe_dir / "license-probe.s"
        source.write_text(
            "        AREA CI_LICENSE_CHECK, CODE, READONLY\n        THUMB\n"
            "        EXPORT ci_license_check\nci_license_check\n"
            + "        NOP\n" * 20000 + "        B .\n        END\n", encoding="ascii")
        obj = probe_dir / "license-probe.o"
        ci.run_logged([directory / "armasm.exe", "--cpu=Cortex-M4", "--thumb", source, "-o", obj],
                      logs / "license-probe-assemble.log", timeout=60)
        try:
            ci.run_logged([directory / "armlink.exe", "--cpu=Cortex-M4", "--ro_base=0x08010000",
                           "--entry=ci_license_check", "--no_remove", obj, "--output", probe_dir / "license-probe.axf"],
                          logs / "license-probe-link.log", timeout=60)
        except RuntimeError:
            log_text = (logs / "license-probe-link.log").read_text(encoding="utf-8", errors="replace")
            failure = ci.explain_build_failure(log_text)
            if failure:
                ci.save_failure(failure, logs)
                raise RuntimeError("Existing Windows Keil license still limits links to a small image. Run the runner as the Windows user whose Keil authorization works; inspect license-probe-link.log") from None
            raise
        if not (probe_dir / "license-probe.axf").is_file():
            raise RuntimeError("License link probe returned without producing an AXF")

    values = {"KEIL_ROOT": str(root), "KEIL_COMPILER_BIN": str(directory),
              "KEIL_ARMCC_TAG": tag, "RTEPATH": str(pack_root), "CMSIS_PACK_ROOT": str(pack_root)}
    export_environment(values)
    (logs / "existing-keil.json").write_text(json.dumps({
        **values, "runner": os.environ.get("RUNNER_NAME", "unknown"),
        "license_probe": "passed >32 KiB Thumb code link", "installation_changed": False,
    }, indent=2), encoding="utf-8")
    ci.say(f"Existing environment checked: {tag}; >32 KiB link probe passed")


def main():
    logs = Path("ci-logs").resolve()
    logs.mkdir(parents=True, exist_ok=True)
    try:
        if os.name != "nt":
            raise RuntimeError("Existing Keil inspection must run on the Windows self-hosted runner")
        check_existing(find_keil_root(), logs)
        return 0
    except (OSError, RuntimeError, configparser.Error) as error:
        ci.say(ci.redact_text(f"ERROR: {error}"))
        return 1


if __name__ == "__main__":
    sys.exit(main())
