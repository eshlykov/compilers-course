#pragma once

#include <string>
#include "../location.hpp"
#include "../source-code.hpp"
#include "compile-error.hpp"

class ClassRedefinition : public CompileError {
 public:
  ClassRedefinition(const std::string& message, const Location& location);
};
