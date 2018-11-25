#include "undeclared-class.hpp"
#include "compile-error.hpp"
#include "../location.hpp"
#include <string>

UndeclaredClass::UndeclaredClass(const std::string& message, const Location& location) :
    CompileError(message, location) {
}
