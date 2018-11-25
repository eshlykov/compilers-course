#include "undeclared-variable.hpp"
#include "compile-error.hpp"
#include "../location.hpp"


UndeclaredVariable::UndeclaredVariable(const std::string& message, const Location& location) :
    CompileError(message, location) {
}
