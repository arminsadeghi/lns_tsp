"""Setup script for the LNS TSP package."""

import os
import subprocess
from pathlib import Path

from setuptools import Extension, find_packages, setup
from setuptools.command.build_ext import build_ext


class CMakeExtension(Extension):
    def __init__(self, name, source_dir=""):
        super().__init__(name, sources=[])
        self.source_dir = os.path.abspath(source_dir)


class CMakeBuild(build_ext):
    def run(self):
        # Ensure CMake is available
        try:
            subprocess.check_output(["cmake", "--version"])
        except OSError:
            raise RuntimeError("CMake must be installed to build the extensions")

        # Run the build
        for ext in self.extensions:
            self.build_cmake(ext)

    def build_cmake(self, ext):
        extdir = Path(self.get_ext_fullpath(ext.name)).parent.resolve()
        build_temp = Path(self.build_temp).resolve()

        # Ensure build_temp directory exists
        os.makedirs(build_temp, exist_ok=True)

        # Configure CMake arguments
        cmake_args = [f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={extdir}"]

        # Specify the build type
        cfg = "Debug" if self.debug else "Release"
        build_args = ["--config", cfg]
        cmake_args += [f"-DCMAKE_BUILD_TYPE={cfg}"]

        # Call CMake to configure and build
        subprocess.check_call(
            ["cmake", ext.source_dir] + cmake_args,
            cwd=build_temp,
        )
        subprocess.check_call(
            ["cmake", "--build", "."] + build_args,
            cwd=build_temp,
        )


cmake_extensions = [
    CMakeExtension("lns_tsp.solver_coreore", source_dir="lns_tsp/solver_c_core"),
]


setup(
    name="lns_tsp",
    version="0.1.0",
    include_package_data=True,
    ext_modules=cmake_extensions,
    cmdclass={"build_ext": CMakeBuild},
    packages=find_packages(),
    author="Armin Sadeghi",
    author_email="sadeghiy.armin@gmail.com",
    python_requires=">=3.10",
    zip_safe=False,
    classifiers=[
        "Programming Language :: Python :: 3",
        "Programming Language :: C++",
    ],
    package_data={"lns_tsp.config": ["*.json"]},
)
