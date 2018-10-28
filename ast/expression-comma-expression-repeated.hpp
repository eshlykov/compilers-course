#pragma once

#include "../visitor.hpp"
#include <vector>

class CommaExpressionRepeated;
class Expression;

class ExpressionCommaExpressionRepeated {
public:
    ExpressionCommaExpressionRepeated(Expression* expression, CommaExpressionRepeated* commaExpressionRepeated) :
        expression_{expression}, commaExpressionRepeated_{commaExpressionRepeated} {
    }

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    Expression* expression_ = {};
    CommaExpressionRepeated* commaExpressionRepeated_ = {};
};
