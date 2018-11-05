#pragma once

#include <algorithm>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class ClassInfo {
public:
    void AddVariable(const std::string& name, VariableInfo variable) {
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

public:
    std::optional<std::string> base_ = {};
    std::unordered_map<std::string, VariableInfo> variables_ = {};
    std::unordered_map<std::string, MethodInfo> methods_ = {};
};

class MethodInfo {
public:
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

class SymbolTable : public Visitor {
public:
    virtual void Visit(AssignmentByIndexStatement* node) override final {
    }

    virtual void Visit(AssignmentStatement* node) override final {
    }

    virtual void Visit(BinaryOperatorExpression* node) override final {
    }

    virtual void Visit(BooleanExpression* node) override final {
    }

    virtual void Visit(ClassBody* node) override final {
        auto& [className, classInfo] = currentClass_;
        for (auto* variable : variables_) {
            variable->Accept(this);
            auto& [variableName, variableInfo] = currentVariable_;
            classInfo.AddVariable(variableName, variableInfo);
        }
        for (auto* method : methods_) {
            method->Accept(this);
            auto& [methodName, methodInfo] = currentMethod_;
            classInfo.AddMethod(methodName, methodInfo);
        }
    }

    virtual void Visit(ClassDeclaration* node) override final {
        currentClass_ = std::make_pair(node->className, ClassInfo{});
        auto& [className, classInfo] = currentClass_;
        if (classes_.find(name) != classes_.end()) {
            throw ClassRedefinition{"Class " + className + " has been already defined."};
        }
        classInfo.base = node->extendsForClass_;
        node->classBody_->Accept(this);
        classes_[className] = classInfo;
    }

    virtual void Visit(ConditionStatement* node) override final {
    }

    virtual void Visit(IdentifierExpression* node) override final {
    }

    virtual void Visit(IndexExpression* node) override final {
    }

    virtual void Visit(IntArrayConstructorExpression* node) override final {
    }

    virtual void Visit(LengthExpression* node) override final {
    }

    virtual void Visit(LoopStatement* node) override final {
    }

    virtual void Visit(MainClass* node) override final {
    }

    virtual void Visit(MethodBody* node) override final {
    }

    virtual void Visit(MethodCallExpression* node) override final {
    }

    virtual void Visit(MethodDeclaration* node) override final {
    }

    virtual void Visit(NotExpression* node) override final {
    }

    virtual void Visit(NumberExpression* node) override final {
    }

    virtual void Visit(ParensExpression* node) override final {
    }

    virtual void Visit(PrimitiveType* node) override final {
    }

    virtual void Visit(PrintStatement* node) override final {
    }

    virtual void Visit(Program* node) override final {
        for (auto* classDeclaration : classDeclarations_) {
            classDeclaration->Accept(this);
        }
    }

    virtual void Visit(ScopeStatement* node) override final {
    }

    virtual void Visit(ThisExpression* node) override final {
    }

    virtual void Visit(UserTypeConstructorExpression* node) override final {
    }

    virtual void Visit(UserType* node) override final {
    }

    virtual void Visit(VarDeclaration* node) override final {
    }

public:
    std::unordered_map<std::string, ClassInfo> classes_ = {};
    std::pair<std::string, VariableInfo> currentVariable_ = {};
    std::pair<std::string, MethodInfo> currentMethod_ = {};
    std::pair<std::string, ClassInfo> currentClass_ = {};
}
