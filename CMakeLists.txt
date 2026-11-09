cmake_minimum_required(VERSION 3.21)
project(LanDrop VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(core)   # backend library (no Qt)
add_subdirectory(cli)    # terminal tool for testing the backend
# add_subdirectory(gui)  # Qt window, comes in step 5
