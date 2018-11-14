#include "method-info.hpp"

void MethodInfo::AddVariable(const std::string& name, VariableInfo variable) {
    auto iter = find_if(arguments_.begin(), arguments_.end(), [&] (const auto& argument) { return argument.first == name; });
    if (variables_.find(name) != variables_.end() || iter != arguments_.end()) {
        throw VariableRedefinition{"Variable " + name + " has been already defined."};
    }
    variables_[name] = variable;
}

void MethodInfo::AddArgument(const std::string& name, VariableInfo variable) {
    auto iter = find_if(arguments_.begin(), arguments_.end(), [&] (const auto& argument) { return argument.first == name; });
    if (iter != arguments_.end()) {
        throw ArgumentRedefinition{"Argument " + name + " has been already defined."};
    }
    arguments_.emplace_back(name, variable);
}