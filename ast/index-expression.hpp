#pragma once

#include "../visitor.hpp"
#include "expression.hpp"

class IndexExpression : public Expression {
public:
    IndexExpression(Expression* indexable, Expression* index) :
        indexable_{indexable}, index_{index} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Expression* indexable_ = {};
    Expression* index_ = {};
};
