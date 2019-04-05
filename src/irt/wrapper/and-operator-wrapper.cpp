#include "and-operator-wrapper.hpp"

namespace Irt {

    AndOperatorWrapper::AndOperatorWrapper(std::shared_ptr<Expression> leftExpression,
        std::shared_ptr<Expression> rightExpression) :
            ComparisonOperatorWrapper(LogicalOperator::And, leftExpression, rightExpression) {
    }

    std::shared_ptr<Statement> AndOperatorWrapper::ToCondition(Address addressIf, Address addressElse) const {
        Address addressNext;
        return std::make_shared<StatementSequence>(
            std::make_shared<ConditionalJump>(
                LogicalOperator::Equal,
                leftExpression_,
                std::make_shared<Constant>(1),
                addressNext,
                addressElse
            ),
            std::make_shared<StatementSequence>(
                std::make_shared<Label>(addressNext),
                std::make_shared<ConditionalJump>(
                    LogicalOperator::Equal,
                    rightExpression_,
                    std::make_shared<Constant>(1),
                    addressIf,
                    addressElse
                )
            )
        );
    }

}
