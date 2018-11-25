#pragma once

#include "compile-error/compile-error.hpp"

class Program;

class ParserArgs {
public:
    std::unique_ptr<Program> program_;
    std::vector<CompileError> errors_;
};
