#pragma once

#include "expression.h"
#include <memory>

enum class BinaryOperator {
    BO_And,
    BO_Less,
    BO_Plus,
    BO_Minus,
    BO_Star,
};

class ExpressionBinaryOperatorExpression : public Expression {
public:
    ExpressionBinaryOperatorExpression(std::shared_ptr<Expression> lhs,
        std::shared_ptr<Expression> rhs, BinaryOperator binaryOperator) :
            lhs_{lhs}, rhs_{rhs}, binaryOperator_{binaryOperator} {
    }

public:
    std::shared_ptr<Expression> lhs_ = {};
    std::shared_ptr<Expression> rhs_ = {};
    BinaryOperator binaryOperator_ = {};
};
