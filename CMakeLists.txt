cmake_minimum_required(VERSION 3.19)
project(WillogProj LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GCC_COVERAGE_COMPILE_FLAGS "/utf-8")
set(CMAKE_CXX_FLAGS "${GCC_COVERAGE_COMPILE_FLAGS}" )

include_directories(include)

add_subdirectory(test)