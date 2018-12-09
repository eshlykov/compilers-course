#pragma once

#include "../location.hpp"
#include "../source-code.hpp"
#include <exception>
#include <string>
#include <variant>

class CompileError {
public:
    CompileError(const std::string& message, const Location& location);

    ~CompileError() = default;

    virtual std::string GetMessage(const SourceCode& sourceCode) const final;

private:
    std::string message_;
    Location location_;
};
