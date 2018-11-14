#include "class-info.hpp"

void ClassInfo::AddVariable(const std::string& name, VariableInfo variable) {
    if (variables_.find(name) != variables_.end()) {
        throw VariableRedefinition{"Variable " + name + " has been already defined."};
    }
    variables_[name] = variable;
}

void AddMethod(const std::string& name, MethodInfo method) {
    if (methods_.find(name) != methods_.end()) {
        throw MethodRedefinition{"Method " + name + " has been already defined."};
    }
    methods_[name] = method;
}
