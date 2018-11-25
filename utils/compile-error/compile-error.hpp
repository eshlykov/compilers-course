#pragma once

#include "../ast.hpp"
#include "../location.hpp"
#include "../source-code.hpp"
#include <exception>
#include <string>
#include <variant>

#include <iostream>

class CompileError {
public:
    CompileError(const std::string& message, const Location& location);

    ~CompileError() = default;

    virtual std::string GetMessage(const SourceCode& sourceCode) const final;

private:
    std::string message_ = {};
    Location location_ = {};
};

class UndeclaredMethod : public CompileError {
public:
    UndeclaredMethod(const std::string& message, const Location& location) :
        CompileError(message, location) {
    }
};

class ArgumentsCountMismatch : public CompileError {
public:
    ArgumentsCountMismatch(const std::string& message, const Location& location) :
        CompileError(message, location) {
    }
};

class MutualInheritance : public CompileError {
public:
    MutualInheritance(const std::string& message, const Location& location) :
        CompileError(message, location) {
    }
};

class SelfInheritance : public CompileError {
public:
    SelfInheritance(const std::string& message, const Location& location) :
        CompileError(message, location) {
    }
};
