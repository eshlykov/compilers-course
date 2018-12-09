#pragma once

#include "converter.hpp"
#include <memory>

class Expression;
class Statement;

namespace Irt {

    class ExpressionConverter : public Converter {
    public:
        explicit ExpressionConverter(std::shared_ptr<Expression> expression);

        virtual std::shared_ptr<Expression> ToExpression() const override final;

        virtual std::shared_ptr<Statement> ToStatement() const override final;

        virtual std::shared_ptr<Statement> ToConditionalJump() const override final;

    public:
        const std::shared_ptr<Expression> expression_;
    };

}
