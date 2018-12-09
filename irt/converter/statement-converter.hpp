#pragma once

#include "converter.hpp"
#include <memory>

namespace Irt {

    class StatementConverter : public Converter {
    public:
        explicit StatementConverter(std::shared_ptr<Statement> statement);

        virtual std::shared_ptr<Expression> ToExpression() const override final;

        virtual std::shared_ptr<Statement> ToStatement() const override final;

        virtual std::shared_ptr<Statement> ToConditionalJump(Address, Address) const override final;

    private:
        std::shared_ptr<Statement> statement_;
    };

}
