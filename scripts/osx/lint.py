import os
import subprocess
import sys

fileToLint=sys.argv[1]

print(">>> Running clang-tidy on file %s..." % fileToLint)

subprocess.run(['/usr/local/opt/llvm/bin/clang-tidy',
  '-config-file=.clang-tidy',
  fileToLint,
  '--',
  '-Iinclude',
  '-Ibuild/vcpkg_installed/x64-osx/include',
  '-std=c++20'], stderr=subprocess.STDOUT)

print(">>> Completed clang-tidy on file %s..." % fileToLint)
