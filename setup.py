from distutils.core import setup
from Cython.Build import cythonize
import os

def main():
    compile_flags = [] if os.name == "nt" else ["-pthread"]
    setup(
        name = "Z1DG",
        ext_modules = cythonize(
            "src/z1dg.pyx",
            compiler_directives={"languge_level": "3"},
            extra_compile_args=compile_flags
        )
    )

if __name__ == "__main__":
    main()