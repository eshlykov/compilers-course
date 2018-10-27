#pragma once

#include <optional>

class ExpressionCommaExpressionRepeated;

class ExpressionCommaExpressionRepeatedOptional {
public:
    ExpressionCommaExpressionRepeatedOptional() = default;

    ExpressionCommaExpressionRepeatedOptional(ExpressionCommaExpressionRepeated* expressionCommaExpressionRepeated) :
        expressionCommaExpressionRepeated_{expressionCommaExpressionRepeated} {
    }

public:
    std::optional<ExpressionCommaExpressionRepeated*> expressionCommaExpressionRepeated_ = {};
};
