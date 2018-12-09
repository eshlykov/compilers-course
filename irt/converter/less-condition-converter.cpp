#include "less-condition-converter.hpp"

namespace Irt {

    LessConditionConverter::LessConditionConverter(std::shared_ptr<Expression> leftExpression,
        std::shared_ptr<Expression> rightExpression) :
            leftExpression_{leftExpression},
            rightExpression_{rightExpression} {
        assert(leftExpression_ != nullptr);
        assert(rightExpression_ != nullptr);
    }

    std::shared_ptr<Statement> LessConditionConverter::ToConditionalJump(Address labelIf, Address labelElse) const {
        return std::make_shared<ConditionalJump>(LogicalOperator::Less,
            leftExpression_,
            rightExpression_,
            labelIf,
            labelElse);
    }

}
