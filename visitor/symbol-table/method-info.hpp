#pragma once

#include "variable-info.hpp"
#include <unordered_map>
#include <vector>

class MethodInfo {
public:
    void AddVariable(const std::string& name, VariableInfo variable);

    void AddArgument(const std::string& name, VariableInfo variable);

public:
    Type* returnType_ = {};
    std::unordered_map<std::string, VariableInfo> variables_ = {};
    std::vector<std::pair<std::string, VariableInfo>> arguments_ = {};
};
