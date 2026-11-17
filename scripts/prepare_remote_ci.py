"""Prepare a disposable Keil project without rewriting firmware source files."""

from pathlib import Path
import re
import xml.etree.ElementTree as ET


def prepare(repo: Path) -> Path:
    root = repo / "2_remote_test/rc_endu_test"
    project = root / "Projects/MDK-ARM/CatchXBlack_Pro.uvprojx"
    tree = ET.parse(project)
    target = tree.find("./Targets/Target")
    if target is None or target.findtext("TargetName") != "Primary":
        raise RuntimeError("Expected the original Primary target")

    missing = []
    for group in target.findall("./Groups/Group"):
        files = group.find("Files")
        if files is None:
            continue
        for entry in list(files):
            relative = entry.findtext("FilePath", "").replace("\\", "/")
            path = (project.parent / relative).resolve()
            if path.is_file():
                continue
            if relative != "../../Drivers/img/ROGUE_MAX.c":
                missing.append(relative)
                continue
            # The absent image entry is stale in this snapshot. Do not invent an image
            # or remove a referenced symbol if a later source revision starts using it.
            references = [
                str(source.relative_to(root))
                for source in root.rglob("*")
                if source.suffix.lower() in (".c", ".h")
                and re.search(rb"\bROGUE_MAX\b", source.read_bytes())
            ]
            if references:
                raise RuntimeError(f"Missing ROGUE_MAX image is referenced by {references}")
            files.remove(entry)
            print("CI only: omitted absent, unreferenced image entry Drivers/img/ROGUE_MAX.c")
    if missing:
        raise RuntimeError(f"Other project inputs are missing: {missing}")

    compiler = target.find("pCCUsed")
    if compiler is None:
        raise RuntimeError("Missing compiler selection")
    print(f"CI compatibility compiler: {compiler.text} -> ARMCC 5.06 update 6 build 750")
    compiler.text = "5060750::V5.06 update 6 (build 750)::ARMCC"

    common = target.find("./TargetOption/TargetCommonOption")
    if common is None:
        raise RuntimeError("Missing target options")
    for name in ("RunUserProg1", "RunUserProg2"):
        node = common.find(f"./AfterMake/{name}")
        if node is None:
            raise RuntimeError(f"Missing AfterMake/{name}")
        node.text = "0"
    print("CI only: disabled legacy post-build steps; workflow converts AXF to application BIN")
    (root / "Output/BIN").mkdir(parents=True, exist_ok=True)
    output = project.with_name("CatchXBlack_Pro.ci.uvprojx")
    tree.write(output, encoding="utf-8", xml_declaration=True)
    print(f"Prepared {output.relative_to(repo)}")
    return output


if __name__ == "__main__":
    prepare(Path(__file__).resolve().parents[1])
