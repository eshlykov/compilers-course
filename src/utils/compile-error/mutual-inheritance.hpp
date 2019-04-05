#pragma once

#include <string>
#include "../location.hpp"
#include "compile-error.hpp"

class MutualInheritance : public CompileError {
 public:
  MutualInheritance(const std::string& message, const Location& location);
};
