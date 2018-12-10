#pragma once

#include "comparison-operator-wrapper.hpp"

namespace Irt {

    class AndOperatorWrapper : public ComparisonOperatorWrapper {
    public:
        AndOperatorWrapper(std::shared_ptr<Expression> leftExpression,
            std::shared_ptr<Expression> rightExpression);

        std::shared_ptr<Statement> ToCondition(Address, Address) const override final;
    };

}
