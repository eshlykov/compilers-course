#include "conditional-jump-converter.hpp"
#include <exception>

namespace Irt {

    ConditionalJumpConverter::ConditionalJumpConverter(std::shared_ptr<Statement> statement) :
        statement_{statement} {
    }

    std::shared_ptr<Expression> ConditionalJumpConverter::ToExpression() const {
        return nullptr;
    }

    std::shared_ptr<Statement> ConditionalJumpConverter::ToStatement() const {
        throw std::runtime_error{"ConditionalJumpConverter::ToStatement should never be called"};
    }

}
