#!/bin/bash

# On OSX, clang-tidy is cask only because Apple has its own LLVM stuff preinstalled
ClangTidy="/usr/local/opt/llvm/bin/clang-tidy"

$ClangTidy \
  --config-file=.clang-tidy \
  src/App.cpp \
  -- -Iinclude -Ibuild/vcpkg_installed/x64-osx/include \
  -std=c++20
