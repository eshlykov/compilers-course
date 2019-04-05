#pragma once

#include <memory>
#include "node.hpp"
#include "type.hpp"

namespace Ast {

class VarDeclaration : public Node {
 public:
  VarDeclaration(Location location, std::unique_ptr<Type> type,
                 const std::string& name);

  void Accept(Visitor* visitor) final;

 public:
  const std::unique_ptr<Type> type_;
  const std::string name_;
};

inline VarDeclaration::VarDeclaration(Location location,
                                      std::unique_ptr<Type> type,
                                      const std::string& name)
    : type_{std::move(type)}, name_{name} {
  SetLocation(location);
  assert(type_ != nullptr);
}

inline void VarDeclaration::Accept(Visitor* visitor) { visitor->Visit(this); }

}  // namespace Ast
