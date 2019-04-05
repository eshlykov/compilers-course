#pragma once

#include <string>
#include <variant>
#include "node.hpp"

namespace Ast {

class Expression : public Node {
 public:
  void SetType(const std::variant<TypeKind, std::string> &type);

  std::variant<TypeKind, std::string> GetType() const;

 private:
  std::variant<TypeKind, std::string> type_;
};

inline void Expression::SetType(
    const std::variant<TypeKind, std::string> &type) {
  type_ = type;
}

inline std::variant<TypeKind, std::string> Expression::GetType() const {
  return type_;
}

}  // namespace Ast
