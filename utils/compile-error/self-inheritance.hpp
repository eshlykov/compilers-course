#pragma once

#include "compile-error.hpp"
#include "../location.hpp"
#include <string>

class SelfInheritance : public CompileError {
public:
    SelfInheritance(const std::string& message, const Location& location);
};
