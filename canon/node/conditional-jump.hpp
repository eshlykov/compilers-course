#pragma once

#include "statement.hpp"
#include "../utils/address.hpp"
#include <memory>

namespace Irt {

    class Expression;

    enum class LogicalOperator {
        And,
        Less,
        Equal
    };

    class ConditionalJump : public Statement {
    public:
        ConditionalJump(LogicalOperator logicalOperator,
            std::shared_ptr<Expression> expressionLeft,
            std::shared_ptr<Expression> expressionRight,
            const Address& addressIf,
            const Address& addressElse);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const LogicalOperator logicalOperator_;
        const std::shared_ptr<Expression> expressionLeft_;
        const std::shared_ptr<Expression> expressionRight_;
        const Address addressIf_;
        const Address addressElse_;
    };

}
