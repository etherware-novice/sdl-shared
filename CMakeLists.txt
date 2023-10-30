cmake_minimum_required(VERSION 3.13)
project(sdl-shared)

if(NOT DEFINED ASSET_PATH)
	set(ASSET_PATH "assets")
endif()
add_compile_definitions(ASSET_PATH="${ASSET_PATH}")

find_package(SDL2 REQUIRED)

# empty string states no dependecies, is added later in src cmakelist
add_library(${PROJECT_NAME} STATIC "")
add_executable(tester "")

target_link_libraries(tester ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} SDL2::SDL2)

include_directories(include)
add_subdirectory(src)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME} EXPORT main DESTINATION bin)
install(EXPORT main DESTINATION lib/main)
