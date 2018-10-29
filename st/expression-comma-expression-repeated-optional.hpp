#pragma once

#include "../visitor.hpp"
#include "node.hpp"
#include <optional>

class ExpressionCommaExpressionRepeated;

class ExpressionCommaExpressionRepeatedOptional : public Node {
public:
    ExpressionCommaExpressionRepeatedOptional() = default;

    ExpressionCommaExpressionRepeatedOptional(ExpressionCommaExpressionRepeated* expressionCommaExpressionRepeated) :
        expressionCommaExpressionRepeated_{expressionCommaExpressionRepeated} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::optional<ExpressionCommaExpressionRepeated*> expressionCommaExpressionRepeated_ = {};
};
