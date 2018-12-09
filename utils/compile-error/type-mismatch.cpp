#include "type-mismatch.hpp"
#include "../ast.hpp"
#include "../location.hpp"
#include "compile-error.hpp"
#include <exception>
#include <string>
#include <variant>

TypesMismatch::TypesMismatch(const std::string& message, const Location& location) :
    CompileError(message, location) {
}

TypesMismatch::TypesMismatch(TypeVariant found, TypeVariant expected, const Location& location) :
    CompileError("types mismatch: expected " + TypeToString(expected) + ", found " +  TypeToString(found), location) {
}

std::string TypesMismatch::TypeToString(TypeVariant& type) {
    try {
        switch (std::get<TypeKind>(type)) {
            case TypeKind::Undefined:
                return "type is undefined";
            case TypeKind::IntArray:
                return "'int[]'";
            case TypeKind::Int:
                return "'int'";
            case TypeKind::Boolean:
                return "'boolean'";
        }
    } catch (const std::bad_variant_access&) {
        return "'" + std::get<std::string>(type) + "'";
    }
}
