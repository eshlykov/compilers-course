#pragma once

#include "compile-error.hpp"
#include "../location.hpp"
#include <string>

class UndeclaredClass : public CompileError {
public:
    UndeclaredClass(const std::string& message, const Location& location);
};
