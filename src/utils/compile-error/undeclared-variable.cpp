#include "undeclared-variable.hpp"
#include "../location.hpp"
#include "compile-error.hpp"

UndeclaredVariable::UndeclaredVariable(const std::string& message,
                                       const Location& location)
    : CompileError(message, location) {}
