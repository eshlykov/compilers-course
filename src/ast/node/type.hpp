#pragma once

#include <string>
#include <variant>
#include "node.hpp"

namespace Ast {

class Type : public Node {
 public:
  Type(Location location, const std::string& className);

  Type(Location location, TypeKind typeKind);

  void Accept(Visitor* visitor) final;

 public:
  const std::variant<TypeKind, std::string> type_;
};

inline Type::Type(Location location, const std::string& className)
    : type_{className} {
  SetLocation(location);
}

inline Type::Type(Location location, TypeKind typeKind) : type_{typeKind} {
  SetLocation(location);
}

inline void Type::Accept(Visitor* visitor) { visitor->Visit(this); }

}  // namespace Ast
