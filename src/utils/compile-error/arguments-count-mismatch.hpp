#pragma once

#include <string>
#include "../location.hpp"
#include "compile-error.hpp"

class ArgumentsCountMismatch : public CompileError {
 public:
  ArgumentsCountMismatch(const std::string& message, const Location& location);
};

inline ArgumentsCountMismatch::ArgumentsCountMismatch(
    const std::string& message, const Location& location)
    : CompileError(message, location) {}
