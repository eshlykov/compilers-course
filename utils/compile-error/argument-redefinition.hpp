#pragma once

#include "../location.hpp"
#include "compile-error.hpp"
#include <string>

class ArgumentRedefinition : public CompileError {
public:
    ArgumentRedefinition(const std::string& message, const Location& location);
};
