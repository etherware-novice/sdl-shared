cmake_minimum_required(VERSION 3.13)
project(sdl-shared)

find_package(SDL2 REQUIRED)

add_library(${PROJECT_NAME} STATIC "")
add_executable(tester "")

target_link_libraries(tester ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} SDL2::SDL2)

include_directories(${SDL2_INCLUDE_DIRS})

include_directories(include)
add_subdirectory(src)

