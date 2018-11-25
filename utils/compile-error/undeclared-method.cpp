#include "compile-error.hpp"
#include "undeclared-method.hpp"
#include "../location.hpp"
#include <string>

UndeclaredMethod::UndeclaredMethod(const std::string& message, const Location& location) :
    CompileError(message, location) {
}
