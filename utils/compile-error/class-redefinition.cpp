#include "class-redefenition.hpp"
#include "compile-error.hpp"
#include "../location.hpp"
#include <string>

ClassRedefinition::ClassRedefinition(const std::string& message, const Location& location) :
    CompileError(message, location) {
}
