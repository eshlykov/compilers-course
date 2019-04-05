#include "conditional-jump.hpp"

namespace Irt {

    ConditionalJump::ConditionalJump(LogicalOperator logicalOperator,
        std::shared_ptr<Expression> expressionLeft,
        std::shared_ptr<Expression> expressionRight,
        const Address& addressIf,
        const Address& addressElse) :
            logicalOperator_{logicalOperator},
            expressionLeft_{expressionLeft},
            expressionRight_{expressionRight},
            addressIf_{addressIf},
            addressElse_{addressElse} {
        assert(expressionLeft_ != nullptr);
        assert(expressionRight_ != nullptr);
    }

    void ConditionalJump::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
