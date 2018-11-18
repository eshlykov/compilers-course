#pragma once

#include "location.hpp"
#include "source-code.hpp"
#include <exception>
#include <string>

class CompileError {
public:
    CompileError(const std::string& message, const Location& location) :
        message_{message}, location_{location} {
    }

    ~CompileError() = default;

    virtual std::string GetMessage(const SourceCode& sourceCode) const final {
        mesage = sourceCode.GetFileName();
        message += "\033[1;37m";
        message += ": " + std::to_string{location_.lineNumber_} + ":" + std::to_string{location_.firstColumn_};
        if (location_.lastColumn_ != location.firstColumn_) {
            message += "-" + std::to_string{location_.lastColumn_};
        }
        message += "\033[0m";
        message += "\033[1;31m" + " error: " + "\033[0m";
        message += "\033[1;37m" + message_ + "\033[0m";
        message += "\n" + sourceeCode[location_.lineNumber_] + "\n";
        message +=  std::string(yylloc.first_column - 1, ' ');
        message +=  "\033[1;32m";
        message += "^";
        message += std::string(location.lastColumn - yylloc.firstColumn_, '~');
        message += "\033[0m";
        return message;
    }

private:
    std::string message_ = {};
    Location location_ = {};
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
