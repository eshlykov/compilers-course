#pragma once

#include <string>
#include "../location.hpp"
#include "compile-error.hpp"

class SelfInheritance : public CompileError {
 public:
  SelfInheritance(const std::string& message, const Location& location);
};

inline SelfInheritance::SelfInheritance(const std::string& message,
                                        const Location& location)
    : CompileError(message, location) {}
