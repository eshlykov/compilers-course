#pragma once

#include "ast.hpp"
#include "location.hpp"
#include "source-code.hpp"
#include "compile-error.hpp"
#include <string>

class ClassRedefinition : public CompileError {
public:
    ClassRedefinition(const std::string& message, const Location& location);
};
