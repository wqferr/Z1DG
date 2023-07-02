from distutils.core import setup
from Cython.Build import cythonize

def main():
    source_file_names = ["z1dg"]
    setup(
        name = "Z1DG",
        ext_modules = cythonize(
            [f"src/{file}.pyx" for file in source_file_names],
            compiler_directives={"language_level": "3"}
        )
    )

if __name__ == "__main__":
    main()