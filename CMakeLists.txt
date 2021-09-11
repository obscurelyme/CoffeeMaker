cmake_minimum_required(VERSION 3.15.0)

set(VCPKG_FEATURE_FLAGS "versions")

project(MyDemoApp VERSION 0.1.0)


set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL)
find_package(Freetype REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_executable(MyDemoApp main.cpp)
target_link_libraries(MyDemoApp PRIVATE sfml-system sfml-network sfml-graphics sfml-window Freetype::Freetype)
target_link_libraries(MyDemoApp PRIVATE spdlog::spdlog spdlog::spdlog_header_only)
# if(APPLE)
#   target_link_libraries(MyDemoApp PRIVATE "-framework OpenGL -framework Cocoa")
# endif()
if(WIN32)
  target_link_libraries(MyDemoApp PRIVATE opengl32)
endif()
