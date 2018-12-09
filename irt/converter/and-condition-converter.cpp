#include "and-condition-converter.hpp"

namespace Irt {

    AndConditionConverter::AndConditionConverter(std::shared_ptr<Expression> leftExpression,
        std::shared_ptr<Expression> rightExpression) :
            leftExpression_{leftExpression},
            rightExpression_{rightExpression} {
        assert(leftExpression_ != nullptr);
        assert(rightExpression_ != nullptr);
    }

    std::shared_ptr<Statement> AndConditionConverter::ToConditionalJump(Address labelIf, Address labelElse) const {
        // TODO: сокращенная арифметика
        return std::make_shared<ConditionalJump>(LogicalOperator::And,
            leftExpression_,
            rightExpression_,
            labelIf,
            labelElse);
    }

}
