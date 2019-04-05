#pragma once

#include "expression.hpp"
#include <memory>

namespace Ast {

    class NotExpression : public Expression {
    public:
        explicit NotExpression(Location location,
            std::unique_ptr<Expression> expression);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const std::unique_ptr<Expression> expression_;
    };

}
