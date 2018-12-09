#pragma once

#include "statement.hpp"
#include <memory>

namespace Irt {

    class Expression;
    class Label;

    enum class LogicalOperator {
        And,
        Less
    };

    class Jump : public Statement {
    public:
        Jump(LogicalOperator logicalOperator,
            std::shared_ptr<Expression> expressionLeft,
            std::shared_ptr<Expression> expressionRight,
            std::shared_ptr<Label> labelIf,
            std::shared_ptr<Label> labelElse);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const LogicalOperator logicalOperator_;
        const std::shared_ptr<Expression> expressionLeft_;
        const std::shared_ptr<Expression> expressionRight_;
        const std::shared_ptr<Label> labelIf_;
        const std::shared_ptr<Label> labelElse_;
    };

}
