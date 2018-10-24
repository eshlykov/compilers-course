#pragma once

#include "expression.hpp"
#include <memory>

class ExpressionAtExpression : public Expression {
public:
    ExpressionAtExpression(std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs) :
        lhs_{lhs}, rhs_{rhs} {
    }

public:
    std::shared_ptr<Expression> lhs_ = {};
    std::shared_ptr<Expression> rhs_ = {};
};
