#!/bin/bash

set -e  # Exit on error

echo "[+] Starting C++ build process..."

BUILD_DIR="./extractor/build"

# Create build directory if not exists
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Configure with CMake
cmake ..

# Build
make -j$(nproc || sysctl -n hw.ncpu)

echo "[+] Build completed. Binary is at: $BUILD_DIR/malalyzer"

