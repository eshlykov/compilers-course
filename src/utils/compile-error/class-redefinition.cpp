#include <string>
#include "../location.hpp"
#include "class-redefenition.hpp"
#include "compile-error.hpp"

ClassRedefinition::ClassRedefinition(const std::string& message,
                                     const Location& location)
    : CompileError(message, location) {}
