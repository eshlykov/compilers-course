cmake_minimum_required(VERSION 3.13)

project(the_compiler)

include(cmake/ClangFormat.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

get_filename_component(SRC "src" ABSOLUTE)

file(GLOB_RECURSE SOURCES ${SRC}/*.cpp)
file(GLOB_RECURSE HEADERS ${SRC}/*.cpp)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

flex_target(lexer ${SRC}/lexer.l ${SRC}/lexer.cpp)
bison_target(parser ${SRC}/parser.y ${SRC}/parser.cpp DEFINES_FILE ${SRC}/parser.hpp)

add_flex_bison_dependency(lexer parser)

add_executable(compiler ${SOURCES})

if (CLANG_FORMAT_TOOL)
    add_clang_format_target(
            parakeet_clang_format
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${HEADERS} ${SOURCES})
endif ()
