#pragma once

#include "compile-error.hpp"
#include "../location.hpp"
#include <string>

class MethodRedefinition : public CompileError {
public:
    MethodRedefinition(const std::string& message, const Location& location);
};
