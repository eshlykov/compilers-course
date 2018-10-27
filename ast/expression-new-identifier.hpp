#pragma once

#include "expression.hpp"

class Identifier;

class ExpressionNewIdentifier : public Expression {
public:
    ExpressionNewIdentifier(Identifier* identifier) : identifier_{identifier} {
    }

public:
    Identifier* identifier_ = {};
};
