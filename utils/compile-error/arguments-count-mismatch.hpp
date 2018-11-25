#pragma once

#include "compile-error.hpp"
#include "../location.hpp"
#include <string>

class ArgumentsCountMismatch : public CompileError {
public:
    ArgumentsCountMismatch(const std::string& message, const Location& location);
};
