#pragma once

#include <string>
#include "../location.hpp"
#include "compile-error.hpp"

class UndeclaredClass : public CompileError {
 public:
  UndeclaredClass(const std::string &message, const Location &location);
};

inline UndeclaredClass::UndeclaredClass(const std::string &message,
                                        const Location &location)
    : CompileError(message, location) {}
