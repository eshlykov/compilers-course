#include "method-redefenition.hpp"
#include "../location.hpp"
#include <string>

MethodRedefinition::MethodRedefinition(const std::string& message, const Location& location) :
    CompileError(message, location) {
}
