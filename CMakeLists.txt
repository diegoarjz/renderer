project("renderer" LANGUAGES CXX)
cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include("Renderer")

# Export compile comands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(png REQUIRED)
find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glew REQUIRED)
find_package(OpenGL REQUIRED)
find_library(COCOA_LIBRARY Cocoa)
find_library(IOKIT_LIBRARY IOKit)
find_library(CORE_VIDEO_LIBRARY CoreVideo)

add_subdirectory(source)

enable_testing()
add_subdirectory(tests)
