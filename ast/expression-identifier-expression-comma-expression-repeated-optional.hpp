#pragma once

#include "../visitor.hpp"
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

    void Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

public:
    Expression* expression_ = {};
    Identifier* identifier_ = {};
    ExpressionCommaExpressionRepeatedOptional* expressionCommaExpressionRepeatedOptional_ = {};
};
