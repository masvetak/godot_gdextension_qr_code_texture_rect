#!/usr/bin/env python
import os
import sys

env = SConscript("submodules/godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["source/"])
sources = Glob("source/*.cpp")

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "build/bin/qr_code_texture_rect.{}.{}.framework/qr_code_texture_rect.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "build/bin/qr_code_texture_rect{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
