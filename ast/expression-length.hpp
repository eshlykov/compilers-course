#pragma once

#include "expression.hpp"
#include <memory>

class ExpressionLength : public Expression {
public:
    ExpressionLength(std::shared_ptr<Expression> expression) :
        expression_{expression} {
    }

public:
    std::shared_ptr<Expression> expression_ = {};
};
