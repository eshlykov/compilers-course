#pragma once

#include "expression.h"
#include <memory>

class ExpressionExpression : public Expression {
public:
    ExpressionExpression(std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs) :
        lhs_{lhs}, rhs_{rhs} {
    }

public:
    std::shared_ptr<Expression> lhs_;
    std::shared_ptr<Expression> rhs_;
};
