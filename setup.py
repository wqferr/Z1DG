# cython: language_level=3
from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize
import os

def main():
    flags = [] if os.name == "nt" else ["-pthread"]
    flags += ["-I./include"]
    os.environ["CFLAGS"] = " ".join(flags)
    setup(
        name = "Z1DG",
        ext_modules = cythonize(
            [
                Extension(
                    "z1dg",
                    [
                        "src/z1dg.pyx",
                        # "src/room.cpp",
                        "src/allocators/PoolAllocator.cpp"
                    ],
                    include_dirs=["src", "include"],
                    language="c++"
                ),
            ],
            compiler_directives = {"language_level": "3"}
        ),
    )

if __name__ == "__main__":
    main()