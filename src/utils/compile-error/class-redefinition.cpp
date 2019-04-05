#include "../location.hpp"
#include "class-redefenition.hpp"
#include "compile-error.hpp"
#include <string>

ClassRedefinition::ClassRedefinition(const std::string& message, const Location& location) :
    CompileError(message, location) {
}
