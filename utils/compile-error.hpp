#pragma once

#include "ast.hpp"
#include "location.hpp"
#include "source-code.hpp"
#include <exception>
#include <string>
#include <variant>

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

class TypesMismatch : public CompileError {
    using TypeVariant = std::variant<TypeKind, std::string>;
public:
    TypesMismatch(const std::string& message, const Location& location) :
        CompileError(message, location) {
    }

    TypesMismatch(TypeVariant found, TypeVariant expected, const Location& location) :
        CompileError("types mismatch: expected " + TypeToString(expected) + ", found " +  TypeToString(found), location) {
    }

private:
    std::string TypeToString(TypeVariant& type) {
        try {
            switch (std::get<TypeKind>(type)) {
            case TypeKind::TK_Undefined:
                return "type is undefined";
            case TypeKind::TK_IntArray:
                return "'int[]'";
            case TypeKind::TK_Int:
                return "'int'";
            case TypeKind::TK_Boolean:
                return "'boolean'";
            }
        } catch (const std::bad_variant_access&) {
            return "'" + std::get<std::string>(type) + "'";
        }
    }
};

class UndeclaredVariable : public CompileError {
public:
    UndeclaredVariable(const std::string& message, const Location& location) :
        CompileError(message, location) {
    }
};

class UndeclaredClass : public CompileError {
public:
    UndeclaredClass(const std::string& message, const Location& location) :
        CompileError(message, location) {
    }
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
