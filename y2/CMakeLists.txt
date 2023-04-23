cmake_minimum_required(VERSION 3.10)

project(y2)
add_definitions(-DY2_SO_EXPORTS)

if (CMAKE_SYSTEM_NAME MATCHES Linux)
	add_compile_options(-std=c++11)
elseif (Windows)
endif()
include_directories( ${incPath})

set(mySourceFiles y2.cpp)
set(myHeaderFiles y2.h)

if(MSVC)
set(libsToLink)
endif()

link_directories(${LinkDir})
link_libraries(${libsToLink})

add_library(y2 SHARED ${mySourceFiles} ${myHeaderFiles})

set_target_properties(y2 PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin
	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)

