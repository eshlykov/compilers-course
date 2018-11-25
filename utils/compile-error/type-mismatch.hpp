#pragma once

#include "../ast.hpp"
#include "../location.hpp"
#include "../source-code.hpp"
#include "compile-error.hpp"
#include <exception>
#include <string>
#include <variant>

class TypesMismatch : public CompileError {
    using TypeVariant = std::variant<TypeKind, std::string>;
public:
    TypesMismatch(const std::string& message, const Location& location);

    TypesMismatch(TypeVariant found, TypeVariant expected, const Location& location);

private:
    std::string TypeToString(TypeVariant& type);
};
