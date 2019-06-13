cmake_minimum_required(VERSION 3.8)

project(the_compiler)

include(cmake/ClangFormat.cmake)
include(cmake/ClangTidy.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

include_directories("src")

get_filename_component(ROOT "." ABSOLUTE)
get_filename_component(SRC "src" ABSOLUTE)

file(GLOB_RECURSE SOURCES ${SRC}/*.cpp)
file(GLOB_RECURSE HEADERS ${SRC}/*.h ${SRC}/*.hpp)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

flex_target(lexer ${SRC}/lexer.l ${SRC}/lexer.cpp)
bison_target(parser ${SRC}/parser.y ${SRC}/parser.cpp DEFINES_FILE ${SRC}/parser.hpp)

add_flex_bison_dependency(lexer parser)

add_executable(compiler ${SOURCES} ${BISON_parser_OUTPUTS} ${FLEX_lexer_OUTPUTS})

if (CLANG_FORMAT_TOOL)
    add_clang_format_target(
            compiler_clang_format
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${HEADERS} ${SOURCES})
endif ()

if (CLANG_TIDY_TOOL)
    add_clang_tidy_target(
            compiler_clang_tidy
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${SRC}
            ${HEADERS} ${SOURCES})
endif ()

add_custom_target(compiler_test COMMAND python3 "${ROOT}/test.py")
add_dependencies(compiler_test compiler)
