cmake_minimum_required(VERSION 3.10)

project(y1)
add_definitions(-DY1_SO_EXPORTS)

if (CMAKE_SYSTEM_NAME MATCHES Linux)
	add_compile_options(-std=c++11)
elseif (Windows)
endif()
include_directories( ${incPath})

set(mySourceFiles y1.c)
set(myHeaderFiles y1.h)

if(MSVC)
set(libsToLink)
endif()

#set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)
#set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)
#set(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)

link_directories(${LinkDir})
link_libraries(${libsToLink})

add_library(y1 SHARED ${mySourceFiles} ${myHeaderFiles})

set_target_properties(y1 PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin
	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)


