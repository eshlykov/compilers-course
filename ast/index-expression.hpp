#pragma once

#include "expression.hpp"
#include <memory>

class IndexExpression : public Expression {
public:
    IndexExpression(Location location,
        std::unique_ptr<Expression> lhs,
        std::unique_ptr<Expression> rhs) :
            lhs_{std::move(lhs)},
            rhs_{std::move(rhs)} {
        location_ = location;
    }

    virtual void Accept(Visitor* visitor) override final {
        visitor->Visit(this);
    }

public:
    std::unique_ptr<Expression> lhs_;
    std::unique_ptr<Expression> rhs_;
};
