# Hello SFML

```
Launch VS Code
CMake Tools will configure assuming you have the following packages installed

sfml:x64-windows
spdlog:x64-windows
```

### Post build

On windows, you can run the post-build-windows.bat file

```
.\post-build-windows.bat
```

This will copy over the font assets into the `build/DEBUG/assets`

On Max/Linux, you can run the cp -r

```
cp -r assets build/Debug/assets
```

### Here is the result directory after a debug build

![Screenshot](doc/debug-libs-screenshot.png)
