#pragma once

#include <memory>
#include <vector>

class CommaExpression;

class CommaExpressionRepeated {
public:
    explicit CommaExpressionRepeated(const std::vector<std::shared_ptr<CommaExpression>>& commaExpression) :
        commaExpression_{commaExpression} {
    }

public:
    std::vector<std::shared_ptr<CommaExpression>> commaExpression_ = {};
};
