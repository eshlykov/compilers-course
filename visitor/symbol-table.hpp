#pragma once

#include <string>
#include <unordered_map>

class ClassInfo {
public:
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

class SymbolTable : public Visitor {
public:
    virtual void Visit(AssignmentByIndexStatement*) override final {
    }

    virtual void Visit(AssignmentStatement*) override final {
    }

    virtual void Visit(BinaryOperatorExpression*) override final {
    }

    virtual void Visit(BooleanExpression*) override final {
    }

    virtual void Visit(ClassBody*) override final {
    }

    virtual void Visit(ClassDeclaration*) override final {
    }

    virtual void Visit(ConditionStatement*) override final {
    }

    virtual void Visit(IdentifierExpression*) override final {
    }

    virtual void Visit(IndexExpression*) override final {
    }

    virtual void Visit(IntArrayConstructorExpression*) override final {
    }

    virtual void Visit(LengthExpression*) override final {
    }

    virtual void Visit(LoopStatement*) override final {
    }

    virtual void Visit(MainClass*) override final {
    }

    virtual void Visit(MethodBody*) override final {
    }

    virtual void Visit(MethodCallExpression*) override final {
    }

    virtual void Visit(MethodDeclaration*) override final {
    }

    virtual void Visit(NotExpression*) override final {
    }

    virtual void Visit(NumberExpression*) override final {
    }

    virtual void Visit(ParensExpression*) override final {
    }

    virtual void Visit(PrimitiveType*) override final {
    }

    virtual void Visit(PrintStatement*) override final {
    }

    virtual void Visit(Program*) override final {
    }

    virtual void Visit(ScopeStatement*) override final {
    }

    virtual void Visit(ThisExpression*) override final {
    }

    virtual void Visit(UserTypeConstructorExpression*) override final {
    }

    virtual void Visit(UserType*) override final {
    }

    virtual void Visit(VarDeclaration*) override final {
    }

public:
    std::unordered_map<std::string, ClassInfo> classes_ = {};
}
