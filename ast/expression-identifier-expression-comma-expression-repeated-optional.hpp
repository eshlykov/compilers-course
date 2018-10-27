#pragma once

#include "expression.hpp"

class Identifier;
class ExpressionCommaExpressionRepeatedOptional;

class ExpressionIdentifierExpressionCommaExpressionRepeatedOptional : public Expression {
public:
    ExpressionIdentifierExpressionCommaExpressionRepeatedOptional(
        Expression* expression, Identifier* identifier,
        ExpressionCommaExpressionRepeatedOptional* expressionCommaExpressionRepeatedOptional) :
            expression_{expression}, identifier_{identifier},
            expressionCommaExpressionRepeatedOptional_{expressionCommaExpressionRepeatedOptional} {
    }

public:
    Expression* expression_ = {};
    Identifier* identifier_ = {};
    ExpressionCommaExpressionRepeatedOptional* expressionCommaExpressionRepeatedOptional_ = {};
};
