#include "../../compile-error.hpp"
#include "method-info.hpp"
#include <algorithm>

void MethodInfo::AddVariable(const std::string& name, VariableInfo variable, const Location& location) {
    auto iter = find_if(arguments_.begin(), arguments_.end(), [&] (const auto& argument) { return argument.first == name; });
    if (variables_.find(name) != variables_.end() || iter != arguments_.end()) {
        throw VariableRedefinition{"variable '" + name + "' has been already defined", location};
    }
    variables_[name] = variable;
}

void MethodInfo::AddArgument(const std::string& name, VariableInfo variable, const Location& location) {
    auto iter = find_if(arguments_.begin(), arguments_.end(), [&] (const auto& argument) { return argument.first == name; });
    if (iter != arguments_.end()) {
        throw ArgumentRedefinition{"argument '" + name + "' has been already defined", location};
    }
    arguments_.emplace_back(name, variable);
}
