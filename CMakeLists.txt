cmake_minimum_required(VERSION 3.16.0)

set(VCPKG_FEATURE_FLAGS "versions")
set(VCPKG_MANIFEST_MODE ON)
# comment here.

if (WIN32)
  if (COFFEEMAKER_RELEASE_BUILD)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
  else()
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")
  endif()
endif()

if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
  set(LINUX_PLATFORM TRUE)
endif()

project(CoffeeMaker VERSION 0.1.0)

add_compile_definitions(_USE_MATH_DEFINES)

set(C_STANDARD_REQUIRED TRUE)
set(CXX_STANDARD_REQUIRED TRUE)
set(C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

if(APPLE OR LINUX_PLATFORM)
	set(CMAKE_THREAD_LIBS_INIT "-lpthread")
	set(CMAKE_HAVE_THREADS_LIBRARY 1)
	set(CMAKE_USE_WIN32_THREADS_INIT 0)
	set(CMAKE_USE_PTHREADS_INIT 1)
	set(THREADS_PREFER_PTHREAD_FLAG ON)
endif()

find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-mixer CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(tinyspline CONFIG REQUIRED)
find_package(tinysplinecxx CONFIG REQUIRED)
find_package(argparse CONFIG REQUIRED)

set(APP_RESOURCES resources.rc)

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
  src/InputManager.cpp
  src/Event.cpp
  src/Events/MouseEvents.cpp
  src/Events/UserEvents.cpp
  src/Math.cpp
  src/Sprite.cpp
  src/Spline.cpp
  src/Audio.cpp
  src/Coroutine.cpp
  src/DateTime.cpp)
set(COFFEEMAKER_PRIMITIVE_SOURCES src/Primitives/Rect.cpp src/Primitives/Line.cpp)
set(COFFEEMAKER_WIDGET_SOURCES src/Widgets/Button.cpp src/Widgets/UIComponent.cpp src/Widgets/View.cpp src/Widgets/Text.cpp src/Widgets/ScalableUISprite.cpp)
set(COFFEEMAKER_SOURCES ${COFFEEMAKER_ROOT_SOURCES} ${COFFEEMAKER_PRIMITIVE_SOURCES} ${COFFEEMAKER_WIDGET_SOURCES} ${APP_RESOURCES})

set(GAME_SOURCES
  src/Game/Scenes/TitleScene.cpp
  src/Game/Scenes/MainScene.cpp
  src/Game/Scenes/TestBedScene.cpp
  src/Game/Scenes/TestAnimations.cpp
  src/Game/Scenes/SplineBuilder.cpp
  src/Game/Scene.cpp
  src/Game/Collider.cpp
  src/Game/Entity.cpp
  src/Game/Enemy.cpp
  src/Game/Player.cpp
  src/Game/Tiles.cpp
  src/Game/Projectile.cpp
  src/Game/Menus/Menu.cpp
  src/Game/Hud.cpp
  src/Game/Animations/EnemyAnimations.cpp
  src/Game/Animations/SpriteAnimation.cpp
  src/Game/Animations/Explode.cpp
  src/Game/PowerUps/BasePowerUp.cpp
  src/Game/Echelon.cpp
  src/Game/Scenes/TestEchelon.cpp
  src/Game/Scenes/HighScoreScene.cpp
  src/Game/Events.cpp
  src/Game/ScoreManager.cpp)

set(COFFEEMAKER_EXE_SOURCES ${COFFEEMAKER_MAIN} ${COFFEEMAKER_SOURCES} ${GAME_SOURCES})

add_executable(main ${COFFEEMAKER_EXE_SOURCES})
target_include_directories(main PRIVATE include)
target_link_libraries(main PRIVATE fmt::fmt-header-only spdlog::spdlog spdlog::spdlog_header_only glm::glm)
target_link_libraries(main PRIVATE tinyspline::tinyspline tinysplinecxx::tinysplinecxx)
target_link_libraries(main PRIVATE argparse::argparse)

if (WIN32)
  message("Building for Win32")
  target_link_libraries(main PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_ttf SDL2::SDL2_image SDL2::SDL2_mixer)

  # target_compile_definitions(main PRIVATE COFFEEMAKER_LOGGER_SOURCE_LOCATION)
elseif(APPLE)
  message("Building for OSX")
  find_package(Ogg CONFIG REQUIRED)
  find_package(Vorbis CONFIG REQUIRED)
  find_package(mpg123 CONFIG REQUIRED)

  target_link_libraries(main PRIVATE Ogg::ogg)
  target_link_libraries(main PRIVATE SDL2::SDL2main SDL2::SDL2-static SDL2::SDL2_ttf SDL2::SDL2_image SDL2::SDL2_mixer)
  target_link_libraries(main PRIVATE Vorbis::vorbis Vorbis::vorbisenc Vorbis::vorbisfile)
  target_link_libraries(main PRIVATE MPG123::libmpg123 MPG123::libout123 MPG123::libsyn123)
elseif(LINUX_PLATFORM)
  message("Linking dependencies for Linux")
  add_compile_definitions(_FILE_OFFSET_BITS=64)
  find_package(Ogg CONFIG REQUIRED)
  find_package(Vorbis CONFIG REQUIRED)
  find_package(mpg123 CONFIG REQUIRED)

  # SDL2
  target_link_libraries(main PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static)
  # SDL2-image
  target_link_libraries(main PRIVATE SDL2::SDL2_image)
  # SDL2-ttf
  target_link_libraries(main PRIVATE SDL2::SDL2_ttf)
  # SDL2-mixer
  target_link_libraries(main PRIVATE SDL2::SDL2_mixer)
  # SDL2-mixer dependencies
  target_link_libraries(main PRIVATE Ogg::ogg)
  target_link_libraries(main PRIVATE Vorbis::vorbis Vorbis::vorbisenc Vorbis::vorbisfile)
  target_link_libraries(main PRIVATE MPG123::libmpg123 MPG123::libout123 MPG123::libsyn123)
endif()

## DPI Awareness
if (WIN32)
  set_target_properties(main PROPERTIES VS_DPI_AWARE "ON")
  set_target_properties(main PROPERTIES VS_GLOBAL_VcpkgEnabled true)
  set_target_properties(main PROPERTIES VS_GLOBAL_VcpkgEnableManifest true)
endif()

# Unit Tests ##########

set(COFFEEMAKER_TEST_MAIN tests/main.cpp)
set(COFFEEMAKER_DEMO_TEST_SOURCES tests/ComplexNumber.cpp tests/Complex.cpp tests/TestWithMocking.cpp)
set(COFFEEMAKER_TEST_SOURCES
  # tests/TestBed.cpp
  tests/CoffeeMakerUserEvents.cpp
  tests/CoffeeMakerBSpline.cpp
  tests/UCIEchelon.cpp
  tests/CoffeeMakerMath.cpp
  tests/CoffeeMakerCoroutine.cpp
  tests/CoffeeMakerDateTime.cpp
  tests/UCIScoreManager.cpp
  # tests/CoffeeMakerShapesRect.cpp
  # tests/CoffeeMakerTextureTest.cpp
  # tests/CoffeeMakerUtilities.cpp
  # tests/CoffeeMakerWidgetButton.cpp
  # tests/CoffeeMakerEvents.cpp
  # tests/CoffeeMakerWidgetView.cpp
  # tests/CoffeeMakerComponent.cpp
  # tests/CoffeeMakerWidgetText.cpp
  # tests/CheapAsteroidsEnemy.cpp
  )
set(COFFEEMAKER_TEST_EXE_SOURCES ${COFFEEMAKER_TEST_MAIN} ${COFFEEMAKER_SOURCES} ${GAME_SOURCES} ${COFFEEMAKER_TEST_SOURCES})

find_package(CppUnit CONFIG REQUIRED)

add_executable(CoffeeMakerUnitTests ${COFFEEMAKER_TEST_EXE_SOURCES})
target_include_directories(CoffeeMakerUnitTests PRIVATE "${VCPKG_INCLUDE}" include tests/include)
target_link_libraries(CoffeeMakerUnitTests PRIVATE CppUnit spdlog::spdlog spdlog::spdlog_header_only glm::glm)
target_link_libraries(CoffeeMakerUnitTests PRIVATE tinyspline::tinyspline tinysplinecxx::tinysplinecxx)

if (WIN32)
  target_link_libraries(CoffeeMakerUnitTests PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_ttf SDL2::SDL2_image SDL2::SDL2_mixer)
elseif(APPLE)
message("Building for OSX")
  find_package(Ogg CONFIG REQUIRED)
  find_package(Vorbis CONFIG REQUIRED)
  find_package(mpg123 CONFIG REQUIRED)

  target_link_libraries(CoffeeMakerUnitTests PRIVATE Ogg::ogg)
  target_link_libraries(CoffeeMakerUnitTests PRIVATE SDL2::SDL2main SDL2::SDL2-static SDL2::SDL2_ttf SDL2::SDL2_image SDL2::SDL2_mixer)
  target_link_libraries(CoffeeMakerUnitTests PRIVATE Vorbis::vorbis Vorbis::vorbisenc Vorbis::vorbisfile)
  target_link_libraries(CoffeeMakerUnitTests PRIVATE MPG123::libmpg123 MPG123::libout123 MPG123::libsyn123)
elseif(LINUX_PLATFORM)
  message("Linking dependencies for Linux")

  add_compile_definitions(_FILE_OFFSET_BITS=64)
  find_package(Ogg CONFIG REQUIRED)
  find_package(Vorbis CONFIG REQUIRED)
  find_package(mpg123 CONFIG REQUIRED)
  # SDL2
  target_link_libraries(CoffeeMakerUnitTests PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static)
  # SDL2-image
  target_link_libraries(CoffeeMakerUnitTests PRIVATE SDL2::SDL2_image)
  # SDL2-ttf
  target_link_libraries(CoffeeMakerUnitTests PRIVATE SDL2::SDL2_ttf)
  # SDL2-mixer
  target_link_libraries(CoffeeMakerUnitTests PRIVATE SDL2::SDL2_mixer)
  # SDL2-mixer dependencies
  target_link_libraries(CoffeeMakerUnitTests PRIVATE Ogg::ogg)
  target_link_libraries(CoffeeMakerUnitTests PRIVATE Vorbis::vorbis Vorbis::vorbisenc Vorbis::vorbisfile)
  target_link_libraries(CoffeeMakerUnitTests PRIVATE MPG123::libmpg123 MPG123::libout123 MPG123::libsyn123)
endif()


if (APPLE OR LINUX_PLATFORM)
  message("Please run ${PROJECT_SOURCE_DIR}/scripts/post-build.sh if this is your first time configuring this project")
  # execute_process(COMMAND sh "${PROJECT_SOURCE_DIR}/scripts/post-build.sh")
elseif (WIN32)
  message("Please run ${PROJECT_SOURCE_DIR}/scripts/post-build.bat if this is your first time configuring this project")
  # execute_process(COMMAND "${PROJECT_SOURCE_DIR}/scripts/post-build.bat")
endif()

# Set Warnings
if (MSVC)
  target_compile_options(CoffeeMakerUnitTests PRIVATE /W4 /WX)
  target_compile_options(main PRIVATE /W4 /WX)
else()
  target_compile_options(CoffeeMakerUnitTests PRIVATE -Wall -Wextra -Wpedantic -Werror)
  target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic -Werror)
  # target_link_options(main PRIVATE -fsanitize=address)
endif()

# Set Coroutine Support
if (MSVC)
  message("Compiler is MSVC and engine will use <coroutine> headers")
  add_compile_definitions(COROUTINE_SUPPORT)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  message("Compiler is GNU and engine will use <coroutine> headers")
  target_compile_options(main PRIVATE -fcoroutines)
  target_compile_options(CoffeeMakerUnitTests PRIVATE -fcoroutines)
  add_compile_definitions(COROUTINE_SUPPORT)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "AppleClang")
  message("NOTICE: PLEASE DO NOT USE CLANG ON LINUX OR WINDOWS PLATFORMS\nYou may experience issues that are and will not be supported in the foreseeable future.")
  message("Compiler is Clang and engine will use <experimental/coroutine> headers")
  add_compile_definitions(COROUTINE_EXPERIMENTAL_SUPPORT)
endif()

if(COFFEEMAKER_RELEASE_BUILD)
  message("Generated binary files for COFFEEMAKER_RELEASE_BUILD")
  add_compile_definitions(COFFEEMAKER_RELEASE_BUILD)
endif()

if(COFFEEMAKER_LICENSED_ASSETS)
  message("Leveraging licensed assets for CoffeeMaker.\nNOTE: This setting is for core developers only.")
  add_compile_definitions(COFFEEMAKER_LICENSED_ASSETS)
else()
  message("WARNING: licensed assets will not be used in this build of CoffeeMaker.\nIf this was NOT what you are expecting please reconfigure cmake with -DCOFFEEMAKER_LICENSED_ASSETS:BOOL=true")
endif()

