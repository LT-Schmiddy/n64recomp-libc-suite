import textwrap, pathlib, json, os
from pathlib import Path

import build_toml_templates as btt

TOML_DIR_NAME = "generated_tomls"
SUBMODULE_CONFIG_NAME = "submodules.json"
RECOMP_LIBC_PREFIX = "recomp_libc_"
BUILD_ROOT_NAME = "build"

class SubmoduleGenerator:    
    project_root: Path
    build_root: Path
    tomls_root: Path
    def __init__(self, project_root: Path, build_root: Path, tomls_root: Path):
        self.project_root = project_root
        self.build_root = build_root
        self.tomls_root = tomls_root
    
    def get_default_config(self):
        return {
            "version":"1.0.0",
            "all_game_ids": {
                "mm": {
                    "func_syms": "/Zelda64RecompSyms/mm.us.rev1.syms.toml",
                    "data_syms": [ 
                        "./Zelda64RecompSyms/mm.us.rev1.datasyms.toml", 
                        "./Zelda64RecompSyms/mm.us.rev1.datasyms_static.toml"
                    ]
                }
            },  
            "submodules": {
                "core": {
                    "makefile": "Makefile_core",
                    "template": "mm_core"
                },
                "tests": {
                    "dependencies": [
                        "core"
                    ]
                }
            }
        }

    def get_dependency_str(self, deps: list[str], version: str):
        retVal = ""
        for i in deps:
            retVal += f"\"{RECOMP_LIBC_PREFIX}{i}:{version}\","
        return retVal
    
    def get_data_syms_str(self, syms: list[str]):
        retVal = ""
        for i in syms:
            p = str(self.project_root.joinpath(i)).replace("\\", "/")
            retVal += f"\"{p}\","
        return retVal
    
    def generate_toml(self, template: str, submodule_id: str, version: str, game_id: str, dependencies_str: str, makefile: Path,
            func_syms: Path, data_syms_str: str):
        return getattr(btt, template)(submodule_id, version, game_id, dependencies_str, makefile,
            str(self.build_root).replace("\\", "/"), func_syms, data_syms_str)
    
    def write_config_toml(self, template: str, submodule_id: str, version: str, game_id: str, dependencies: str, makefile: Path,
            func_syms: Path, data_syms_str: str) -> Path:
        print(f"Writing .toml for submodule '{submodule_id}'...")
        out_file = self.tomls_root.joinpath(game_id).joinpath(submodule_id).with_suffix(".toml")
        os.makedirs(out_file.parent, exist_ok=True)
        
        out_toml = self.generate_toml(template, submodule_id, version, game_id, dependencies, str(makefile.absolute()).replace("\\", "/"),
            str(func_syms).replace("\\", "/"), data_syms_str)
        
        out_file.write_text(out_toml)

        return out_file
    
    def generate_from_config_dict(self, cd: dict) -> list[Path]:
        version: str= cd["version"]
        all_game_ids: dict[str] = cd["all_game_ids"]
        submodules: dict = cd["submodules"]
        
        retVal = []
        
        for submodule_id, config in submodules.items():
            gen_for_game_ids = config["gen_for_game_ids"] if "gen_for_game_ids" in config else list(all_game_ids.keys())
            
            dep_str = ""
            if "dependencies" in config:
                dep_str = self.get_dependency_str(config["dependencies"], version)
            
            makefile = self.project_root.joinpath("Makefile")
            if "makefile" in config:
                makefile = self.project_root.joinpath(config["makefile"])
                
            template = "mm_extra"
            if "template" in config:
                template = config["template"]
                
            for game_id in gen_for_game_ids:
                syms = all_game_ids[game_id]
                
                retVal.append(self.write_config_toml(template, submodule_id, version, game_id, dep_str, makefile,
                    self.project_root.joinpath(syms["func_syms"]), self.get_data_syms_str(syms["data_syms"])))
        
        return retVal

if __name__ == '__main__':
    proot = Path(__file__).parent.absolute()
    subgen = SubmoduleGenerator(proot, proot.joinpath(TOML_DIR_NAME), proot.joinpath(BUILD_ROOT_NAME))
    submodule_config = json.loads(proot.joinpath(SUBMODULE_CONFIG_NAME).read_text())
    subgen.generate_from_config_dict(submodule_config)