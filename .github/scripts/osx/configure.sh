#!/bin/sh

cmake --no-warn-unused-cli \
  -DCMAKE_TOOLCHAIN_FILE="/usr/local/share/vcpkg/scripts/buildsystems/vcpkg.cmake" \
  -DCMAKE_MAKE_PROGRAM="ninja" \
  -B ./build \
  -G Ninja
