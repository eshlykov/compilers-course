#pragma once

#include "../../ast.hpp"
#include "../../compile-error.hpp"
#include "../visitor.hpp"
#include "class-info.hpp"
#include "method-info.hpp"
#include "variable-info.hpp"
#include <algorithm>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class SymbolTable : public Visitor {
public:
    virtual ~SymbolTable() = default;
    
    virtual void Visit(AssignmentByIndexStatement* node) override final;

    virtual void Visit(AssignmentStatement* node) override final;

    virtual void Visit(BinaryOperatorExpression* node) override final;

    virtual void Visit(BooleanExpression* node) override final;

    virtual void Visit(ClassBody* node) override final;

    virtual void Visit(ClassDeclaration* node) override final;

    virtual void Visit(ConditionStatement* node) override final;

    virtual void Visit(IdentifierExpression* node) override final;

    virtual void Visit(IndexExpression* node) override final;

    virtual void Visit(IntArrayConstructorExpression* node) override final;

    virtual void Visit(LengthExpression* node) override final;

    virtual void Visit(LoopStatement* node) override final;

    virtual void Visit(MainClass* node) override final;

    virtual void Visit(MethodBody* node) override final;

    virtual void Visit(MethodCallExpression* node) override final;

    virtual void Visit(MethodDeclaration* node) override final;

    virtual void Visit(NotExpression* node) override final;

    virtual void Visit(NumberExpression* node) override final;

    virtual void Visit(PrimitiveType* node) override final;

    virtual void Visit(PrintStatement* node) override final;

    virtual void Visit(Program* node) override final;

    virtual void Visit(ScopeStatement* node) override final;

    virtual void Visit(ThisExpression* node) override final;

    virtual void Visit(UserTypeConstructorExpression* node) override final;

    virtual void Visit(UserType* node) override final;

    virtual void Visit(VarDeclaration* node) override final;

public:
    std::unordered_map<std::string, ClassInfo> classes_ = {};
    std::pair<std::string, VariableInfo> currentVariable_ = {};
    std::pair<std::string, MethodInfo> currentMethod_ = {};
    std::pair<std::string, ClassInfo> currentClass_ = {};
};
