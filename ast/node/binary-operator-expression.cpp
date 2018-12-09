#include "binary-operator-expression.hpp"

BinaryOperatorExpression::BinaryOperatorExpression(Location location,
    std::unique_ptr<Expression> lhs,
    std::unique_ptr<Expression> rhs,
    BinaryOperator binaryOperator) :
        lhs_{std::move(lhs)},
        rhs_{std::move(rhs)},
        binaryOperator_{binaryOperator} {
    SetLocation(location);
    assert(lhs_ != nullptr);
    assert(rhs_ != nullptr);
}

void BinaryOperatorExpression::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
