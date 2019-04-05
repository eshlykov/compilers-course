#include "variable-redefinition.hpp"

VariableRedefinition::VariableRedefinition(const std::string& message,
                                           const Location& location)
    : CompileError(message, location) {}
