#pragma once

#include "../visitor.hpp"
#include "node.hpp"

class VarDeclaration;
class Statement;
class Expression;

class MethodBody : public Node {
public:
    MethodBody(const std::vector<VarDeclaration*>& variables, const std::vector<Statement*>& statements, Expression* returnExpression) :
        variables_{variables}, statements_{statements}, returnExpression_{returnExpression} {
    }

    ~MethodBody() {
        FreeVector(variables_);
        FreeVector(statements_);
        delete returnExpression_;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::vector<VarDeclaration*> variables_ = {};
    std::vector<Statement*> statements_ = {};
    Expression* returnExpression_ = {};
};
