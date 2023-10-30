cmake_minimum_required(VERSION 3.15)
project(sdl-shared VERSION 0.1)

if(NOT DEFINED ASSET_PATH)
	set(ASSET_PATH "assets")
endif()
add_compile_definitions(ASSET_PATH="${ASSET_PATH}")

find_package(SDL2 REQUIRED)

# empty string states no dependecies, is added later in src cmakelist
add_library(${PROJECT_NAME} STATIC "")
add_executable(tester "")
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "sdl-shared.h")

target_link_libraries(tester ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} SDL2::SDL2)

include_directories(include)
add_subdirectory(src)

export(TARGETS ${PROJECT_NAME} NAMESPACE SDLShared:: FILE sdl-shared.cmake)
set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)
export(PACKAGE sdl-shared)
