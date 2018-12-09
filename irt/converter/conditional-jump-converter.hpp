#pragma once

#include "converter.hpp"
#include <memory>

namespace Irt {

    class ConditionalJumpConverter : public Converter {
    public:
        explicit ConditionalJumpConverter(std::shared_ptr<Statement> statement);

        virtual std::shared_ptr<Expression> ToExpression() const override final;

        virtual std::shared_ptr<Statement> ToStatement() const override final;

    private:
        std::shared_ptr<Statement> statement_;
    };

}
