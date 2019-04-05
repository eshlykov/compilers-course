#pragma once

#include "../location.hpp"
#include "compile-error.hpp"

class UndeclaredVariable : public CompileError {
 public:
  UndeclaredVariable(const std::string &message, const Location &location);
};

inline UndeclaredVariable::UndeclaredVariable(const std::string &message,
                                              const Location &location)
    : CompileError(message, location) {}
