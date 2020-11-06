cmake_minimum_required(VERSION 3.18)
project(Bubo)

set(CMAKE_CXX_STANDARD 14)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(lib)
include_directories(include)

add_subdirectory(lib/glad)
add_subdirectory(src)
