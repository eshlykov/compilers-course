#pragma once

#include <string>
#include "../location.hpp"
#include "compile-error.hpp"

class ArgumentRedefinition : public CompileError {
 public:
  ArgumentRedefinition(const std::string& message, const Location& location);
};
