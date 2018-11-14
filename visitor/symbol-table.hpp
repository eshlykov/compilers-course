#pragma once

#include "../ast.hpp"
#include "../compile-error.hpp"
#include "visitor.hpp"
#include <algorithm>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class VariableInfo {
public:
    Type* type_ = {};
};

class MethodInfo {
public:
    void AddVariable(const std::string& name, VariableInfo variable) {
        auto iter = find_if(arguments_.begin(), arguments_.end(), [&] (const auto& argument) { return argument.first == name; });
        if (variables_.find(name) != variables_.end() || iter != arguments_.end()) {
            throw VariableRedefinition{"Variable " + name + " has been already defined."};
        }
        variables_[name] = variable;
    }

    void AddArgument(const std::string& name, VariableInfo variable) {
        auto iter = find_if(arguments_.begin(), arguments_.end(), [&] (const auto& argument) { return argument.first == name; });
        if (iter != arguments_.end()) {
            throw ArgumentRedefinition{"Argument " + name + " has been already defined."};
        }
        arguments_.emplace_back(name, variable);
    }

public:
    Type* returnType_ = {};
    std::unordered_map<std::string, VariableInfo> variables_ = {};
    std::vector<std::pair<std::string, VariableInfo>> arguments_ = {};
};

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

        for (auto& variable : node->variables_) {
            variable->Accept(this);
            auto& [variableName, variableInfo] = currentVariable_;
            classInfo.AddVariable(variableName, variableInfo);
            currentVariable_ = {};
        }

        for (auto& method : node->methods_) {
            method->Accept(this);
            auto& [methodName, methodInfo] = currentMethod_;
            classInfo.AddMethod(methodName, methodInfo);
            currentMethod_ = {};
        }
    }

    virtual void Visit(ClassDeclaration* node) override final {
        currentClass_ = std::make_pair(node->className_, ClassInfo{});

        auto& [className, classInfo] = currentClass_;
        if (classes_.find(className) != classes_.end()) {
            throw ClassRedefinition{"Class " + className + " has been already defined."};
        }

        classInfo.base_ = node->extendsForClass_;
        node->classBody_->Accept(this);
        classes_[className] = classInfo;

        currentClass_ = {};
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
        auto& [methodName, methodInfo] = currentMethod_;

        for (auto& variable : node->variables_) {
            variable->Accept(this);
            auto& [variableName, variableInfo] = currentVariable_;
            methodInfo.AddVariable(variableName, variableInfo);
            currentVariable_ = {};
        }
    }

    virtual void Visit(MethodCallExpression* node) override final {
    }

    virtual void Visit(MethodDeclaration* node) override final {
        currentMethod_ = std::make_pair(node->methodName_, MethodInfo{});

        auto& [methodName, methodInfo] = currentMethod_;
        methodInfo.returnType_ = node->resultType_.get();

        for (auto& argument : node->argumentsList_) {
            argument->Accept(this);
            auto& [variableName, variableInfo] = currentVariable_;
            methodInfo.AddArgument(variableName, variableInfo);
            currentVariable_ = {};
        }

        node->methodBody_->Accept(this);
    }

    virtual void Visit(NotExpression* node) override final {
    }

    virtual void Visit(NumberExpression* node) override final {
    }

    virtual void Visit(PrimitiveType* node) override final {
    }

    virtual void Visit(PrintStatement* node) override final {
    }

    virtual void Visit(Program* node) override final {
        for (auto& classDeclaration : node->classDeclarations_) {
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
        currentVariable_ = std::make_pair(node->name_, VariableInfo{});

        auto& [variableName, variableInfo] = currentVariable_;
        variableInfo.type_ = node->type_.get();
    }

public:
    std::unordered_map<std::string, ClassInfo> classes_ = {};
    std::pair<std::string, VariableInfo> currentVariable_ = {};
    std::pair<std::string, MethodInfo> currentMethod_ = {};
    std::pair<std::string, ClassInfo> currentClass_ = {};
};
