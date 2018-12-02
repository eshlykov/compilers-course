#include "index-expression.hpp"

IndexExpression::IndexExpression(Location location,
    std::unique_ptr<Expression> lhs,
    std::unique_ptr<Expression> rhs) :
        lhs_{std::move(lhs)},
        rhs_{std::move(rhs)} {
    SetLocation(location);
}

void IndexExpression::Accept(Visitor* visitor) {
    visitor->Visit(this);
}
