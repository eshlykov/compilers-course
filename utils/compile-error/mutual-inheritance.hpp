#pragma once

#include "compile-error.hpp"
#include "../location.hpp"
#include <string>

class MutualInheritance : public CompileError {
public:
    MutualInheritance(const std::string& message, const Location& location);
};
