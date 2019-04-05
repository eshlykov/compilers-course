#pragma once

#include "compile-error.hpp"
#include "../location.hpp"
#include <string>

class UndeclaredMethod : public CompileError {
public:
    UndeclaredMethod(const std::string& message, const Location& location);
};
