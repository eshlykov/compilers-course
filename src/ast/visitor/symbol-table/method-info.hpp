#pragma once

#include <unordered_map>
#include <vector>
#include "../../../utils/ast.hpp"
#include "../../../utils/location.hpp"
#include "variable-info.hpp"

namespace Ast {

class MethodInfo {
 public:
  void AddVariable(const std::string &name, VariableInfo variable,
                   const Location &location);

  void AddArgument(const std::string &name, VariableInfo variable,
                   const Location &location);

  const std::variant<TypeKind, std::string> &GetReturnType() const;

  const std::unordered_map<std::string, VariableInfo> &GetVariables() const;

  const std::vector<std::pair<std::string, VariableInfo>> &GetArguments() const;

  void SetReturnType(const std::variant<TypeKind, std::string> &returnType);

 private:
  std::variant<TypeKind, std::string> returnType_;
  std::unordered_map<std::string, VariableInfo> variables_;
  std::vector<std::pair<std::string, VariableInfo>> arguments_;
};

}  // namespace Ast
