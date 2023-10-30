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

target_link_libraries(tester ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} SDL2::SDL2)

include(GNUInstallDirs)
target_include_directories(${PROJECT_NAME}
	PUBLIC
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
	"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
add_subdirectory(src)

install(TARGETS ${PROJECT_NAME}
	EXPORT ${PROJECT_NAME}Targets
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
}
install(FILES sdl-shared.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT ${PROJECT_NAME}Targets
	FILE ${PROJECT_NAME}Targets.cmake
	NAMESPACE SDLShared::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
add_library(SDLShared::SDLShared STATIC IMPORTED)
set_target_properties(SDLShared::SDLShared PROPERTIES
	INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include"
)

set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)
export(PACKAGE sdl-shared)
