#pragma once

#include <exception>

class CompileError : public std::exception {
public:
    CompileError(const std::string& message) :
        message_{message} {
    }

    virtual const char* what() override final {
        return message_.c_str();
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

class VariableRedefition : public CompileError {
public:
    VariableRefenition(const std::string& message) :
        CompileError(message) {
    }
};

class ArgumentRedefinition : public CompileError {
public:
    ArgumentRedefinition(const std::string& message) :
        CompileError(message) {
    }
};

class MethodRedefintion : public CompileError {
public:
    MethodRedefintion(const std::string& message) :
        CompileError(message) {
    }
};
