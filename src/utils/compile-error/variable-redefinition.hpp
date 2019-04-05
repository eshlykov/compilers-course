#pragma once

#include "../location.hpp"
#include "compile-error.hpp"
#include <string>

class VariableRedefinition : public CompileError {
public:
    VariableRedefinition(const std::string& message, const Location& location);
};
