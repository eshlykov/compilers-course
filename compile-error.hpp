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
        std::string message = "\033[1;37m";
        message += sourceCode.GetFilename();
        message += ":" + std::to_string(location_.lineNumber_) + ":" + std::to_string(location_.firstColumn_);
        if (location_.lastColumn_ != location_.firstColumn_) {
            message += "-" + std::to_string(location_.lastColumn_);
        }
        message += ":";
        message += "\033[0m";
        message += "\033[1;31m error: \033[0m";
        message += "\033[1;37m" + message_ + "\033[0m";
        message += "\n" + sourceCode[location_.lineNumber_] + "\n";
        message += std::string(location_.firstColumn_ - 1, ' ');
        message += "\033[1;32m";
        message += "^";
        message += std::string(location_.lastColumn_ - location_.firstColumn_, '~');
        message += "\033[0m";
        return message;
    }

private:
    std::string message_ = {};
    Location location_ = {};
};

class ClassRedefinition : public CompileError {
public:
    ClassRedefinition(const std::string& message, const Location& location) :
        CompileError(message, location) {
    }
};

class VariableRedefinition : public CompileError {
public:
    VariableRedefinition(const std::string& message, const Location& location) :
        CompileError(message, location) {
    }
};

class ArgumentRedefinition : public CompileError {
public:
    ArgumentRedefinition(const std::string& message, const Location& location) :
        CompileError(message, location) {
    }
};

class MethodRedefinition : public CompileError {
public:
    MethodRedefinition(const std::string& message, const Location& location) :
        CompileError(message, location) {
    }
};
