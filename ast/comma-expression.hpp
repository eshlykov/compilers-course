#pragma once

#include <memory>

class Expression;

class CommaExpression {
public:
    CommaExpression(std::shared_ptr<Expression> expression) :
        expression_{expression} {
    }

public:
    std::shared_ptr<Expression> expression_ = {};
};
