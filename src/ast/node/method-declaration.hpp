#pragma once

#include <memory>
#include <string>
#include <vector>
#include "method-body.hpp"
#include "node.hpp"
#include "type.hpp"
#include "var-declaration.hpp"

namespace Ast {

class MethodDeclaration : public Node {
 public:
  MethodDeclaration(Location location, std::unique_ptr<Type> resultType,
                    std::string methodName,
                    std::vector<std::unique_ptr<VarDeclaration>>& argumentsList,
                    std::unique_ptr<MethodBody> methodBody);

  void Accept(Visitor* visitor) final;

 public:
  const std::unique_ptr<Type> resultType_;
  const std::string methodName_;
  const std::vector<std::unique_ptr<VarDeclaration>> argumentsList_;
  const std::unique_ptr<MethodBody> methodBody_;
};

inline MethodDeclaration::MethodDeclaration(
    Location location, std::unique_ptr<Type> resultType, std::string methodName,
    std::vector<std::unique_ptr<VarDeclaration>>& argumentsList,
    std::unique_ptr<MethodBody> methodBody)
    : resultType_{std::move(resultType)},
      methodName_{std::move(methodName)},
      argumentsList_{std::move(argumentsList)},
      methodBody_{std::move(methodBody)} {
  SetLocation(location);
  assert(resultType_ != nullptr);
  assert(methodBody_ != nullptr);
}

inline void MethodDeclaration::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

}  // namespace Ast
