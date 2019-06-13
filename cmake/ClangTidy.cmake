find_program(CLANG_TIDY_TOOL
        NAMES clang-tidy
        clang-tidy-7.0
        clang-tidy-6.0
        clang-tidy-5.0)

function(add_clang_tidy_target NAME CWD INCLUDES)
    add_custom_target(${NAME}
            COMMAND ${CLANG_TIDY_TOOL} --quiet ${ARGN} -- -std=c++17 -I ${INCLUDES}
            WORKING_DIRECTORY ${CWD}
            COMMENT "Applying clang-tidy")
endfunction()
