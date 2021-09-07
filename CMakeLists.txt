cmake_minimum_required(VERSION 3.15.0)

project(main VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
target_link_libraries(main PRIVATE spdlog::spdlog spdlog::spdlog_header_only)
# if(APPLE)
#   target_link_libraries(main PRIVATE "-framework OpenGL -framework Cocoa")
# endif()
# if(WIN32)
#   target_link_libraries(main PRIVATE opengl32)
# endif()
