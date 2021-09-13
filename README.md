# Semi-Pro CPP

A neat little repository to practice CPP at the semi-professional level.

## Installation

### Windows

You'll need to fetch the cpp library dependencies using `vcpkg`

```sh
vcpkg install sdl2 sdl2-ttf sdl2-image spdlog cppunit
```

This step could take a minute because `vcpkg` is going to download and compile each of those libraries.

Open up `VS Code` and assuming you have both `Cmake` and `Cmake Tools` extensions installed, it will going ahead and configure the project for you. You should be able to build both the main and test executable.

### OSX

You will need to have autoconf, automake, and libtool installed in order to leverage `cppunit`

You can install these dependencies using `Homebrew` with the command

```sh
brew install automake autoconf libtool
```

Next, you'll need to fetch the cpp library dependencies using `vcpkg`

```sh
vcpkg install sdl2 sdl2-ttf sdl2-image spdlog cppunit
```

This step could take a minute because `vcpkg` is going to download and compile each of those libraries.

Open up `VS Code` and assuming you have both `Cmake` and `Cmake Tools` extensions installed, it will going ahead and configure the project for you. You should be able to build both the main and test executable.

### Linux

You should be able to follow the [OSX](#OSX) steps.
