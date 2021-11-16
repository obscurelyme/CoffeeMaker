cmake --no-warn-unused-cli -DCMAKE_TOOLCHAIN_FILE:STRING="C:/vcpkg/scripts/buildsystems/vcpkg.cmake" -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -B build -S . -T host=x64 -A x64
