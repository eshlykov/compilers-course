#include "this-expression.hpp"

ThisExpression::ThisExpression(Location location) {
    location_ = location;
}

virtual void ThisExpression::Accept(Visitor* visitor) override final {
    visitor->Visit(this);
}