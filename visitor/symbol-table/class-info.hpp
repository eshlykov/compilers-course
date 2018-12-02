#pragma once

#include "../../utils/location.hpp"
#include "method-info.hpp"
#include "variable-info.hpp"
#include <unordered_map>
#include <optional>

class ClassInfo {
public:
    void AddVariable(const std::string& name, VariableInfo variable, const Location& location);

    void AddMethod(const std::string& name, MethodInfo method, const Location& location);

    const std::optional<std::string>& GetBase() const;

    const std::unordered_map<std::string, VariableInfo>& GetVariables() const;

    const std::unordered_map<std::string, MethodInfo>& GetMethods() const;

    void SetBase(std::string base);

private:
    std::optional<std::string> base_;
    std::unordered_map<std::string, VariableInfo> variables_;
    std::unordered_map<std::string, MethodInfo> methods_;
};
