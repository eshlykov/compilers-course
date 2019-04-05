#include "type-mismatch.hpp"

TypesMismatch::TypesMismatch(const std::string& message, const Location& location) :
    CompileError(message, location) {
}

TypesMismatch::TypesMismatch(TypeVariant found, TypeVariant expected, const Location& location) :
    CompileError("types mismatch: expected " + TypeToString(expected) + ", found " +  TypeToString(found), location) {
}

std::string TypesMismatch::TypeToString(TypeVariant& type) {
    try {
        switch (std::get<Ast::TypeKind>(type)) {
            case Ast::TypeKind::Undefined:
                return "type is undefined";
            case Ast::TypeKind::IntArray:
                return "'int[]'";
            case Ast::TypeKind::Int:
                return "'int'";
            case Ast::TypeKind::Boolean:
                return "'boolean'";
        }
    } catch (const std::bad_variant_access&) {
        return "'" + std::get<std::string>(type) + "'";
    }
}
