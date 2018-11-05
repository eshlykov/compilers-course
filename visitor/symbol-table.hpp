#pragma once

#include <string>
#include <unordered_map>

class ClassInfo {
public:
    ClassInfo() = default;

    void AddVariable(const std::string& name, VariableInfo variable) {
        if (variables_.find(name) == variables_.end()) {
            variables_[name] = variable;
        }
    }

    void AddMethod(const std::string& name, MethodInfo method) {
        if (methods_.find(name) == methods_.end()) {
            methods_[name] = method;
        }
    }

public:
    std::unordered_map<std::string, VariableInfo> variables_ = {};
    std::unordered_map<std::string, MethodInfo> methods_ = {};
};
