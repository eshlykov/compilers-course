#pragma once

#include "../../ast.hpp"
#include "../../location.hpp"
#include "variable-info.hpp"
#include <unordered_map>
#include <vector>

class MethodInfo {
public:
    void AddVariable(const std::string& name, VariableInfo variable, const Location& location);

    void AddArgument(const std::string& name, VariableInfo variable, const Location& location);

public:
    std::variant<TypeKind, std::string> returnType_;
    std::unordered_map<std::string, VariableInfo> variables_;
    std::vector<std::pair<std::string, VariableInfo>> arguments_;
};
