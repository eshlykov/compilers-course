#pragma once

#include "converter.hpp"
#include <memory>

namespace Irt {

    class ConditionConverter : public Converter {
    public:
        virtual std::shared_ptr<Expression> ToExpression() const override final;

        virtual std::shared_ptr<Statement> ToStatement() const override final;
    };

}
