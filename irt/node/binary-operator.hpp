#pragma once

#include "expression.hpp"
#include <memory>

enum class ArithmeticOperator {
    Plus,
    Minus,
    Multiplication
};

class BinaryOperator : public Expression {
public:
    BinaryOperator(ArithmeticOperator arithmeticOperator,
        std::shared_ptr<Expression> left,
        std::shared_ptr<Expression> right);

    virtual void Accept(Visitor* visitor) override final;

public:
    const ArithmeticOperator arithmeticOperator_;
    const std::shared_ptr<Expression> left_;
    const std::shared_ptr<Expression> right_;
};
