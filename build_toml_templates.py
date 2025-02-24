import textwrap
from pathlib import Path

def mm_core(submodule_id: str, version: str, game_id: str, dependencies_str: str, makefile: str,
            build_root: Path, func_syms: Path, data_syms_str: str) -> str:
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
        dependencies = [{dependencies_str}]

        # Native libraries (e.g. DLLs) and the functions they export.
        native_libraries = [
        # Example native library:
        #    {{ name = "my_native_library", funcs = ["my_native_library_function"] }}
        ]

        # Inputs to the mod tool.
        [inputs]

        # Input elf file to generate a mod from.
        elf_path = "{build_root}/{submodule_id}/mod.elf"

        # Output mod filename.
        mod_filename = "{game_id}_recomp_libc_{submodule_id}_{version}"

        # Reference symbol files.
        func_reference_syms_file = "{func_syms}"
        data_reference_syms_files = [{data_syms_str}]

        # Additional files to include in the mod.
        additional_files = [ ]

        [N64Recomp_libc]
        submodule = "{submodule_id}"
        Makefile = "{makefile}"
        build_dir = "{build_root}/{submodule_id}"
        """)


def mm_extra(submodule_id: str, version: str, game_id: str, dependencies_str: str, makefile: str,
            build_root: Path, func_syms: Path, data_syms_str: str) -> str:
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
        dependencies = [{dependencies_str}]

        # Native libraries (e.g. DLLs) and the functions they export.
        native_libraries = [
        # Example native library:
        #    {{ name = "my_native_library", funcs = ["my_native_library_function"] }}
        ]

        # Inputs to the mod tool.
        [inputs]

        # Input elf file to generate a mod from.
        elf_path = "{build_root}/{submodule_id}/mod.elf"

        # Output mod filename.
        mod_filename = "{game_id}_recomp_libc_{submodule_id}_{version}"

        # Reference symbol files.
        func_reference_syms_file = "{func_syms}"
        data_reference_syms_files = [{data_syms_str}]

        # Additional files to include in the mod.
        additional_files = [ ]

        [N64Recomp_libc]
        submodule = "{submodule_id}"
        Makefile = "{makefile}"
        build_dir = "{build_root}/{submodule_id}"
        """)