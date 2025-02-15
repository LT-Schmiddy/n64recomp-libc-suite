import pathlib, subprocess, os, shutil, tomllib, zipfile
from pathlib import Path
import build_n64recomp_tools as bnt

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
        build_dir = toml_path.parent.joinpath(mod_data['N64Recomp_libc']['build_dir']).resolve()
        build_nrm_filename = build_dir.joinpath(f"{mod_data['inputs']['mod_filename']}.nrm")

        submodule = mod_data['N64Recomp_libc']['submodule']
        makefile_path = toml_path.parent.joinpath(mod_data['N64Recomp_libc']['Makefile']).resolve()
        
        if submodule in self.submodules_built:
            print(f"'{makefile_path.name}' was already built.")
        else:
            self.build_elf(submodule, makefile_path)
            self.submodules_built.add(submodule)
        
        output_dir = toml_path.parent.joinpath(mod_data['N64Recomp_libc']['output_dir']).resolve()
        os.makedirs(output_dir, exist_ok=True)
        
        self.run_RecompModTool(toml_path, output_dir)
        
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
    builder = ModBuilder(proot)
    builder.run_build_directory(proot.joinpath("./tomls"))