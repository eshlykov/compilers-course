#pragma once

#include <string>
#include <unordered_map>

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
    }

    virtual void Visit(ClassDeclaration* node) override final {
        if (classes_.find(node->className_) != classes_.end()) {
            throw ClassRedefinition{"Class " + node->className_ + " has been already defined."};
        }
        auto& current = classes_[node->className_];
        current.base = node->extendsForClass_;
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
}
