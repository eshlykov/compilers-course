#pragma once

#include "wrapper.hpp"

namespace Irt {

    class ExpressionWrapper : public Wrapper {
    public:
        ExpressionWrapper(std::shared_ptr<Expression> expression);

        virtual std::shared_ptr<Expression> ToRValue() const override final;

        virtual std::shared_ptr<Statement> ToCondition(Address addressIf, Address addressElse) const override final;

    private:
        const std::shared_ptr<Expression> expression_;
    };

}
