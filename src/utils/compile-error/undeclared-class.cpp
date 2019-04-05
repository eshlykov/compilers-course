#include "undeclared-class.hpp"
#include <string>
#include "../location.hpp"
#include "compile-error.hpp"

UndeclaredClass::UndeclaredClass(const std::string& message,
                                 const Location& location)
    : CompileError(message, location) {}
