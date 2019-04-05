#pragma once

#include <exception>
#include <string>
#include <variant>
#include "../ast.hpp"
#include "../location.hpp"
#include "../source-code.hpp"
#include "compile-error.hpp"

class TypesMismatch : public CompileError {
  using TypeVariant = std::variant<Ast::TypeKind, std::string>;

 public:
  TypesMismatch(const std::string& message, const Location& location);

  TypesMismatch(TypeVariant found, TypeVariant expected,
                const Location& location);

 private:
  std::string TypeToString(TypeVariant& type);
};

inline TypesMismatch::TypesMismatch(const std::string& message,
                                    const Location& location)
    : CompileError(message, location) {}

inline TypesMismatch::TypesMismatch(TypeVariant found, TypeVariant expected,
                                    const Location& location)
    : CompileError("types mismatch: expected " + TypeToString(expected) +
                       ", found " + TypeToString(found),
                   location) {}

inline std::string TypesMismatch::TypeToString(TypeVariant& type) {
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
