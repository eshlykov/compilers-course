#pragma once

#include <optional>

class CommaExpressionRepeated;

class ExpressionCommaExpressionRepeatedOptional {
public:
    ExpressionCommaExpressionRepeatedOptional(std::shared_ptr<CommaExpressionRepeated> commaExpressionRepeated) :
        commaExpressionRepeated_{commaExpressionRepeated} {
    }

public:
    std::optional<CommaExpressionRepeated*> commaExpressionRepeated_ = {};
};
