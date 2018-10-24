#pragma once

#include <memory>
#include <optional>

class CommaExpressionRepeated;

class ExpressionCommaExpressionRepeatedOptional {
public:
    ExpressionCommaExpressionRepeatedOptional(std::optional<std::shared_ptr<CommaExpressionRepeated>> commaExpressionRepeated) :
        commaExpressionRepeated_{commaExpressionRepeated} {
    }

public:
    std::optional<> commaExpressionRepeated_ = {};
};
