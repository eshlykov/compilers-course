#pragma once

#include <string>
#include "../location.hpp"
#include "compile-error.hpp"

class VariableRedefinition : public CompileError {
 public:
  VariableRedefinition(const std::string& message, const Location& location);
};

inline VariableRedefinition::VariableRedefinition(const std::string& message,
                                                  const Location& location)
    : CompileError(message, location) {}
