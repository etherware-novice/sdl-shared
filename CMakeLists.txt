cmake_minimum_required(VERSION 3.13)
project(sdl-shared)

add_library(${PROJECT_NAME} STATIC "")

include_directories(${SDL2_INCLUDE_DIRS})

include_directories(include)
add_subdirectory(src)
