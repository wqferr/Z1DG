# cython: language_level=3
from distutils.core import setup
from Cython.Build import cythonize
import os

def main():
    flags = [] if os.name == "nt" else ["-pthread"]
    flags += "-I./include"
    os.environ["CFLAGS"] = " ".join(flags)
    setup(
        name = "Z1DG",
        ext_modules = cythonize("src/z1dg.pyx")
    )

if __name__ == "__main__":
    main()