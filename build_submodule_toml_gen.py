import textwrap, pathlib, json, os
from pathlib import Path

TOML_DIR_NAME = "generated_tomls"
SUBMODULE_CONFIG_NAME = "submodules.json"
RECOMP_LIBC_PREFIX = "recomp_libc_"

class SubmoduleGenerator:    
    project_root: Path
    tomls_root: Path
    def __init__(self, project_root: Path, tomls_root: Path):
        self.project_root = project_root
        self.tomls_root = tomls_root
    
    def get_default_config(self):
        return {
            "version":"1.0.0",
            "all_game_ids": [
                "mm"
            ],
            "submodules": {
                "ctype": {},
                "printf": {},
                "strings": {},
                "stdlib": {
                    "dependencies": [
                        "ctype",
                        "strings"
                    ]
                }
            }
        }
    
    def generate_toml(self, submodule_id: str, version: str, game_id: str, dependencies_str: str, makefile: str = "Makefile"):
        return textwrap.dedent(f"""
        # Config file for an example Majora's Mask: Recompiled mod.

        # Fields that end up in the mod's manifest.
        [manifest]

        # Unique ID of this mod. Pick something long enough that it'll never be the same as any other mod.
        # The name displayed in the mod management menu is separate from this so this doesn't need to be human readable.
        id = "recomp_libc_{submodule_id}"

        # Version of this mod.
        version = "{version}"

        # The name that will show up for this mod in the mod menu. This should be human readable.
        display_name = "Recomp LibC: {submodule_id.capitalize()} ({game_id.upper()})"

        # The description that will show up when this mod is displayed in the mod menu. This should be human readable.
        description =  \"\"\"An Implementation of LibC for N64Recomp, ported from https://github.com/embeddedartistry/libc.<br/>
        <br/>
        This package targets Majora's Mask
        \"\"\"

        # A short description that will show up in this mod's entry in the mod list. This should be human readable and kept short
        # to prevent it from being cut off due to the limited space.
        short_description = "An Implementation of LibC: {submodule_id.capitalize()} for N64Recomp."

        # Authors of this mod.
        authors = [ "LT_Schmiddy" ]

        # ID of the target recomp game.
        game_id = "{game_id}"

        # Minimum version of the target recomp (e.g. Zelda 64: Recompiled) that this mod can run on.
        minimum_recomp_version = "1.2.0"

        # Dependency mods. Each entry is the mod's ID and then an optional minimum version of the dependency mod.
        # Example dependency:
        # "modname:1.0.0"
        dependencies = [{dependencies_str}        ]

        # Native libraries (e.g. DLLs) and the functions they export.
        native_libraries = [
        # Example native library:
        #    {{ name = "my_native_library", funcs = ["my_native_library_function"] }}
        ]

        # Inputs to the mod tool.
        [inputs]

        # Input elf file to generate a mod from.
        elf_path = "../../build/{submodule_id}/mod.elf"

        # Output mod filename.
        mod_filename = "{game_id}_recomp_libc_{submodule_id}_{version}"

        # Reference symbol files.
        func_reference_syms_file = "../../Zelda64RecompSyms/{game_id}.us.rev1.syms.toml"
        data_reference_syms_files = [ "../../Zelda64RecompSyms/{game_id}.us.rev1.datasyms.toml", "../../Zelda64RecompSyms/{game_id}.us.rev1.datasyms_static.toml" ]

        # Additional files to include in the mod.
        additional_files = [ ]

        [N64Recomp_libc]
        submodule = "{submodule_id}"
        """)
    
    def get_dependency_str(self, deps: list[str], version: str):
        retVal = "\n"
        for i in deps:
            retVal += f"            \"{RECOMP_LIBC_PREFIX}{i}:{version}\",\n"
        return retVal
    
    def write_config_toml(self, submodule_id: str, version: str, game_id: str, dependencies: list[str]) -> Path:
        print(f"Writing .toml for submodule '{submodule_id}'...")
        out_file = self.tomls_root.joinpath(game_id).joinpath(submodule_id).with_suffix(".toml")
        os.makedirs(out_file.parent, exist_ok=True)
        out_file.write_text(self.generate_toml(submodule_id, version, game_id, dependencies))
        
        return out_file
    
    def generate_from_config_dict(self, cd: dict) -> list[Path]:
        version: str= cd["version"]
        all_game_ids: list[str] = cd["all_game_ids"]
        submodules: dict = cd["submodules"]
        
        retVal = []
        
        for submodule_id, config in submodules.items():
            gen_for_game_ids = config["gen_for_game_ids"] if "gen_for_game_ids" in config else all_game_ids
            
            dep_str = ""
            if "dependencies" in config:
                dep_str = self.get_dependency_str(config["dependencies"], version)
                
            for game_id in gen_for_game_ids:
                retVal.append(self.write_config_toml(submodule_id, version, game_id, dep_str))
        
        return retVal

if __name__ == '__main__':
    proot = Path(__file__).parent
    subgen = SubmoduleGenerator(proot, proot.joinpath(TOML_DIR_NAME))
    submodule_config = json.loads(proot.joinpath(SUBMODULE_CONFIG_NAME).read_text())
    subgen.generate_from_config_dict(submodule_config)