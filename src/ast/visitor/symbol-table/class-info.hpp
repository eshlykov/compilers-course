#pragma once

#include <optional>
#include <unordered_map>
#include "../../../utils/location.hpp"
#include "method-info.hpp"
#include "variable-info.hpp"

namespace Ast {

class ClassInfo {
 public:
  ClassInfo();

  void AddVariable(const std::string& name, VariableInfo variable,
                   const Location& location);

  void AddMethod(const std::string& name, MethodInfo method,
                 const Location& location);

  const std::optional<std::string>& GetBase() const;

  const std::unordered_map<std::string, VariableInfo>& GetVariables() const;

  const std::unordered_map<std::string, MethodInfo>& GetMethods() const;

  size_t GetSize() const;

  void SetBase(std::string base);

  void UpdateVariableOffsets(int additionalOffset);

 private:
  std::optional<std::string> base_;
  std::unordered_map<std::string, VariableInfo> variables_;
  std::unordered_map<std::string, MethodInfo> methods_;
  bool are_offsets_updated_;
};

}  // namespace Ast
