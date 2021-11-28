if "%~1"=="" goto End1

set FILE_TO_LINT=%1

echo "Linting %FILE_TO_LINT%...";
  clang-tidy --checks=*,-llvmlibc-*,-modernize-use-trailing-return-type,-fuchsia-default-arguments-calls "%FILE_TO_LINT%" --warnings-as-errors=* -- -std=c++20 -Iinclude -I./build/vcpkg_installed/x64-windows/include

:End1
