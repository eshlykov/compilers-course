#pragma once

#include "converter.hpp"
#include <memory>

namespace Irt {

    class ExpressionConverter : public Converter {
    public:
        explicit ExpressionConverter(std::shared_ptr<Expression> expression);

        virtual std::shared_ptr<Expression> ToExpression() const override final;

        virtual std::shared_ptr<Statement> ToStatement() const override final;

        virtual std::shared_ptr<Statement> ToConditionalJump(std::shared_ptr<Label> labelIf,
            std::shared_ptr<Label> labelElse) const override final;

    private:
        std::shared_ptr<Expression> expression_;
    };

}