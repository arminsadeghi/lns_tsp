#!/bin/bash


# Find the root directory of the project
ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )/.."

# Go to the root directory
cd $ROOT_DIR

# Remove old build directory if it exists
if [ -d "build" ]; then
    echo "Removing old build directory..."
    rm -rf build
    rm -rf dist
fi
echo "Installing the package..."
python setup.py sdist bdist_wheel
pip install --force-reinstall dist/*.whl
echo "Installation completed successfully."
echo "==============================================================="
echo "==============================================================="
