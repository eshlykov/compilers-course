#include "expression-sequence.hpp"

namespace Irt {

    ExpressionSequence::ExpressionSequence(std::shared_ptr<Statement> statement,
        std::shared_ptr<Expression> expression) :
            statement_{statement},
            expression_{expression} {
        assert(statement_ != nullptr);
        assert(expression_ != nullptr);
    }

    void ExpressionSequence::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
