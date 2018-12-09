#pragma once

#include "condition-converter.hpp"
#include <memory>

namespace Irt {

    class LessConditionConverter : public ConditionConverter {
    public:
        LessConditionConverter(std::shared_ptr<Expression> leftExpression,
            std::shared_ptr<Expression> rightExpression);

        virtual std::shared_ptr<Statement> ToConditionalJump(Address, Address) const override final;

    private:
        std::shared_ptr<Expression> leftExpression_;
        std::shared_ptr<Expression> rightExpression_;
    };

}
