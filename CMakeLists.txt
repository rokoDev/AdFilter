set(cmake_version 3.13.1)

cmake_minimum_required(VERSION ${cmake_version})

set(AppName "AdFilter")

set(CC "/usr/bin/clang")
set(CXX "/usr/bin/clang++")

project(${AppName} 
		VERSION 1.0.0.0
		LANGUAGES CXX)
		
message(STATUS "cur c++ compiler is:${CMAKE_CXX_COMPILER}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-std=c++11 -O0 -fPIC -Wall")

set(INCLUDE_DIRS
	${CMAKE_SOURCE_DIR}/include
	)
set(HEADERS 
	${CMAKE_SOURCE_DIR}/include/AdFilter.h
	)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(SOURCES
	${SOURCE_DIR}/main.cpp
	${SOURCE_DIR}/AdFilter.cpp
	)

include_directories("${INCLUDE_DIRS}")

# Setup testing
enable_testing()
add_subdirectory(tests)

# Create application
add_executable(${AppName} ${SOURCES} ${HEADERS})
