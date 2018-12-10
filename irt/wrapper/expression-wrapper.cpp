#include "expression-wrapper.hpp"

namespace Irt {

    ExpressionWrapper::ExpressionWrapper(std::shared_ptr<Expression> expression) :
        expression_{expression} {
    }

    std::shared_ptr<Expression> ExpressionWrapper::ToRValue() const {
        return expression_;
    }

    std::shared_ptr<Statement> ExpressionWrapper::ToCondition(Address ifTrue, Address ifFalse) const {
        return std::make_shared<ConditionalJump>(
            LogicalOperator::Equal,
            expression_,
            std::make_shared<Constant>(1),
            ifTrue,
            ifFalse);
    }

}
