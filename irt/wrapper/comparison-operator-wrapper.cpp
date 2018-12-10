#include "comparison-operator-wrapper.hpp"

namespace Irt {

    ComparisonOperatorWrapper::ComparisonOperatorWrapper(LogicalOperator logicalOperator,
        std::shared_ptr<Expression> leftExpression,
        std::shared_ptr<Expression> rightExpression) :
            logicalOperator_{logicalOperator},
            leftExpression_{leftExpression},
            rightExpression_{rightExpression} {
    }

    std::shared_ptr<Expression> ComparisonOperatorWrapper::ToRvalue() const {
        Register temp;
        Address ifTrue;
        Address ifFalse;
        Address end;
        return std::make_shared<ExpressionSequence>(
            ToCondition(ifTrue, ifFalse),
            std::make_shared<ExpressionSequence>(
                std::make_shared<StatementSequence>(
                    std::make_shared<Label>(ifTrue),
                    std::make_shared<StatementSequence>(
                        std::make_shared<Move>(
                            std::make_shared<Temporary>(temp),
                            std::make_shared<Constant>(1)
                        ),
                        std::make_shared<StatementSequence>(
                            std::make_shared<Jump>(end),
                            std::make_shared<StatementSequence>(
                                std::make_shared<Label>(ifFalse),
                                std::make_shared<StatementSequence>(
                                    std::make_shared<Move>(
                                        std::make_shared<Temporary>(temp),
                                        std::make_shared<Constant>(0)
                                    ),
                                    std::make_shared<Label>(end)
                                )
                            )
                        )
                    )
                ),
                std::make_shared<Temporary>(temp)
            )
        );
    }

    std::shared_ptr<Statement> ComparisonOperatorWrapper::ToCondition(Address ifTrue, Address ifFalse) const {
        return std::make_shared<ConditionalJump>(
            logicalOperator_,
            leftExpression_,
            rightExpression_,
            ifTrue,
            ifFalse
        );
    }

}
