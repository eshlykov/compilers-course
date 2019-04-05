#pragma once

#include <string>
#include "../location.hpp"
#include "compile-error.hpp"

class MethodRedefinition : public CompileError {
 public:
  MethodRedefinition(const std::string& message, const Location& location);
};
