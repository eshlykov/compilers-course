#pragma once

#include "wrapper.hpp"

namespace Irt {

    class ComparisonOperatorWrapper : public Wrapper {
    public:
        ComparisonOperatorWrapper(LogicalOperator logicalOperator,
            std::shared_ptr<Expression> leftExpression,
            std::shared_ptr<Expression> rightExpression);

        virtual std::shared_ptr<Expression> ToRvalue() const override final;

        virtual std::shared_ptr<Statement> ToCondition(Address, Address) const override;

    protected:
        const LogicalOperator logicalOperator_;
        const std::shared_ptr<Expression> leftExpression_;
        const std::shared_ptr<Expression> rightExpression_;
    };

}
