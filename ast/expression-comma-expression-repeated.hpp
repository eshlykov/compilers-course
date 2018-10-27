#pragma once

#include <vector>

class CommaExpressionRepeated;
class Expression;

class ExpressionCommaExpressionRepeated {
public:
    ExpressionCommaExpressionRepeated(Expression* expression, CommaExpressionRepeated* commaExpressionRepeated) :
        expression_{expression}, commaExpressionRepeated_{commaExpressionRepeated} {
    }

public:
    Expression* expression_ = {};
    CommaExpressionRepeated* commaExpressionRepeated_ = {};
};
