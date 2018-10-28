#pragma once

#include "../visitor.hpp"
#include <optional>

class ExpressionCommaExpressionRepeated;

class ExpressionCommaExpressionRepeatedOptional {
public:
    ExpressionCommaExpressionRepeatedOptional() = default;

    ExpressionCommaExpressionRepeatedOptional(ExpressionCommaExpressionRepeated* expressionCommaExpressionRepeated) :
        expressionCommaExpressionRepeated_{expressionCommaExpressionRepeated} {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    std::optional<ExpressionCommaExpressionRepeated*> expressionCommaExpressionRepeated_ = {};
};
