#!/bin/sh

file=$1

echo "Linting $file..." &&
  /usr/local/opt/llvm/bin/clang-tidy --checks=*,-llvmlibc-*,-modernize-use-trailing-return-type,-fuchsia-default-arguments-calls "$file" --warnings-as-errors=* -- -std=c++20 -Iinclude -I./build/vcpkg_installed/x64-osx/include
