#include "jump.hpp"

namespace Irt {

    Jump::Jump(LogicalOperator logicalOperator,
        std::shared_ptr<Expression> expressionLeft,
        std::shared_ptr<Expression> expressionRight,
        std::shared_ptr<Label> labelIf,
        std::shared_ptr<Label> labelElse) :
            logicalOperator_{logicalOperator},
            expressionLeft_{expressionLeft},
            expressionRight_{expressionRight},
            labelIf_{labelIf},
            labelElse_{labelElse} {
        assert(expressionLeft_ != nullptr);
        assert(expressionRight_ != nullptr);
        assert(labelIf_ != nullptr);
        assert(labelElse_ != nullptr);
    }

    void Jump::Accept(Visitor* visitor) {
        visitor->Visit(this);
    }

}
