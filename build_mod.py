import pathlib, subprocess, os, shutil, tomllib, zipfile, json
from pathlib import Path
import build_n64recomp_tools as bnt
import build_submodule_toml_gen as bstg

BUILD_DIR_NAME = "build"
OUT_DIR_NAME = "out"
RUNTIME_DIR_NAME = "runtime"

class ModBuilder:
    
    project_root: Path
    submodules_built: set[str]
    
    def __init__(self, project_root: Path):
        self.project_root = project_root
        self.submodules_built = set()
        
    
    def build_elf(self, submodule: str, makefile_path: Path = None):
        make_run = subprocess.run(
            [
                bnt.deps["make"],
                "-f",
                str(makefile_path),
                f"SUBMODULE={submodule}"
            ],
            cwd=self.project_root
        )
        if make_run.returncode != 0:
            raise RuntimeError("Make failed to build mod binaries.")


    def run_RecompModTool(self, toml_path: Path, out_path: Path):
        RecompModTool_run = subprocess.run(
            [
                bnt.get_RecompModTool_path(),
                str(toml_path),
                str(out_path)
            ],
            cwd=self.project_root
        )
        if RecompModTool_run.returncode != 0:
            raise RuntimeError("RecompModTool failed to build mod.")


    def build_toml(self, toml_path: Path):
        if isinstance(toml_path, str):
            toml_path = Path(toml_path)
            
        mod_data = tomllib.loads(toml_path.read_text())
        submodule = mod_data['N64Recomp_libc']['submodule']
        
        # Handling Defaults:
        if "Makefile" in mod_data['N64Recomp_libc']:
            makefile_path = toml_path.parent.joinpath(mod_data['N64Recomp_libc']['Makefile']).resolve()
        else:
            # DEFAULT
            makefile_path = self.project_root.joinpath("Makefile")
            
        if "build_dir" in mod_data['N64Recomp_libc']:
            build_dir = toml_path.parent.joinpath(mod_data['N64Recomp_libc']['build_dir']).resolve()
        else:
            # DEFAULT
            build_dir = self.project_root.joinpath(f"{BUILD_DIR_NAME}/{submodule}")
        
        if "output_dir" in mod_data['N64Recomp_libc']:
            output_dir = toml_path.parent.joinpath(mod_data['N64Recomp_libc']['output_dir']).resolve()
        else:
            # DEFAULT
            output_dir = self.project_root.joinpath(f"{OUT_DIR_NAME}/{mod_data['manifest']['game_id']}/{submodule}")

        nrm_file = output_dir.joinpath(f"{mod_data['inputs']['mod_filename']}.nrm")

        if submodule in self.submodules_built:
            print(f"'{makefile_path.name}' was already built.")
        else:
            self.build_elf(submodule, makefile_path)
            self.submodules_built.add(submodule)
        
        os.makedirs(output_dir, exist_ok=True)
        self.run_RecompModTool(toml_path, output_dir)
        
        # Copy to runtime dir:
        print(f"Copying '{nrm_file.name}' to runtime dir...")
        runtime_mods_dir = self.project_root.joinpath(RUNTIME_DIR_NAME).joinpath("mods")
        os.makedirs(runtime_mods_dir, exist_ok=True)
        shutil.copy(nrm_file, runtime_mods_dir.joinpath(nrm_file.name))
        
    def run_build(self, tomls: list[Path]):          
        if not bnt.build_dir.exists():
            print("N64Recomp tools not built. Building now...")
            bnt.rebuild_tools();
        
        for i in tomls:
            self.build_toml(i)
        
            
    def run_build_directory(self, root: list[Path]):
        tomls_found = []
              
        for dirpath, dirnames, filenames in os.walk(root):
            directory = Path(dirpath)
            for filename in filenames:
                file = directory.joinpath(filename)
                if file.suffix == ".toml":
                    print(f"Found mod toml at '{file}'...")
                tomls_found.append(file)
        
        self.run_build(tomls_found)
                

if __name__ == '__main__':
    proot = Path(__file__).parent
    
    # Regenerating TOML Files:
    # subgen = bstg.SubmoduleGenerator(proot, proot.joinpath(bstg.TOML_DIR_NAME))
    # submodule_config = json.loads(proot.joinpath(bstg.SUBMODULE_CONFIG_NAME).read_text())
    # tomls = subgen.generate_from_config_dict(submodule_config)
    
    # Building Submodules:
    builder = ModBuilder(proot)
    # builder.run_build(tomls)
    builder.run_build(["combined.toml"])
    
    print("BUILD COMPLETE!")