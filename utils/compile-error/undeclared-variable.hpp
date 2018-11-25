#pragma once

#include "compile-error.hpp"
#include "../location.hpp"

class UndeclaredVariable : public CompileError {
public:
    UndeclaredVariable(const std::string& message, const Location& location);
};
