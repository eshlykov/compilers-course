#pragma once

#include "../visitor.hpp"
#include "node.hpp"
#include <memory>

class VarDeclaration;
class Statement;
class Expression;

class MethodBody : public Node {
public:
    MethodBody(Location location,
        std::vector<std::unique_ptr<VarDeclaration>>& variables,
        std::vector<std::unique_ptr<Statement>>& statements,
        std::unique_ptr<Expression> returnExpression) :
            variables_{std::move(variables)},
            statements_{std::move(statements)},
            returnExpression_{std::move(returnExpression)} {
        location_ = location;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::vector<std::unique_ptr<VarDeclaration>> variables_;
    std::vector<std::unique_ptr<Statement>> statements_;
    std::unique_ptr<Expression> returnExpression_;
};
