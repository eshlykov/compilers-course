#include "conditional-jump.hpp"

namespace Irt {

    ConditionalJump::ConditionalJump(LogicalOperator logicalOperator,
        std::shared_ptr<Expression> expressionLeft,
        std::shared_ptr<Expression> expressionRight,
        Address labelIf,
        Address labelElse) :
            logicalOperator_{logicalOperator},
            expressionLeft_{expressionLeft},
            expressionRight_{expressionRight},
            labelIf_{labelIf},
            labelElse_{labelElse} {
        assert(expressionLeft_ != nullptr);
        assert(expressionRight_ != nullptr);
    }

    void ConditionalJump::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
