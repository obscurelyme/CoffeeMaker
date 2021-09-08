cmake_minimum_required(VERSION 3.15.0)

project(main VERSION 0.1.0)

set(C_STANDARD_REQUIRED TRUE)
set(CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL)
find_package(sdl2-ttf CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
# find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_executable(main App.cpp)
# target_link_libraries(main PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
target_link_libraries(main PRIVATE spdlog::spdlog spdlog::spdlog_header_only)
if (WIN32)
  target_link_libraries(main PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_ttf)
elseif(APPLE)
  target_link_libraries(main PRIVATE SDL2::SDL2main SDL2::SDL2-static SDL2::SDL2_ttf)
endif()

