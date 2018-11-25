#pragma once

#include "compile-error.hpp"
#include "location.hpp"
#include <string>

class VariableRedefinition : public CompileError {
public:
    VariableRedefinition(const std::string& message, const Location& location);
};
