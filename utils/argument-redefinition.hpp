#pragma once

#include "ast.hpp"
#include "location.hpp"
#include <string>

class ArgumentRedefinition : public CompileError {
public:
    ArgumentRedefinition(const std::string& message, const Location& location);
};
