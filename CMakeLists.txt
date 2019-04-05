cmake_minimum_required(VERSION 3.13)

project(the_compiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

get_filename_component(SRC "src" ABSOLUTE)

file(GLOB_RECURSE SOURCES ${SRC}/*.cpp)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

flex_target(lexer ${SRC}/lexer.l ${SRC}/lexer.cpp)
bison_target(parser ${SRC}/parser.y ${SRC}/parser.cpp DEFINES_FILE ${SRC}/parser.hpp)

add_flex_bison_dependency(lexer parser)

add_executable(compiler ${SOURCES})
