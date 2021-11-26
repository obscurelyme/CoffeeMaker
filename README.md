# CoffeeMaker

_A warm and fuzzy 2D game engine._

[![coffeemaker-ci](https://github.com/obscurelyme/CoffeeMaker/actions/workflows/config.yml/badge.svg?branch=master)](https://github.com/obscurelyme/CoffeeMaker/actions/workflows/config.yml) [![CodeFactor](https://www.codefactor.io/repository/github/obscurelyme/coffeemaker/badge)](https://www.codefactor.io/repository/github/obscurelyme/coffeemaker)

CoffeeMaker is an open source 2D game engine written in C++ with SDL2.

> This engine is being built alongside an arcade 2D top-down space shooter game. All game specific files are located within
> `src/Game`.

### Features

---

- B-Spline creation
- Events
  - SDL2 Mouse Event
  - SDL2 User Event
- Window creation
- 2D Renderer with SDL2
  - Sprites
- Audio
  - Play music
  - Play sound effects
- Animation
  - B-Spline Animations
  - Sprite Animations
- Input Manager
  - Keyboard
- Scenes
- Physics
  - AABB
- Fonts (TTF)
- UI widgets
  - View
  - Buttons
  - Text
  - Flexbox-like positioning
- Math
  - 2D Vectors
  - Bezier Curves
  - Lerps
  - Random Number Generation
- Async
  - Timeouts
  - Intervals
- Logging
  - Log to files
  - Log to consoles

---

### Prerequisites

[vcpkg](https://vcpkg.io/en/index.html) is a required package manager for this project. If you do not have vcpkg installed, you can follow the instructions in the link to install and setup `vcpkg`.

### Getting Started

1. Clone

```bash
git clone https://github.com/obscurelyme/CoffeeMaker
```

2. Download the assets from [Google Drive](https://drive.google.com/drive/folders/1p6DR6DBM-Piak81ub66MXonAL9pEK6e4?usp=sharing) into ./CoffeeMaker/assets.

3. Run ./scripts/post-build.{sh | bat} to copy over assets into build directory.

4. Configure

5. Build

#### Follow the development of CoffeeMaker

[Trello](https://trello.com/b/j6CsKZz1/coffeemaker)
