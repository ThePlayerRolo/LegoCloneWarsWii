#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import sys
from pathlib import Path
from typing import Any, Dict, List

from tools.project import (
    Object,
    ProgressCategory,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "SC4E64",   # 0
    "SC4P64",   # 1
]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
# Don't build asm unless we're --non-matching
if not config.non_matching:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-1"
config.compilers_tag = "20250520"
config.dtk_tag = "v1.5.1"
config.objdiff_tag = "v3.0.0-beta.8"
config.sjiswrap_tag = "v1.2.1"
config.wibo_tag = "0.6.16"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    f"-I build/{config.version}/include",
    f"--defsym BUILD_VERSION={version_num}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
]
if args.debug:
    config.ldflags.append("-g")  # Or -gdwarf-2 for Wii linkers
if args.map:
    config.ldflags.append("-mapunused")
    # config.ldflags.append("-listclosure") # For Wii linkers

# Use for any additional files that should cause a re-configure when modified
config.reconfig_deps = []

# Optional numeric ID for decomp.me preset
# Can be overridden in libraries or objects
config.scratch_preset_id = None

# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
cflags_base = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    "-func_align 4",
    # "-W all",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-fp_contract on",
    "-str reuse",
    "-enc SJIS",
    "-i include",
    f"-i build/{config.version}/include",
    f"-DBUILD_VERSION={version_num}",
    f"-DVERSION_{config.version}",
]

# Debug flags
if args.debug:
    # Or -sym dwarf-2 for Wii compilers
    cflags_base.extend(["-sym on", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

config.linker_version = "Wii/1.0"


Matching = True                   # Object matches and should be linked
NonMatching = False               # Object does not match and should not be linked
Equivalent = config.non_matching  # Object should be linked when configured with --non-matching


config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": config.linker_version,
        "cflags": [
            *cflags_base,
            "-use_lmw_stmw on",
            "-str reuse,pool,readonly",
            "-gccinc",
            "-common off",
            "-inline auto",
            "-lang=c99",
        ],
        "progress_category": "runtime",
        "objects": [
            Object(Matching, "runtime.ppceabi.h/global_destructor_chain.c",  extra_cflags=["-O4"]),
            Object(Matching, "runtime.ppceabi.h/__init_cpp_exceptions.cpp",  extra_cflags=["-O4"]),
            Object(Matching, "runtime.ppceabi.h/Gecko_ExceptionPPC.cpp",  extra_cflags=["-O4,s"]),
            Object(Matching, "runtime.ppceabi.h/__va_arg.c",  extra_cflags=["-O4"]),
            Object(Matching, "runtime.ppceabi.h/GCN_mem_alloc.c", extra_cflags=["-O4"]),
            Object(Matching, "runtime.ppceabi.h/ptmf.c", extra_cflags=["-O4"]),
            Object(Matching, "runtime.ppceabi.h/runtime.c", extra_cflags=["-O3,s"]),
            Object(Matching, "runtime.ppceabi.h/__mem.c", extra_cflags=["-O4,s"]),
            Object(Matching, "runtime.ppceabi.h/NMWException.cpp", extra_cflags=["-O4"])
        ]
    },
    {
        "lib": "TRK_Hollywood_Revolution",
        "mw_version": config.linker_version,
        "cflags": [
            *cflags_base,
            "-use_lmw_stmw on",
            "-str reuse,pool,readonly",
            "-gccinc",
            "-common off",
            "-inline auto",
            "-lang=c99",
        ],
        "progress_category": "trk",
        "objects": [
            Object(Matching, "TRK_Hollywood_Revolution/metrotrk/metrotrk/target_options.cpp"),
        ]
    },
    {
        "lib": "RVL_SDK",
        "mw_version": config.linker_version,
        "cflags": [
            *cflags_base,
            "-use_lmw_stmw off",
            "-str reuse",
            "-gccinc",
            "-common off",
            "-inline auto",
            "-O4,p",
            "-lang=c99",
        ],
        "progress_category": "sdk",
        "objects": [
            # OS
            Object(Matching, "os/__ppc_eabi_init.c"),
            Object(Matching, "os/__start.c"),
            Object(NonMatching, "os/OS.c"),
            Object(Matching, "os/OSAlarm.c"),
            Object(Matching, "os/OSAlloc.c"),
            Object(Matching, "os/OSArena.c"),
            Object(Matching, "os/OSAudioSystem.c"),
            Object(NonMatching, "os/OSCache.c"),
            Object(Matching, "os/OSContext.c"),
            Object(Matching, "os/OSError.c"),
            Object(NonMatching, "os/OSExec.c"),
            Object(NonMatching, "os/OSFatal.c"),
            Object(Matching, "os/OSFont.c"),
            Object(NonMatching, "os/OSInterrupt.c"),
            Object(Matching, "os/OSLink.c"),
            Object(NonMatching, "os/OSMessage.c"),
            Object(Matching, "os/OSMemory.c"),
            Object(NonMatching, "os/OSMutex.c"),
            Object(Matching, "os/OSReboot.c"),
            Object(NonMatching, "os/OSReset.c"),
            Object(NonMatching, "os/OSRtc.c"),
            Object(NonMatching, "os/OSSemaphore.c"),
            Object(Matching, "os/OSSync.c"),
            Object(NonMatching, "os/OSThread.c"),
            Object(Matching, "os/OSTime.c"),
            Object(NonMatching, "os/OSUtf.c"),
            Object(Matching, "os/OSIpc.c"),
            Object(NonMatching, "os/OSStateTM.c"),
            Object(NonMatching, "os/OSPlayRecord.c"),
            Object(Matching, "os/OSStateFlags.c"),
            Object(NonMatching, "os/OSNet.c"),
            Object(Matching, "os/OSNandbootInfo.c"),
            Object(NonMatching, "os/OSPlayTime.c"),
            Object(NonMatching, "os/OSCrc.c"),
            Object(NonMatching, "os/OSLaunch.c"),
            # NAND
            Object(NonMatching, "nand/nand.c"),
            Object(Matching, "nand/NANDCheck.c"),
            # BASE
            Object(Matching, "base/PPCArch.c"),
            # MEM
            Object(Matching, "mem/mem_allocator.c"),
            # AI
            Object(Matching, "ai/ai.c"),
        ]
    },
    {
        "lib": "MSL",
        "mw_version": config.linker_version,
        "cflags": [
            *cflags_base,
        ],
        "progress_category": "msl",
        "objects": [
            Object(Matching, "msl_c.ppceabi.bare.h/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/Src/math_sun.c")
        ]
    }
]


# Optional callback to adjust link order. This can be used to add, remove, or reorder objects.
# This is called once per module, with the module ID and the current link order.
#
# For example, this adds "dummy.c" to the end of the DOL link order if configured with --non-matching.
# "dummy.c" *must* be configured as a Matching (or Equivalent) object in order to be linked.
def link_order_callback(module_id: int, objects: List[str]) -> List[str]:
    # Don't modify the link order for matching builds
    if not config.non_matching:
        return objects
    if module_id == 0:  # DOL
        return objects + ["dummy.c"]
    return objects

# Uncomment to enable the link order callback.
# config.link_order_callback = link_order_callback


# Optional extra categories for progress tracking
# Adjust as desired for your project
config.progress_categories = [
    ProgressCategory("game", "Game Code"),
    ProgressCategory("runtime", "Runtime Code"),
    ProgressCategory("trk", "MetroTRK Code"),
    ProgressCategory("sdk", "RVL_SDK Code"),
    ProgressCategory("msl", "MSL Code"),
]
config.progress_each_module = args.verbose
# Optional extra arguments to `objdiff-cli report generate`
config.progress_report_args = [
    # Marks relocations as mismatching if the target value is different
    # Default is "functionRelocDiffs=none", which is most lenient
    # "--config functionRelocDiffs=data_value",
]

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress information
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
