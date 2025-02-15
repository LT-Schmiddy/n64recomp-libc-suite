import pathlib, subprocess, os, shutil, tomllib, zipfile
from pathlib import Path
import build_n64recomp_tools as bnt

class ModBuilder:
    
    project_root: Path
    makefiles_run: set[Path]
    
    
    def __init__(self, project_root: Path):
        self.project_root = project_root
        self.makefiles_run: set[Path] = set()
        
    
    def build_elf(self, makefile_path: Path):
        make_run = subprocess.run(
            [
                bnt.deps["make"],
                "-f",
                str(makefile_path)
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
        build_dir = toml_path.parent.joinpath(mod_data['N64Recomp_libc']['Makefile_build_dir']).resolve()
        build_nrm_file = build_dir.joinpath(f"{mod_data['inputs']['mod_filename']}.nrm")

        makefile_path = toml_path.parent.joinpath(mod_data['N64Recomp_libc']['Makefile']).resolve()
        if makefile_path in self.makefiles_run:
            print(f"'{makefile_path.name}' was already built.")
        else:
            self.build_elf(makefile_path)
            self.makefiles_run.add(makefile_path)
        
        out_dir = toml_path.parent.joinpath(mod_data['N64Recomp_libc']['out_dir']).resolve()
        os.makedirs(out_dir, exist_ok=True)
        
        self.run_RecompModTool(toml_path, out_dir)
        
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