#pragma once

#include <string>
#include "../location.hpp"
#include "compile-error.hpp"

class UndeclaredMethod : public CompileError {
 public:
  UndeclaredMethod(const std::string &message, const Location &location);
};

inline UndeclaredMethod::UndeclaredMethod(const std::string &message,
                                          const Location &location)
    : CompileError(message, location) {}
