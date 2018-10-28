#pragma once

#include "../visitor.hpp"
#include <vector>

class CommaExpression;

class CommaExpressionRepeated {
public:
    CommaExpressionRepeated() = default;

    CommaExpressionRepeated(const std::vector<CommaExpression*>& commaExpression) :
        commaExpression_{commaExpression} {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    std::vector<CommaExpression*> commaExpression_ = {};
};
