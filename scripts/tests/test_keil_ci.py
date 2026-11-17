"""Run with: python3 -B -m unittest discover -s scripts/tests -v"""

import configparser
import importlib.util
import io
import json
from contextlib import redirect_stdout
from pathlib import Path
import struct
import sys
import tempfile
import time
import unittest
from unittest.mock import patch
import zipfile

spec = importlib.util.spec_from_file_location("keil_ci", Path(__file__).resolve().parents[1] / "keil_ci.py")
ci = importlib.util.module_from_spec(spec)
spec.loader.exec_module(ci)


class KeilCITests(unittest.TestCase):
    def test_recognizes_real_license_failure_and_does_not_misclassify_memory_overflow(self):
        # Exact error from run 44043719956, independent of downloaded artifacts.
        text = (
            "apm32f407.axf: error: L6050U: The code size of this image (237820 bytes) "
            "exceeds the maximum allowed for this version of the linker."
        )
        failure = ci.explain_build_failure(text)
        self.assertEqual(failure["kind"], "keil_license_code_size_limit")
        self.assertEqual(failure["code_size_bytes"], 237820)
        self.assertIsNone(ci.explain_build_failure("L6406E: No space in execution regions"))

    def test_build_saves_actionable_reason_when_linker_hits_license_limit(self):
        with tempfile.TemporaryDirectory() as temp:
            logs = Path(temp) / "logs"
            logs.mkdir()
            (logs / "keil-build.log").write_text(
                "L6050U: The code size of this image (237820 bytes) exceeds the maximum allowed"
            )
            with patch.object(ci, "run_logged", side_effect=RuntimeError("exit code 2")), \
                    self.assertRaisesRegex(RuntimeError, "Keil L6050U"):
                ci.build(Path(temp), Path(temp), logs)
            failure = json.loads((logs / "failure.json").read_text(encoding="utf-8"))
            self.assertEqual(failure["code_size_bytes"], 237820)
            self.assertIn("授权容量限制", failure["reason_zh"])
            self.assertIn("GCC", (logs / "failure.txt").read_text(encoding="utf-8"))

    def test_floating_license_configuration_requires_real_server_address(self):
        settings = ci.license_settings("8224@license.example.internal", "mdk_pro")
        self.assertEqual(settings["TOOL_VARIANT"], "mdk_pro_flex")
        self.assertEqual(settings["FLEX_USE"], "1")
        for server in ("8224@server\nLIC0=invalid", "70000@server", "not-a-server"):
            with self.assertRaises(RuntimeError):
                ci.license_settings(server, "mdk_pro")
        with self.assertRaises(RuntimeError):
            ci.license_settings("8224@server", "invented_variant")

    def test_server_address_is_redacted_from_uploaded_logs(self):
        server = "8224@license.example.internal"
        with tempfile.TemporaryDirectory() as temp, patch.dict(ci.os.environ, {"KEIL_LICENSE_SERVER": server}):
            root = Path(temp)
            logs = root / "logs"
            logs.mkdir()
            log = logs / "probe.log"
            log.write_text(f"License path: {server}; host license.example.internal", encoding="utf-8")
            output = root / "Output"
            output.mkdir()
            html = output / "build.htm"
            html.write_text(f"License path: {server}", encoding="utf-16")
            ci.redact_logs(logs, root)
            for path, encoding in ((log, "utf-8"), (html, "utf-16")):
                self.assertNotIn("license.example.internal", path.read_text(encoding=encoding))
                self.assertIn("REDACTED_LICENSE_SERVER", path.read_text(encoding=encoding))

    def test_preserves_vendor_compiler_registration_and_evaluation(self):
        text = '''[UV2]
TOOL_VARIANT=mdk_lite
RTEPATH="%KEIL_DIR%\\ARM\\PACK"
[ARM]
VERSION=5.25
[ARMADS]
PATH1=".\\ARMCC\\bin\\"
ARMCCPATH0="ARMCC" ("5.06 update 6 (build 750)")
[REGISTRY1]
DATA0=V5.25
'''
        actual, version = ci.tools_ini_text(text, r"C:\Keil_v5", r"C:\Keil_v5\ARM\PACK")
        config = configparser.RawConfigParser()
        config.read_string(actual)
        self.assertEqual(version, "V5.25")
        self.assertEqual(config["UV2"]["TOOL_VARIANT"], "mdk_lite")
        self.assertEqual(config["ARMADS"]["ARMCCPATH0"], '"ARMCC" ("5.06 update 6 (build 750)")')
        self.assertEqual(config["ARMADS"]["PATH"], '"C:\\Keil_v5\\ARM\\"')
        self.assertEqual(config["UV2"]["RTEPATH"], '"C:\\Keil_v5\\ARM\\PACK"')
        self.assertNotIn("%KEIL_DIR%", actual)
        self.assertNotIn("LIC0", actual)
        self.assertNotIn("FLEX_USE", actual)
        licensed, _ = ci.tools_ini_text(text, r"C:\Keil_v5", r"C:\Keil_v5\ARM\PACK",
                                       "8224@license.example.internal", "mdk_std")
        config.read_string(licensed)
        self.assertEqual(config["UV2"]["TOOL_VARIANT"], "mdk_std_flex")
        self.assertEqual(config["UV2"]["FLEX_VARIANT"], "mdk_std")
        self.assertEqual(config["UV2"]["FLEX"], "8224@license.example.internal")

    def test_extracts_sfx_with_windows_paths(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            archive = root / "vendor.exe"
            archive.write_bytes(b"MZ vendor self-extractor prefix")
            with zipfile.ZipFile(archive, "a") as package:
                package.writestr("UV4/UV4.exe", b"test tool")
                package.writestr(r"ARM\ARMCC\bin\armcc.exe", b"test compiler")
            with redirect_stdout(io.StringIO()):
                ci.extract_archive(archive, root / "extracted")
            self.assertEqual((root / "extracted/ARM/ARMCC/bin/armcc.exe").read_bytes(), b"test compiler")

    def test_rejects_archive_traversal(self):
        with tempfile.TemporaryDirectory() as temp:
            root = Path(temp)
            archive = root / "bad.zip"
            with zipfile.ZipFile(archive, "w") as package:
                package.writestr("../outside", b"bad")
            with self.assertRaisesRegex(RuntimeError, "Unsafe archive"), redirect_stdout(io.StringIO()):
                ci.extract_archive(archive, root / "out")
            self.assertFalse((root / "outside").exists())

    def test_hung_tool_is_killed_and_logged(self):
        with tempfile.TemporaryDirectory() as temp:
            log = Path(temp) / "process.log"
            started = time.monotonic()
            with self.assertRaisesRegex(RuntimeError, "timed out"), redirect_stdout(io.StringIO()), \
                    patch.object(ci, "save_process_diagnostics"):
                ci.run_logged([sys.executable, "-c", "import time; time.sleep(30)"],
                              log, timeout=0.15, heartbeat=0.05)
            self.assertLess(time.monotonic() - started, 5)
            self.assertIn("timed out", log.read_text())

    def test_nonzero_tool_result_is_failure(self):
        with tempfile.TemporaryDirectory() as temp:
            with self.assertRaisesRegex(RuntimeError, "exit code 2"), redirect_stdout(io.StringIO()):
                ci.run_logged([sys.executable, "-c", "print('link error'); raise SystemExit(2)"],
                              Path(temp) / "process.log", timeout=3)

    def test_binary_bounds_and_reset_vector(self):
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp) / "app.bin"
            path.write_bytes(struct.pack("<II", 0x20020000, 0x08010101))
            ci.validate_bin(path)
            path.write_bytes(struct.pack("<II", 0x20020000, 0x08000101))
            with self.assertRaisesRegex(RuntimeError, "reset vector"):
                ci.validate_bin(path)
            path.write_bytes(b"x" * (0xF0000 + 1))
            with self.assertRaisesRegex(RuntimeError, "960 KiB"):
                ci.validate_bin(path)


if __name__ == "__main__":
    unittest.main()
