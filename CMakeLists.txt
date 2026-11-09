cmake_minimum_required(VERSION 3.16)
project(LanDrop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(landrop cli/main.cpp)
target_include_directories(landrop PRIVATE core)
