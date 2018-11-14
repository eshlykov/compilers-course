#pragma once

#include "variable-info.hpp"
#include "method-info.hpp"
#include <unordered_map>

class ClassInfo {
public:
    void AddVariable(const std::string& name, VariableInfo variable);

    void AddMethod(const std::string& name, MethodInfo method);

public:
    std::optional<std::string> base_ = {};
    std::unordered_map<std::string, VariableInfo> variables_ = {};
    std::unordered_map<std::string, MethodInfo> methods_ = {};
};