#pragma once

#include "../location.hpp"
#include "compile-error.hpp"
#include <string>

class UndeclaredClass : public CompileError {
public:
    UndeclaredClass(const std::string& message, const Location& location);
};
