from distutils.core import setup
from Cython.Build import cythonize

def main():
    setup(
        name = "Z1DG",
        ext_modules = cythonize(
            "src/z1dg.pyx",
            compiler_directives={"language_level": "3"}
        )
    )

if __name__ == "__main__":
    main()