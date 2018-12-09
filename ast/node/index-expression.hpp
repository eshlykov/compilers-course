#pragma once

#include "expression.hpp"
#include <memory>

namespace Ast {

    class IndexExpression : public Expression {
    public:
        IndexExpression(Location location,
            std::unique_ptr<Expression> lhs,
            std::unique_ptr<Expression> rhs);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const std::unique_ptr<Expression> lhs_;
        const std::unique_ptr<Expression> rhs_;
    };

}