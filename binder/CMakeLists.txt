cmake_minimum_required(VERSION 3.10)

project(cpp_demo)

if($ENV{RUNTIME_BINDING})
	add_definitions(-D_SO_RUNTIME_BINDING)
	set(exeSuffix runtime_binding)
	set(runtimeBinding 1)
	message("Runtime binding")
else()
	add_definitions(-U_SO_RUNTIME_BINDING)
	set(exeSuffix static_binding)
	message("Static binding")
endif()

message("CMAKE_IMPORT_LIBRARY_SUFFIX = ${CMAKE_IMPORT_LIBRARY_SUFFIX}")
#message("CMAKE_LINK_LIBRARY_SUFFIX = ${CMAKE_LINK_LIBRARY_SUFFIX}")
#message("CMAKE_SHARED_LIBRARY_SUFFIX = ${CMAKE_SHARED_LIBRARY_SUFFIX}")
#message("CMAKE_SHARED_LIBRARY_PREFIX = ${CMAKE_SHARED_LIBRARY_PREFIX}")

if (CMAKE_SYSTEM_NAME MATCHES Linux)
	add_definitions(-DLINUX)
	add_compile_options(-std=c++11)
elseif (Windows)
endif()
include_directories(../y1 ../y2)

set(mySourceFiles main.cpp)
if(runtimeBinding)
	set(mySourceFiles ${mySourceFiles} classes.cpp)
endif()
set(myHeaderFiles dynload.hpp)

add_executable(cpp_demo_${exeSuffix} ${mySourceFiles} ${myHeaderFiles})
set_target_properties(cpp_demo_${exeSuffix} PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin
	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)

function(importLibrary outVar libName)
	set(t lib${libName})
	set(y ${CMAKE_CURRENT_SOURCE_DIR}/../bin/${CMAKE_SHARED_LIBRARY_PREFIX}${libName})
	if(CMAKE_IMPORT_LIBRARY_SUFFIX)
		set(y ${y}${CMAKE_IMPORT_LIBRARY_SUFFIX})
		add_library(${t} STATIC IMPORTED)
	else()
		set(y ${y}${CMAKE_SHARED_LIBRARY_SUFFIX})
		add_library(${t} SHARED IMPORTED)
	endif()
#	message("y = ${y}")
#	set(${outVar} ${y} PARENT_SCOPE)
	set_target_properties(${t} PROPERTIES IMPORTED_LOCATION ${y})
endfunction()

if("${exeSuffix}" STREQUAL static_binding)
	importLibrary(y y1)
	importLibrary(y y2)
	target_link_libraries(cpp_demo_${exeSuffix} liby1 liby2)
endif()

if (CMAKE_SYSTEM_NAME MATCHES Linux)
	target_link_libraries(cpp_demo_${exeSuffix} -ldl)
endif()

