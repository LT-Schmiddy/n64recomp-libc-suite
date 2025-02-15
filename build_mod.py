import pathlib, subprocess, os, shutil, tomllib, zipfile
from pathlib import Path
import build_n64recomp_tools as bnt

USING_ASSETS_ARCHIVE = True

project_root = pathlib.Path(__file__).parent

# mod_data = tomllib.loads(project_root.joinpath("mod.toml").read_text())
# mod_manifest_data = mod_data["manifest"]
# # print(mod_data)
# build_dir = project_root.joinpath(f"build")
# build_nrm_file = build_dir.joinpath(f"{mod_data['inputs']['mod_filename']}.nrm")

# runtime_mods_dir = project_root.joinpath("runtime/mods")
# runtime_nrm_file = runtime_mods_dir.joinpath(f"{mod_data['inputs']['mod_filename']}.nrm")

assets_archive_path = project_root.joinpath("assets_archive.zip")
assets_extract_path = project_root.joinpath("assets_extracted/assets")

def build_elf(makefile_path: Path):
    make_run = subprocess.run(
        [
            bnt.deps["make"],
            "-f",
            str(makefile_path)
        ],
        cwd=pathlib.Path(__file__).parent
    )
    if make_run.returncode != 0:
        raise RuntimeError("Make failed to build mod binaries.")

def build_mod_toml(toml_path: Path):
    RecompModTool_run = subprocess.run(
        [
            bnt.get_RecompModTool_path(),
            str(toml_path),
            "build"
        ],
        cwd=pathlib.Path(__file__).parent
    )
    if RecompModTool_run.returncode != 0:
        raise RuntimeError("RecompModTool failed to build mod.")

    
def run_build():          
    if not bnt.build_dir.exists():
        print("N64Recomp tools not built. Building now...")
        bnt.rebuild_tools();

    build_elf(Path("./Makefile_ctype"))
    build_mod_toml(Path("./tomls/mm/ctype.toml"))

    # Copying files for debugging:
    # os.makedirs(runtime_mods_dir, exist_ok=True)
    # shutil.copy(build_nrm_file, runtime_nrm_file)

if __name__ == '__main__':
    run_build()