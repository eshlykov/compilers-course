#include "method-redefenition.hpp"
#include <string>
#include "../location.hpp"

MethodRedefinition::MethodRedefinition(const std::string& message,
                                       const Location& location)
    : CompileError(message, location) {}
