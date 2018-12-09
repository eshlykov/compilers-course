#include "../node/void.hpp"
#include "expression-converter.hpp"

namespace Irt {

    ExpressionConverter::ExpressionConverter(std::shared_ptr<Expression> expression) :
        expression_{expression} {
    }

    std::shared_ptr<Expression> ExpressionConverter::ToExpression() const {
        return expression_;
    }

    std::shared_ptr<Statement> ExpressionConverter::ToStatement() const {
        return std::make_shared<Void>(expression_);
    }

    std::shared_ptr<Statement> ExpressionConverter::ToConditionalJump() const {
        return nullptr;
    }

}
