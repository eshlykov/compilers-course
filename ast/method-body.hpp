#pragma once

#include "../visitor.hpp"
#include "node.hpp"
#include <memory>

class VarDeclaration;
class Statement;
class Expression;

class MethodBody : public Node {
public:
    MethodBody(const std::vector<VarDeclaration*>& variables,
        std::vector<std::unique_ptr<Statement>>& statements,
        Expression* returnExpression) :
            variables_{variables},
            statements_{std::move(statements)},
            returnExpression_{returnExpression} {
    }

    ~MethodBody() {
        FreeVector(variables_);
        delete returnExpression_;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::vector<VarDeclaration*> variables_;
    std::vector<std::unique_ptr<Statement>> statements_;
    Expression* returnExpression_;
};
