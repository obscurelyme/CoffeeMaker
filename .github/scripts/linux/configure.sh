#!/bin/sh

cmake --no-warn-unused-cli \
  -DCMAKE_TOOLCHAIN_FILE="/usr/local/share/vcpkg/scripts/buildsystems/vcpkg.cmake" \
  -DCMAKE_C_COMPILER:FILEPATH="/usr/bin/gcc-11" \
  -DCMAKE_CXX_COMPILER:FILEPATH="/usr/bin/g++-11" \
  -B ./build
