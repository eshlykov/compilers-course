#include "expression-converter.hpp"
#include <exception>

namespace Irt {

    ExpressionConverter::ExpressionConverter(std::shared_ptr<Expression> expression) :
        expression_{expression} {
    }

    std::shared_ptr<Expression> ExpressionConverter::ToExpression() const {
        return expression_;
    }

    std::shared_ptr<Statement> ExpressionConverter::ToStatement() const {
        //return std::make_shared<Void>(expression_); // Undefined reference to ctor
        return nullptr;
    }

    std::shared_ptr<Statement> ExpressionConverter::ToConditionalJump(Address, Address) const {
        throw std::runtime_error{"ExpressionConverter::ToConditionalJump should never be called"};
    }

}
