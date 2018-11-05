#pragma once

#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>

class MethodInfo {
public:
    MethodInfo() = default;

    void AddVariable(const std::string& name, VariableInfo variable) {
        if (variables_.find(name) == variables_.end()) {
            variables_[name] = variable;
        }
    }

    void AddArgument(const std::string& name, VariableInfo variable) {
        auto it = find_if(arguments_.begin(), arguments_.end(), [] (const auto& str) { return str.first == name; });
        if (it == arguments_.end()) {
            arguments_.push_back(std::make_pair(name, variable));
        }
    }

public:
    Type* returnType_ = {};
    std::unordered_map<std::string, VariableInfo> variables_ = {};
    std::vector<std::pair<std::string, VariableInfo>> arguments_ = {};
};

class VariableInfo {
public:
    Type* type = {};
};
