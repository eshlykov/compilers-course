#pragma once

#include <memory>
#include "visitor.hpp"
#include "../ast/expression-and-expression.hpp"

class Interpreter : public IVisitor {
    virtual void Visit(std::shared_ptr<ExpressionAndExpression> expression) override {
        auto lhs = std::dynamic_pointer_cast<IExpression<bool>>(nodes.top())->value;
        nodes.pop();
        auto rhs = std::dynamic_pointer_cast<IExpression<bool>>(nodes.top())->value;
        nodes.pop();

        expression->value = lhs && rhs;

        nodes.emplace(expression);
    }
};
