#pragma once

#include <vector>

class CommaExpression;

class CommaExpressionRepeated {
public:
    CommaExpressionRepeated() = default;

    CommaExpressionRepeated(const std::vector<CommaExpression*>& commaExpression) :
        commaExpression_{commaExpression} {
    }

public:
    std::vector<CommaExpression*> commaExpression_ = {};
};
