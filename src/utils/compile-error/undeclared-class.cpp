#include "../location.hpp"
#include "compile-error.hpp"
#include "undeclared-class.hpp"
#include <string>

UndeclaredClass::UndeclaredClass(const std::string& message, const Location& location) :
    CompileError(message, location) {
}
