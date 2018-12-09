#include "binary-operator.hpp"

BinaryOperator::BinaryOperator(ArithmeticOperator arithmeticOperator,
    std::shared_ptr<Expression> left,
    std::shared_ptr<Expression> right) :
        arithmeticOperator_{arithmeticOperator},
        right_{right},
        left_{left} {
}

void BinaryOperator::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
