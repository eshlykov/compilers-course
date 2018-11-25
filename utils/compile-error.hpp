#pragma once

#include "ast.hpp"
#include "location.hpp"
#include "source-code.hpp"
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
