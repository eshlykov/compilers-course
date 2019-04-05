#include "comparison-operator-wrapper.hpp"

namespace Irt {

    ComparisonOperatorWrapper::ComparisonOperatorWrapper(LogicalOperator logicalOperator,
        std::shared_ptr<Expression> leftExpression,
        std::shared_ptr<Expression> rightExpression) :
            logicalOperator_{logicalOperator},
            leftExpression_{leftExpression},
            rightExpression_{rightExpression} {
    }

    std::shared_ptr<Expression> ComparisonOperatorWrapper::ToRValue() const {
        Storage storage;
        Address addressIf;
        Address addressElse;
        Address addressEnd;
        return std::make_shared<ExpressionSequence>(
            ToCondition(addressIf, addressElse),
            std::make_shared<ExpressionSequence>(
                std::make_shared<StatementSequence>(
                    std::make_shared<Label>(addressIf),
                    std::make_shared<StatementSequence>(
                        std::make_shared<Move>(
                            std::make_shared<Temporary>(storage),
                            std::make_shared<Constant>(1)
                        ),
                        std::make_shared<StatementSequence>(
                            std::make_shared<Jump>(addressEnd),
                            std::make_shared<StatementSequence>(
                                std::make_shared<Label>(addressElse),
                                std::make_shared<StatementSequence>(
                                    std::make_shared<Move>(
                                        std::make_shared<Temporary>(storage),
                                        std::make_shared<Constant>(0)
                                    ),
                                    std::make_shared<Label>(addressEnd)
                                )
                            )
                        )
                    )
                ),
                std::make_shared<Temporary>(storage)
            )
        );
    }

    std::shared_ptr<Statement> ComparisonOperatorWrapper::ToCondition(Address addressIf, Address addressElse) const {
        return std::make_shared<ConditionalJump>(
            logicalOperator_,
            leftExpression_,
            rightExpression_,
            addressIf,
            addressElse
        );
    }

}
