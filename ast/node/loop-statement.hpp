#pragma once

#include "statement.hpp"
#include "expression.hpp"
#include <memory>

namespace Ast {

    class LoopStatement : public Statement {
    public:
        LoopStatement(Location location,
            std::unique_ptr<Expression> condition,
            std::unique_ptr<Statement> statement);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const std::unique_ptr<Expression> condition_;
        const std::unique_ptr<Statement> statement_;
    };

}
