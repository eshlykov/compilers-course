#include "undeclared-method.hpp"
#include <string>
#include "../location.hpp"
#include "compile-error.hpp"

UndeclaredMethod::UndeclaredMethod(const std::string& message,
                                   const Location& location)
    : CompileError(message, location) {}
