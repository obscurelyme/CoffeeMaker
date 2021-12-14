#!/bin/sh

cmake --no-warn-unused-cli \
  -DCMAKE_TOOLCHAIN_FILE="/usr/local/share/vcpkg/scripts/buildsystems/vcpkg.cmake" \
  -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
  -DCMAKE_BUILD_TYPE:STRING=Debug \
  -DCOFFEEMAKER_RELEASE_BUILD:BOOL=TRUE \
  -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/clang \
  -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++ \
  -B ./build \
  -G Ninja
