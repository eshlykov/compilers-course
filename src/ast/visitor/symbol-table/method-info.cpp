#include "method-info.hpp"
#include <algorithm>
#include "../../../utils/compile-error/argument-redefinition.hpp"
#include "../../../utils/compile-error/compile-error.hpp"
#include "../../../utils/compile-error/method-redefinition.hpp"
#include "../../../utils/compile-error/variable-redefinition.hpp"

namespace Ast {

void MethodInfo::AddVariable(const std::string& name, VariableInfo variable,
                             const Location& location) {
  auto iter =
      find_if(arguments_.begin(), arguments_.end(),
              [&](const auto& argument) { return argument.first == name; });
  if (variables_.find(name) != variables_.end() || iter != arguments_.end()) {
    throw VariableRedefinition{
        "variable '" + name + "' has been already defined", location};
  }
  variables_[name] = std::move(variable);
}

void MethodInfo::AddArgument(const std::string& name,
                             const VariableInfo& variable,
                             const Location& location) {
  auto iter =
      find_if(arguments_.begin(), arguments_.end(),
              [&](const auto& argument) { return argument.first == name; });
  if (iter != arguments_.end()) {
    throw ArgumentRedefinition{
        "argument '" + name + "' has been already defined", location};
  }
  arguments_.emplace_back(name, variable);
}

const std::variant<TypeKind, std::string>& MethodInfo::GetReturnType() const {
  return returnType_;
}

const std::unordered_map<std::string, VariableInfo>& MethodInfo::GetVariables()
    const {
  return variables_;
}

const std::vector<std::pair<std::string, VariableInfo>>&
MethodInfo::GetArguments() const {
  return arguments_;
}

void MethodInfo::SetReturnType(
    const std::variant<TypeKind, std::string>& returnType) {
  returnType_ = returnType;
}

}  // namespace Ast
