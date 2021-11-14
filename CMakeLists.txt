cmake_minimum_required(VERSION 3.16.0)

project(HelloWinBuild VERSION 0.1.0)

set(C_STANDARD_REQUIRED TRUE)
set(CXX_STANDARD_REQUIRED TRUE)
set(C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

add_executable(HelloWin testme.cpp)
