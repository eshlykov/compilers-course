#pragma once

#include "../visitor.hpp"
#include "node.hpp"
#include <vector>

class CommaExpression;

class CommaExpressionRepeated : public Node {
public:
    CommaExpressionRepeated() = default;

    CommaExpressionRepeated(const std::vector<CommaExpression*>& commaExpression) :
        commaExpression_{commaExpression} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::vector<CommaExpression*> commaExpression_ = {};
};
