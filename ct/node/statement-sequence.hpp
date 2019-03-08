#pragma once

#include "statement.hpp"
#include <memory>

namespace Ct {

    class StatementSequence : public Statement {
    public:
        StatementSequence(std::shared_ptr<Statement> leftStatement,
            std::shared_ptr<Statement> rightStatement);

        virtual void Accept(Visitor* visitor) override final;

    public:
        const std::shared_ptr<Statement> leftStatement_;
        const std::shared_ptr<Statement> rightStatement_;
    };

}
