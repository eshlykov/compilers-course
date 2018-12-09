#include "expression-sequence.hpp"

namespace Irt {

    ExpressionSequence::ExpressionSequence(std::shared_ptr<Expression> leftExpression,
        std::shared_ptr<Expression> rightExpression) :
            leftExpression_{leftExpression},
            rightExpression_{rightExpression} {
        assert(leftExpression_ != nullptr);
        assert(rightExpression_ != nullptr);
    }

    void ExpressionSequence::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
