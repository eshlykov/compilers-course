#pragma once

#include "expression.hpp"
#include "../visitor/visitor.hpp"

#include <memory>

class ExpressionAndExpression : public IExpression<bool> {
public:
    explicit ExpressionAndExpression(bool _value) :
        IExpression<bool>{std::move(_value)} {
    }

    virtual void Accept(std::shared_ptr<IVisitor> visitor) override {
        visitor->Visit(std::dynamic_pointer_cast<ExpressionAndExpression>(shared_from_this()));
    }
};
