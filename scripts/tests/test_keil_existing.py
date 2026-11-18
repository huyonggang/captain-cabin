"""Regression checks for read-only use of an existing Keil installation."""

from contextlib import redirect_stdout
import importlib.util
import io
import json
import os
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

SCRIPTS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(SCRIPTS))
import keil_existing as existing
sys.path.pop(0)


class ExistingKeilTests(unittest.TestCase):
    def make_installation(self, base):
        root = base / "Keil"
        (root / "UV4").mkdir(parents=True)
        (root / "UV4/UV4.exe").write_bytes(b"fixture")
        directory = root / "ARM/ARMCC_custom/bin"
        directory.mkdir(parents=True)
        for name in ("armcc.exe", "armasm.exe", "armlink.exe", "fromelf.exe"):
            (directory / name).write_bytes(b"fixture")
        (root / "TOOLS.INI").write_text(
            '[UV2]\nTOOL_VARIANT=mdk_pro\nLIC0=fixture-node-locked-license\n'
            'RTEPATH="%KEIL_DIR%\\ARM\\PACK"\n[ARMADS]\n'
            'ARMCCPATH0=".\\ARMCC_custom" ("5.06 update 5 (build 528)")\n', encoding="utf-8")
        pdsc = root / "ARM/PACK/Geehy/APM32F4xx_DFP/1.0.11/Geehy.APM32F4xx_DFP.pdsc"
        pdsc.parent.mkdir(parents=True)
        pdsc.write_text("<package/>", encoding="utf-8")
        return root, directory

    def test_parse_original_and_compatible_versions(self):
        for update, build in ((5, 528), (6, 750), (7, 960)):
            tag = existing.compiler_tag(f"Component: ARM Compiler 5.06 update {update} (build {build})")
            self.assertEqual(tag, f"{5060000 + build}::V5.06 update {update} (build {build})::ARMCC")
        with self.assertRaisesRegex(RuntimeError, "requires ARM Compiler 5"):
            existing.compiler_tag("Component: ARM Compiler 6.18")

    def test_honors_explicit_root_instead_of_silently_falling_back(self):
        with tempfile.TemporaryDirectory() as temp:
            root, _ = self.make_installation(Path(temp))
            with patch.dict(os.environ, {"KEIL_INSTALL_DIR": str(root)}):
                self.assertEqual(existing.find_keil_root(), root.resolve())
            with patch.dict(os.environ, {"KEIL_INSTALL_DIR": str(root / "missing")}):
                with self.assertRaisesRegex(RuntimeError, "Existing Keil not found"):
                    existing.find_keil_root()

    def test_uses_custom_registered_compiler_and_configured_pack_root(self):
        with tempfile.TemporaryDirectory() as temp:
            root, directory = self.make_installation(Path(temp))
            config = existing.read_tools_ini(root)
            self.assertEqual(existing.compiler_candidates(root, config), [directory.resolve()])
            self.assertEqual(existing.find_pack_root(root, config), (root / "ARM/PACK").resolve())
            config.set("UV2", "RTEPATH", str(root / "missing-packs"))
            with self.assertRaisesRegex(RuntimeError, "configured Keil pack root"):
                existing.find_pack_root(root, config)

    def test_preflight_never_changes_installation_and_checks_large_link(self):
        with tempfile.TemporaryDirectory() as temp:
            base = Path(temp)
            root, directory = self.make_installation(base)
            before = {p.relative_to(root): p.read_bytes() for p in root.rglob("*") if p.is_file()}
            logs = base / "logs"
            logs.mkdir()
            env = {"RUNNER_TEMP": str(base), "GITHUB_ENV": str(base / "github.env"), "RUNNER_NAME": "PAILIKEN"}
            commands = []

            def run(command, log, **kwargs):
                commands.append(command)
                if str(command[0]).endswith("armcc.exe"):
                    log.write_text("Component: ARM Compiler 5.06 update 5 (build 528)", encoding="utf-8")
                elif str(command[0]).endswith("armlink.exe"):
                    self.assertIn("--no_remove", command)
                    Path(command[-1]).write_bytes(b"linked test fixture")
                    log.write_text("link succeeded", encoding="utf-8")
                else:
                    source = next(Path(x) for x in command if str(x).endswith(".s"))
                    self.assertEqual(source.read_text(encoding="ascii").count("        NOP\n"), 20000)
                    log.write_text("assembly succeeded", encoding="utf-8")
                return 0

            with patch.dict(os.environ, env), patch.object(existing.ci, "run_logged", side_effect=run), \
                    patch.object(existing.ci, "setup", side_effect=AssertionError("must not deploy")), \
                    redirect_stdout(io.StringIO()):
                existing.check_existing(root, logs)
                redactions = json.loads(Path(os.environ["KEIL_REDACTIONS_FILE"]).read_text(encoding="utf-8"))
                self.assertIn("fixture-node-locked-license", redactions)
                self.assertNotIn("fixture-node-locked-license", (logs / "existing-keil.json").read_text(encoding="utf-8"))
            self.assertEqual(before, {p.relative_to(root): p.read_bytes() for p in root.rglob("*") if p.is_file()})
            exported = (base / "github.env").read_text(encoding="utf-8")
            self.assertIn("KEIL_ARMCC_TAG=5060528::", exported)
            self.assertIn(f"KEIL_COMPILER_BIN={directory.resolve()}", exported)
            self.assertEqual(len(commands), 3)

    def test_limited_existing_license_stops_before_firmware_build(self):
        with tempfile.TemporaryDirectory() as temp:
            base = Path(temp)
            root, _ = self.make_installation(base)
            original = (root / "TOOLS.INI").read_bytes()
            logs = base / "logs"
            logs.mkdir()

            def run(command, log, **kwargs):
                if str(command[0]).endswith("armcc.exe"):
                    log.write_text("ARM Compiler 5.06 update 5 (build 528)", encoding="utf-8")
                elif str(command[0]).endswith("armlink.exe"):
                    log.write_text("L6050U: The code size of this image (40002 bytes) exceeds the maximum allowed", encoding="utf-8")
                    raise RuntimeError("link failed")
                return 0

            with patch.dict(os.environ, {"RUNNER_TEMP": str(base), "GITHUB_ENV": str(base / "env"),
                                        "GITHUB_STEP_SUMMARY": str(base / "summary")}), \
                    patch.object(existing.ci, "run_logged", side_effect=run), redirect_stdout(io.StringIO()), \
                    self.assertRaisesRegex(RuntimeError, "Existing Windows Keil license still limits"):
                existing.check_existing(root, logs)
            self.assertEqual((root / "TOOLS.INI").read_bytes(), original)
            self.assertTrue((logs / "failure.json").is_file())
            self.assertNotIn("KEIL_ARMCC_TAG", (base / "env").read_text(encoding="utf-8"))

    def test_prepare_project_uses_detected_compiler_without_changing_original(self):
        spec = importlib.util.spec_from_file_location("prepare_fixture", SCRIPTS / "prepare_remote_ci.py")
        prepare = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(prepare)
        with tempfile.TemporaryDirectory() as temp:
            base = Path(temp)
            project = base / "2_remote_test/rc_endu_test/Projects/MDK-ARM/CatchXBlack_Pro.uvprojx"
            project.parent.mkdir(parents=True)
            original = ('<Project><Targets><Target><TargetName>Primary</TargetName><pCCUsed>original</pCCUsed>'
                        '<TargetOption><TargetCommonOption><AfterMake><RunUserProg1>1</RunUserProg1>'
                        '<RunUserProg2>1</RunUserProg2></AfterMake></TargetCommonOption></TargetOption>'
                        '</Target></Targets></Project>')
            project.write_text(original, encoding="utf-8")
            with patch.dict(os.environ, {"KEIL_ARMCC_TAG": "5060528::V5.06 update 5 (build 528)::ARMCC"}), \
                    redirect_stdout(io.StringIO()):
                result = prepare.prepare(base)
            self.assertIn("5060528::V5.06 update 5", result.read_text(encoding="utf-8"))
            self.assertEqual(project.read_text(encoding="utf-8"), original)


if __name__ == "__main__":
    unittest.main()
