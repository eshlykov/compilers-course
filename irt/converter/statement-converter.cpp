#include "statement-converter.hpp"
#include <exception>

namespace Irt {

    StatementConverter::StatementConverter(std::shared_ptr<Statement> statement) :
        statement_{statement} {
    }

    std::shared_ptr<Expression> StatementConverter::ToExpression() const {
        return std::make_shared<ExpressionSequence>(statement, std::make_shared<Constant>(0));
    }

    std::shared_ptr<Statement> StatementConverter::ToStatement() const {
        return statement_;
    }

    std::shared_ptr<Statement> StatementConverter::ToConditionalJump(Address, Address) const {
        throw std::runtime_error{"StatementConverter::ToConditionalJump should never be called"};
    }

}
