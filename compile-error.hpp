#pragma once

#include <exception>
#include <string>

class CompileError {
public:
    CompileError(const std::string& message) :
        message_{message} {
    }

    virtual std::string GetMessage() const final {
        return message_;
    }

private:
    std::string message_ = {};
};

class ClassRedefinition : public CompileError {
public:
    ClassRedefinition(const std::string& message) :
        CompileError(message) {
    }
};

class VariableRedefinition : public CompileError {
public:
    VariableRedefinition(const std::string& message) :
        CompileError(message) {
    }
};

class ArgumentRedefinition : public CompileError {
public:
    ArgumentRedefinition(const std::string& message) :
        CompileError(message) {
    }
};

class MethodRedefinition : public CompileError {
public:
    MethodRedefinition(const std::string& message) :
        CompileError(message) {
    }
};
