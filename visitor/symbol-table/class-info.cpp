#include "../../utils/compile-error/compile-error.hpp"
#include "../../utils/compile-error/variable-redefinition.hpp"
#include "../../utils/compile-error/method-redefenition.hpp"
#include "class-info.hpp"


void ClassInfo::AddVariable(const std::string& name, VariableInfo variable, const Location& location) {
    if (variables_.find(name) != variables_.end()) {
        throw VariableRedefinition{"variable '" + name + "' has been already defined", location};
    }
    variables_[name] = variable;
}

void ClassInfo::AddMethod(const std::string& name, MethodInfo method, const Location& location) {
    if (methods_.find(name) != methods_.end()) {
        throw MethodRedefinition{"method '" + name + "' has been already defined", location};
    }
    methods_[name] = method;
}
