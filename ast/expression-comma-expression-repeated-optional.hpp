#pragma once

#include <optional>

class CommaExpressionRepeated;

class ExpressionCommaExpressionRepeatedOptional {
public:
    ExpressionCommaExpressionRepeatedOptional(CommaExpressionRepeated* commaExpressionRepeated) :
        commaExpressionRepeated_{commaExpressionRepeated} {
    }

public:
    std::optional<CommaExpressionRepeated*> commaExpressionRepeated_ = {};
};
