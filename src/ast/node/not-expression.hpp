#pragma once

#include "expression.hpp"
#include <memory>

namespace Ast {

    class NotExpression : public Expression {
    public:
        explicit NotExpression(Location location,
            std::unique_ptr<Expression> expression);

        void Accept(Visitor* visitor) final;

    public:
        const std::unique_ptr<Expression> expression_;
    };

    inline NotExpression::NotExpression(Location location,
        std::unique_ptr<Expression> expression) :
        expression_{std::move(expression)} {
        SetLocation(location);
        assert(expression_ != nullptr);
    }

    inline void NotExpression::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
