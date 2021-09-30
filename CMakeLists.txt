cmake_minimum_required(VERSION 3.15.0)

set(VCPKG_FEATURE_FLAGS "versions")

project(MyDemoApp VERSION 0.1.0)

set(VCPKG_INCLUDE "${VCPKG_INSTALLED_DIR}/x64-windows/include")

set(C_STANDARD_REQUIRED TRUE)
set(CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

if(APPLE)
	set(CMAKE_THREAD_LIBS_INIT "-lpthread")
	set(CMAKE_HAVE_THREADS_LIBRARY 1)
	set(CMAKE_USE_WIN32_THREADS_INIT 0)
	set(CMAKE_USE_PTHREADS_INIT 1)
	set(THREADS_PREFER_PTHREAD_FLAG ON)
endif()

find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

set(COFFEEMAKER_MAIN src/App.cpp)
set(COFFEEMAKER_ROOT_SOURCES
  src/Renderer.cpp
  src/Window.cpp
  src/Color.cpp
  src/Logger.cpp
  src/Utilities.cpp
  src/Texture.cpp
  src/Cursor.cpp
  src/FPS.cpp
  src/FontManager.cpp
  src/Timer.cpp
  src/MessageBox.cpp
  src/Transform.cpp
  src/InputManager.cpp)
set(COFFEEMAKER_PRIMITIVE_SOURCES src/Primitives/Rect.cpp src/Primitives/Line.cpp)
set(COFFEEMAKER_WIDGET_SOURCES src/Widgets/Button.cpp src/Widgets/UIComponent.cpp src/Widgets/View.cpp src/Widgets/Text.cpp)
set(COFFEEMAKER_SOURCES ${COFFEEMAKER_ROOT_SOURCES} ${COFFEEMAKER_PRIMITIVE_SOURCES} ${COFFEEMAKER_WIDGET_SOURCES})

set(GAME_SOURCES
  src/Game/Scenes/TitleScene.cpp
  src/Game/Scenes/MainScene.cpp
  src/Game/Scene.cpp
  src/Game/Collider.cpp
  src/Game/Enemy.cpp
  src/Game/Player.cpp
  src/Game/Tiles.cpp
  src/Game/Projectile.cpp)

set(COFFEEMAKER_EXE_SOURCES ${COFFEEMAKER_MAIN} ${COFFEEMAKER_SOURCES} ${GAME_SOURCES})

add_executable(main ${COFFEEMAKER_EXE_SOURCES})
target_include_directories(main PRIVATE include)
target_link_libraries(main PRIVATE spdlog::spdlog spdlog::spdlog_header_only glm::glm)
if (WIN32)
  message("Building for Win32")
  target_link_libraries(main PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_ttf SDL2::SDL2_image)
elseif(APPLE)
  message("Building for OSX")
  target_link_libraries(main PRIVATE SDL2::SDL2main SDL2::SDL2-static SDL2::SDL2_ttf SDL2::SDL2_image)
endif()

## DPI Awareness
if (WIN32)
  set_target_properties(main PROPERTIES VS_DPI_AWARE "ON")
  set_target_properties(main PROPERTIES VS_GLOBAL_VcpkgEnabled true)
endif()
# set_target_properties(main PROPERTIES VS_GLOBAL_VcpkgTriplet "x64-windows-static") # Uncomment to use static libraries instead

# Unit Tests ##########

set(COFFEEMAKER_TEST_MAIN tests/main.cpp)
set(COFFEEMAKER_DEMO_TEST_SOURCES tests/ComplexNumber.cpp tests/Complex.cpp tests/TestWithMocking.cpp)
set(COFFEEMAKER_TEST_SOURCES
  tests/TestBed.cpp
  # tests/CoffeeMakerShapesRect.cpp
  # tests/CoffeeMakerTextureTest.cpp
  # tests/CoffeeMakerUtilities.cpp
  # tests/CoffeeMakerWidgetButton.cpp
  tests/CoffeeMakerWidgetView.cpp
  # tests/CoffeeMakerComponent.cpp
  tests/CoffeeMakerWidgetText.cpp)
set(COFFEEMAKER_TEST_EXE_SOURCES ${COFFEEMAKER_TEST_MAIN} ${COFFEEMAKER_SOURCES} ${COFFEEMAKER_TEST_SOURCES})

find_package(CppUnit CONFIG REQUIRED)

add_executable(CoffeeMakerWindowUnitTests ${COFFEEMAKER_TEST_EXE_SOURCES})
target_include_directories(CoffeeMakerWindowUnitTests PRIVATE "${VCPKG_INCLUDE}" include tests/include)
target_link_libraries(CoffeeMakerWindowUnitTests PRIVATE CppUnit spdlog::spdlog spdlog::spdlog_header_only glm::glm)
if (WIN32)
  target_link_libraries(CoffeeMakerWindowUnitTests PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_ttf SDL2::SDL2_image)
elseif(APPLE)
  target_link_libraries(CoffeeMakerWindowUnitTests PRIVATE SDL2::SDL2main SDL2::SDL2-static SDL2::SDL2_ttf SDL2::SDL2_image)
endif()


if (APPLE)
  execute_process(COMMAND rm "-rf" "${PROJECT_BINARY_DIR}/assets")
  execute_process(COMMAND bash "${PROJECT_SOURCE_DIR}/post-build-osx.sh")
endif()

# Set Warnings
if (MSVC)
  target_compile_options(CoffeeMakerWindowUnitTests PRIVATE /W4 /WX)
  target_compile_options(main PRIVATE /W4 /WX)
else()
  target_compile_options(CoffeeMakerWindowUnitTests PRIVATE -Wall -Wextra -Wpedantic -Werror)
  target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
