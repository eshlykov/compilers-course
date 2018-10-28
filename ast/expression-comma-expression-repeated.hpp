#pragma once

#include "../visitor.hpp"
#include "node.hpp"
#include <vector>

class CommaExpressionRepeated;
class Expression;

class ExpressionCommaExpressionRepeated : public Node {
public:
    ExpressionCommaExpressionRepeated(Expression* expression, CommaExpressionRepeated* commaExpressionRepeated) :
        expression_{expression}, commaExpressionRepeated_{commaExpressionRepeated} {
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    Expression* expression_ = {};
    CommaExpressionRepeated* commaExpressionRepeated_ = {};
};
